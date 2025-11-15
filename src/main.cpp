#include "GrpcServices/AuthServiceImpl.h"
#include "Server.h"
#include <grpcpp/grpcpp.h>
#include <grpcpp/impl/service_type.h>
#include <grpcpp/support/interceptor.h>
#include <grpcpp/support/server_interceptor.h>
#include <string>
#include <vector>
#include "ServerConfig.h"

/*
 *  Auth Service / MsSql / In memry cache;
 *  Start game / Token JWT Buy in
 *
 *
 *
 */


int main(){
    std::vector<grpc::Service*> services;

    AuthServiceImpl authService;
    services.push_back(&authService);

    ServerConfig serverConfig("0.0.0.0", 8080);

    Server server(serverConfig, services, "poker");

    server.run();
}
