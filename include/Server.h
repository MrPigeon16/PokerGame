#pragma once
#include <grpcpp/impl/service_type.h>
#include <grpcpp/server_builder.h>
#include "ServerConfig.h"
#include <vector>
class Server {
    public:
    Server(ServerConfig& cfg);
    Server(ServerConfig& cfg, std::vector<grpc::Service*> services);
    void addService(grpc::Service* service);
    void run();
    std::vector<grpc::Service*> getServices();
    private:
    std::vector<grpc::Service*> services;
    ServerConfig serverConfig;
    grpc::ServerBuilder builder;
    void bindServices();
};
