#include "Interceptors.h"
#include "Server.h"
#include <grpcpp/support/interceptor.h>
#include <grpcpp/support/server_interceptor.h>
#include <string>
#include <unordered_set>
#include <utility>
#include "InterceptorFactories.h"
#include "Validators.h"
#include <regex>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/message.h>


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

            }
        }
    }

    methods->Proceed();
}

bool PasswordValidator::Validate(const void* password) const {
    const char* str = static_cast<const char*>(password);
    if (!str) return false;
    static std::regex pattern(R"(^(?=.*[a-z])(?=.*[A-Z])(?=.*\d)(?=.*[!@#$%^&*-+])[A-Za-z\d!@#$%^&*-+]{8,64}$)");
    return std::regex_match(str, pattern);
}

bool EmailValidator::Validate(const void* email) const {
    const char* str = static_cast<const char*>(email);
    if (!str) {
        return false;
    };
    const std::regex pattern(R"([A-Za-z0-9]+([._][A-Za-z0-9]+)*@[A-Za-z0-9]+\.[A-Za-z]{2,})");
    return std::regex_match(str, pattern);
}

ValidatorInterceptor::ValidatorInterceptor(grpc::experimental::ServerRpcInfo* rpc_info) : rpc_info(rpc_info) {}

ValidatorInterceptor::ValidatorInterceptor(grpc::experimental::ServerRpcInfo* rpc_info, Server* server) : ValidatorInterceptor(rpc_info) {
    this->server = server;
}

void ValidatorInterceptor::Intercept(grpc::experimental::InterceptorBatchMethods* methods) {
    if (methods->QueryInterceptionHookPoint(grpc::experimental::InterceptionHookPoints::POST_RECV_MESSAGE)) {
        const std::vector<std::unique_ptr<Validator>>& validators = this->server->getValidators();
        std::unordered_set<std::string> methodsToValidate;

        google::protobuf::Message* req_msg = static_cast<google::protobuf::Message*>(methods->GetRecvMessage());

        const google::protobuf::Reflection* refl = req_msg->GetReflection();
        const google::protobuf::Descriptor* desc = req_msg->GetDescriptor();

        // if (!req_msg && validators.size() != 0) {
        //     methods->ModifySendStatus(grpc::Status(grpc::StatusCode::INVALID_ARGUMENT, "No arguments provided"));
        //     methods->Proceed();

        //     return;
        // }

        for (const std::unique_ptr<Validator>& validator : validators) {
            if (("/" + server->getProtoPackage()+"."+validator->serviceName+"/"+validator->methodName) != this->rpc_info->method()) continue;
            const google::protobuf::FieldDescriptor* field = desc->FindFieldByName(validator->fieldName);
            const google::protobuf::FieldDescriptor* cancellField = desc->FindFieldByLowercaseName("cancell");
            const google::protobuf::FieldDescriptor* cancellMsgField = desc->FindFieldByName("cancellMessage");
            if (!field) {
                refl->SetBool(req_msg, cancellField, true);
                refl->SetString(req_msg, cancellMsgField, "Field " + validator->fieldName + " was not found");

                methods->Proceed();
                return;
            }

            std::string value = refl->GetString(*req_msg, field);
            if (!validator->Validate(value.c_str())) {
                std::string err_msg = "Invalid argument: " + validator->fieldName;
                const grpc::Status status(grpc::StatusCode::INVALID_ARGUMENT, err_msg);

                refl->SetBool(req_msg, cancellField, true);
                refl->SetString(req_msg, cancellMsgField, err_msg);
                methods->Proceed();

                return;
            }


        }
    }
        methods->Proceed();

}
