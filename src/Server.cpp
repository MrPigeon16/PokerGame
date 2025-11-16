#include "Server.h"
#include "Interceptors/AuthInterceptorFactory.h"
#include "ServerConfig.h"
#include "version.h"
#include <grpcpp/security/credentials.h>
#include <grpcpp/security/server_credentials.h>
#include <grpcpp/support/server_interceptor.h>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

Server::Server(ServerConfig& config, std::string protoPackage) : serverConfig(config), builder(), protoPackage(protoPackage){
    std::string server_address = this->serverConfig.host + ":" + std::to_string(this->serverConfig.port);

    std::shared_ptr<grpc::ServerCredentials> creds;

    if (config.getVersion() == VersionType::Development) {
        creds = grpc::InsecureServerCredentials();
    } else {
        creds = grpc::SslServerCredentials(this->serverConfig.sslOptions);
    }

    this->builder.AddListeningPort(server_address, creds);
}

std::vector<grpc::Service*> Server::getServices() {
    return this->services;
}

void Server::addService(grpc::Service* service) {
    this->services.push_back(service);
    this->builder.RegisterService(service);
}

void Server::addAuthencationOnlyMethod(std::string serviceName, std::string methodName) {
    this->authroizationOnlyMethods.insert(std::make_pair(serviceName, methodName));
}

std::unordered_map<std::string, std::string> Server::getAuthenicationOnlyMethods() {
    return this->authroizationOnlyMethods;
}

Server::Server(ServerConfig& config, std::vector<grpc::Service*> services, std::string protoPackage) : Server(config, protoPackage) {
    this->services = services;
    this->bindServices();
}

void Server::bindServices() {
    for (auto& service : this->services) {
        this->builder.RegisterService(service);
    }
}

void Server::run() {
    std::vector<std::unique_ptr<grpc::experimental::ServerInterceptorFactoryInterface>> creators;
    creators.push_back(std::unique_ptr<grpc::experimental::ServerInterceptorFactoryInterface>(
        new AuthInterceptorFactory(this)
    ));
    this->builder.experimental().SetInterceptorCreators(std::move(creators));
    std::unique_ptr<grpc::Server> server(this->builder.BuildAndStart());

    std::cout << "Server listenning on " << this->serverConfig.host << std::endl;

    server->Wait();
}

std::string Server::getProtoPackage() {
    return this->protoPackage;
}

std::vector<Validator*> Server::getValidators() {
    return this->validators;
}

void Server::addValidator(Validator* validator) {
    this->validators.push_back(validator);
}
