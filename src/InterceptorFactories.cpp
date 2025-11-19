#include "InterceptorFactories.h"
#include "Interceptors.h"

grpc::experimental::Interceptor* ValidatorInterceptorsFactory::CreateServerInterceptor(grpc::experimental::ServerRpcInfo* rpc_info) {
    return new ValidatorInterceptor(rpc_info, server);
}

AuthInterceptorFactory::AuthInterceptorFactory(Server* server) : server(server) { }

grpc::experimental::Interceptor* AuthInterceptorFactory::CreateServerInterceptor(grpc::experimental::ServerRpcInfo* rpcInfo) {
    return new AuthInterceptor(rpcInfo, this->server);
}

ValidatorInterceptorsFactory::ValidatorInterceptorsFactory(Server* server) : server(server) { }
