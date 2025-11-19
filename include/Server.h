#pragma once
#include <grpcpp/impl/service_type.h>
#include <grpcpp/server_builder.h>
#include "Validators.h"
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

enum class VersionType {
    Production,
    Development
};

class ServerConfig {
    public:
    std::string host;
    int port;
    ServerConfig(std::string host, int port) : host(host), port(port), version(VersionType::Development) {}
    ServerConfig(std::string host, int port, grpc::SslServerCredentialsOptions sslOptions) : host(host), port(port), sslOptions(sslOptions), version(VersionType::Production) {}
    const grpc::SslServerCredentialsOptions sslOptions;
    VersionType getVersion() {
        return this->version;
    }
    private:
    const VersionType version;
};

class Server {
public:
    Server(ServerConfig& cfg, std::string protoPackage);
    Server(ServerConfig& cfg, std::vector<grpc::Service*> services, std::string protoPackage);
    void addService(grpc::Service* service);
    void run();
    std::vector<grpc::Service*> getServices();

    std::unordered_map<std::string, std::string> getAuthenicationOnlyMethods();
    void addAuthencationOnlyMethod(std::string serviceName, std::string methodName);
    std::string getProtoPackage();
    void addValidator(std::unique_ptr<Validator> validator);
    const std::vector<std::unique_ptr<Validator>>& getValidators();
private:
    std::vector<std::unique_ptr<Validator>> validators;
    std::unordered_map<std::string, std::string> authroizationOnlyMethods;
    const std::string protoPackage;
    std::vector<grpc::Service*> services;
    ServerConfig serverConfig;
    grpc::ServerBuilder builder;
    void bindServices();
};
