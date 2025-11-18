#pragma once
#include <grpcpp/impl/service_type.h>
#include <grpcpp/server_builder.h>
#include "ServerConfig.h"
#include "Validator.h"
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
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
