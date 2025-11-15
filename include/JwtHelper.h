#pragma once
#include <string>
#include <utility>


class JwtHelper {
public:
    std::pair<std::string, std::string> generateJwtTokens(std::string email);
    std::string renewAuthToken(std::string refreshToken);
private:
    const int AUTH_SECONDS_EXPIRE = 60 * 60; // 1 houd
    const int REFRESH_SECONDS_EXPIRE = 7 * 24 * 60 * 60; // 1 week
    const std::string JwtSecret = "IlayShamenSecret1234AuthJwtMaximMeleh!";
    const std::string issuer = "MaximAndIlay";
};
