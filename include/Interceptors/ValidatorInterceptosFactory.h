#pragma once
#include <grpcpp/grpcpp.h>
#include <grpcpp/support/interceptor.h>
#include <grpcpp/support/server_interceptor.h>
#include "Interceptors/ValidatorInterceptor.h"
#include "Server.h"


class ValidatorInterceptorsFactory : public grpc::experimental::ServerInterceptorFactoryInterface {
    public:
    ValidatorInterceptorsFactory(Server* server) : server(server)  {}
    grpc::experimental::Interceptor* CreateServerInterceptor(grpc::experimental::ServerRpcInfo* rpc_info) override;
    private:
    Server* server;
};
