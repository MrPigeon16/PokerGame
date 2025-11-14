#include "Server.h"
#include "ServerConfig.h"
#include "version.h"
#include <grpcpp/security/credentials.h>
#include <grpcpp/security/server_credentials.h>

Server::Server(ServerConfig& config) : serverConfig(config), builder() {
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

Server::Server(ServerConfig& config, std::vector<grpc::Service*> services) : Server(config) {
    this->services = services;
    this->bindServices();
}

void Server::bindServices() {
    for (auto& service : this->services) {
        this->builder.RegisterService(service);
    }
}

void Server::run() {
    std::unique_ptr<grpc::Server> server(this->builder.BuildAndStart());

    std::cout << "Server listenning on " << this->serverConfig.host << std::endl;

    server->Wait();
}
