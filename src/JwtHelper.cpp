#include "JwtHelper.h"
#include <chrono>
#include <jwt-cpp/traits/kazuho-picojson/defaults.h>
#include <jwt-cpp/traits/kazuho-picojson/traits.h>
#include <string>
#include <utility>
#include <jwt-cpp/jwt.h>

std::pair<std::string, std::string> JwtHelper::generateJwtTokens(std::string email) {

    auto currentTime = std::chrono::system_clock::now();
    auto expireAuthTime = currentTime + std::chrono::seconds(this->AUTH_SECONDS_EXPIRE);
    auto expireRefreshTime = currentTime + std::chrono::seconds(this->REFRESH_SECONDS_EXPIRE);


    jwt::claim email_claim(email);


    auto authTokenBuilder = jwt::create().
        set_issuer(this->issuer)
        .set_issued_at(currentTime)
        .set_expires_at(expireAuthTime)
        .set_payload_claim("email", email_claim);

    std::string signedToken = authTokenBuilder.sign(jwt::algorithm::hs256(this->JwtSecret));

    auto refreshTokenBuilder = jwt::create()

        .set_issuer(this->issuer)
        .set_issued_at(currentTime)
        .set_expires_at(expireRefreshTime)
        .set_payload_claim("email", email_claim);

    std::string signedRefreshToken = refreshTokenBuilder.sign(jwt::algorithm::hs256(this->JwtSecret));

    return std::pair<std::string, std::string>(signedToken, signedRefreshToken);
}
