#include "Services.h"
#include "Server.h"
#include <grpcpp/grpcpp.h>
#include <grpcpp/impl/service_type.h>
#include <grpcpp/support/interceptor.h>
#include <grpcpp/support/server_interceptor.h>
#include <memory>
#include <string>
#include <vector>
#include "Validators.h"

/*
 *  Auth Service / MsSql / In memry cache;
 *  Start game / Token JWT Buy in
 *
 *
 *
 */


int main(){
    std::vector<grpc::Service*> services;

    AuthServiceImpl authService;
    services.push_back(&authService);

    ServerConfig serverConfig("0.0.0.0", 8080);

    Server server(serverConfig, services, "poker");
    server.addValidator(std::make_unique<PasswordValidator>("AuthService", "Signin", "password"));
    server.addValidator(std::make_unique<EmailValidator>("AuthService", "Signin", "email"));
    server.addValidator(std::make_unique<PasswordValidator>("AuthService", "Login", "password"));
    server.addValidator(std::make_unique<EmailValidator>("AuthService", "Login", "email"));
    server.run();
}
