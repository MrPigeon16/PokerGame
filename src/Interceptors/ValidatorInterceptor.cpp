#include "Interceptors/ValidatorInterceptor.h"
#include "Validator.h"
#include <grpcpp/support/interceptor.h>
#include <grpcpp/support/server_interceptor.h>
#include <unordered_set>

ValidatorInterceptor::ValidatorInterceptor(grpc::experimental::ServerRpcInfo* rpc_info) : rpc_info(rpc_info) {}

ValidatorInterceptor::ValidatorInterceptor(grpc::experimental::ServerRpcInfo* rpc_info, Server* server) : ValidatorInterceptor(rpc_info) {
    this->server = server;
}

void ValidatorInterceptor::Intercept(grpc::experimental::InterceptorBatchMethods* methods) {
    std::vector<Validator*> validators = this->server->getValidators();
    std::unordered_set<std::string> methodsToValidate;

    for (Validator* validator : validators) {
        methodsToValidate.insert("/" + server->getProtoPackage()+"."+validator->serviceName+"/"+validator->methodName);
    }


}
