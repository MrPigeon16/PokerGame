#pragma once

#include <grpcpp/grpcpp.h>
#include <grpcpp/support/interceptor.h>
#include <grpcpp/support/server_interceptor.h>
#include <grpcpp/support/status.h>
#include "Server.h"

class AuthInterceptor final : public grpc::experimental::Interceptor{
public:
    explicit AuthInterceptor(grpc::experimental::ServerRpcInfo* info);
    AuthInterceptor(grpc::experimental::ServerRpcInfo* info, Server* server);
    void Intercept(grpc::experimental::InterceptorBatchMethods* methods) override;
private:
    grpc::experimental::ServerRpcInfo* rpc_info;
    Server* server;
};
