#pragma once

#include "authService.grpc.pb.h"
#include "authService.pb.h"
#include <grpcpp/server_context.h>

class AuthServiceImpl final : public poker::AuthService::Service {
public:
    grpc::Status Signin(grpc::ServerContext* context, const poker::AuthRequest* request, poker::AuthResponse* response) override;

    grpc::Status Login(grpc::ServerContext* context, const poker::AuthRequest* request, poker::AuthResponse* response) override;
};
