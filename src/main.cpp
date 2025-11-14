#include "Server.h"
#include <grpcpp/grpcpp.h>
#include <grpcpp/impl/service_type.h>
#include <vector>
#include "ServerConfig.h"
#include "protos/hello.grpc.pb.h"
#include "protos/hello.pb.h"

/*
 *  Auth Service / MsSql / In memry cache;
 *  Start game / Token JWT Buy in
 *
 *
 *
 */

class MyServiceImpl final : public hello::HelloService::Service {
public:
    grpc::Status SayHello(grpc::ServerContext* context, const hello::HelloRequest* request, hello::HelloResponse* response) override {
        response->set_reply("Hello, " + request->greeting());
        return grpc::Status::OK;
    }
};

int main(){
    std::vector<grpc::Service*> services;
    MyServiceImpl service;
    services.push_back(&service);
    ServerConfig serverConfig("0.0.0.0", 8080);
    Server server(serverConfig, services);
    server.run();
}
