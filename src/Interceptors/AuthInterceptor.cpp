#include "Interceptors/AuthInterceptor.h"
#include "Server.h"
#include <grpcpp/support/interceptor.h>
#include <grpcpp/support/server_interceptor.h>
#include <string>
#include <unordered_set>
#include <utility>

AuthInterceptor::AuthInterceptor(grpc::experimental::ServerRpcInfo* rpc_info) : rpc_info(rpc_info) {}
AuthInterceptor::AuthInterceptor(grpc::experimental::ServerRpcInfo* rpc_info, Server* server) : rpc_info(rpc_info), server(server) {}

void AuthInterceptor::Intercept(grpc::experimental::InterceptorBatchMethods* methods) {
    if (methods->QueryInterceptionHookPoint(grpc::experimental::InterceptionHookPoints::PRE_SEND_STATUS)) {
        std::unordered_set<std::string> fullAuthorizationMethodsNames;
        for (const std::pair<std::string, std::string> pair : this->server->getAuthenicationOnlyMethods()) {
            fullAuthorizationMethodsNames.insert("/" + server->getProtoPackage()+"."+pair.first+"/"+pair.second);
        }
        if (fullAuthorizationMethodsNames.find((std::string)this->rpc_info->method()) != fullAuthorizationMethodsNames.end()) {
            const auto& test = rpc_info->server_context()->client_metadata();
            for (const auto& t :test) {
                std::cout << t.first << " : " << t.second << std::endl;
            }
        }
    }

    methods->Proceed();
}
