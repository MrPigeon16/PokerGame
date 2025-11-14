#pragma once

#include <grpcpp/grpcpp.h>
#include <grpcpp/security/server_credentials.h>
#include <string>
#include <version.h>

class ServerConfig{
    public:
    std::string host;
    int port;
    ServerConfig(std::string host, int port) : host(host), port(port), version(VersionType::Development) {}
    ServerConfig(std::string host, int port, grpc::SslServerCredentialsOptions sslOptions) : host(host), port(port), sslOptions(sslOptions), version(VersionType::Production) {}
    const grpc::SslServerCredentialsOptions sslOptions;
    VersionType getVersion() {
        return this->version;
    }
    private:
    const VersionType version;
};
