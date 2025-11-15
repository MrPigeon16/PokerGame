#include "Interceptors/AuthInterceptorFactory.h"
#include "Interceptors/AuthInterceptor.h"
#include "Server.h"
#include <grpcpp/support/interceptor.h>
#include <grpcpp/support/server_interceptor.h>

AuthInterceptorFactory::AuthInterceptorFactory(Server* server) : server(server) { }

grpc::experimental::Interceptor* AuthInterceptorFactory::CreateServerInterceptor(grpc::experimental::ServerRpcInfo* rpcInfo) {
    return new AuthInterceptor(rpcInfo, this->server);
}
