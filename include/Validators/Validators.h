#pragma once
#include <regex>
#include <string>

inline bool validate_email(const std::string& email) {
    const std::regex pattern(R"(\w+(\.|_)?\w*@\w+(\.\w+)+)");
    return std::regex_match(email, pattern);
}
