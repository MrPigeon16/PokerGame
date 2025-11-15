#pragma once
#include "Server.h"
#include <grpcpp/grpcpp.h>

class AuthInterceptorFactory : public grpc::experimental::ServerInterceptorFactoryInterface {
    public:
    AuthInterceptorFactory(Server* server);
    grpc::experimental::Interceptor* CreateServerInterceptor(grpc::experimental::ServerRpcInfo* rpcInfo) override;
    private:
    Server* server;
};
