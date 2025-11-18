#include "GrpcServices/AuthServiceImpl.h"
#include <exception>
#include <grpcpp/support/status.h>
#include <optional>
#include <sqlite_modern_cpp.h>
#include <sqlite3.h>
#include "DbState.h"
#include "JwtHelper.h"
#include "openssl/sha.h"
#include <chrono>

std::string sha256(const std::string& str) {
    unsigned char hash[SHA256_DIGEST_LENGTH];

    SHA256(reinterpret_cast<const unsigned char*>(str.c_str()), str.length(), hash);


    std::stringstream ss;
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }

    return ss.str();
}


grpc::Status AuthServiceImpl::Signin(grpc::ServerContext* context, const poker::AuthRequest* request, poker::AuthResponse* response) {
    if (request->cancell()) {

        return grpc::Status(grpc::StatusCode::CANCELLED, request->cancellmessage());
    }

    const std::string& email = request->email();

    try {
        sqlite::database& db = DbState::getInstance().getConnection();
        bool found = false;
        db << "SELECT 1 FROM Users WHERE email = ? LIMIT 1;" << email >> [&found](int) {
            found = true;
        };

        if (found) {
            response->set_responsestring("User with this uername already exists");
            return grpc::Status(grpc::StatusCode::ALREADY_EXISTS, "User with this email already exists");
        }



        const std::string hashed_password = sha256(request->password());

        db << "INSERT INTO Users (email, password, createdAt) VALUES (?, ?, ?)"
            << request->email()
            << hashed_password
            << std::chrono::duration_cast<std::chrono::seconds>(
                    std::chrono::system_clock::now().time_since_epoch()
                ).count();
        response->set_responsestring("Registered successfully");
    } catch (std::exception& ex) {
        return grpc::Status(grpc::StatusCode::INTERNAL, ex.what());
    }
    return grpc::Status::OK;
}


grpc::Status AuthServiceImpl::Login(grpc::ServerContext* context, const poker::AuthRequest* request, poker::AuthResponse* response) {
    if (request->cancell()) {

        return grpc::Status(grpc::StatusCode::CANCELLED, request->cancellmessage());
    }
 // Yuisj26! pass for ilayGay;

    try {
        sqlite::database& db = DbState::getInstance().getConnection();
        std::string hashedPassword = sha256(request->password());
        bool found = false;
        std::optional<std::string> password;
        db << "SELECT password FROM Users WHERE email = ? LIMIT 1;" << request->email() >> [&password](std::string pass) {
            password = pass;
        };

        if (!password.has_value()) {
            return grpc::Status(grpc::StatusCode::NOT_FOUND, "User with those credentials does not exists");
        }

        if (sha256(request->password()) != password) {
            return grpc::Status(grpc::StatusCode::NOT_FOUND, "User with those credentials does not exists");
        }
        JwtHelper jwtHelper;
        std::pair<std::string, std::string> tokenPair = jwtHelper.generateJwtTokens(request->email());

        response->set_responsestring(tokenPair.first);
    } catch (std::exception& ex) {

        return grpc::Status(grpc::StatusCode::INTERNAL, ex.what());

    }
    return grpc::Status::OK;
}
