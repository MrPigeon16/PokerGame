#pragma once

#include <grpcpp/server.h>
#include <grpcpp/support/interceptor.h>
#include <grpcpp/support/server_interceptor.h>
#include "Server.h"

class ValidatorInterceptor final : public grpc::experimental::Interceptor {
public:
    explicit ValidatorInterceptor(grpc::experimental::ServerRpcInfo* rpc_info);
    ValidatorInterceptor(grpc::experimental::ServerRpcInfo* rpc_info, Server* server);
    void Intercept(grpc::experimental::InterceptorBatchMethods* methods) override;
private:
    grpc::experimental::ServerRpcInfo* rpc_info;
    Server* server;
};
