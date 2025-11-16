#pragma once
#include "Validator.h"
#include <regex>
#include <string>

class EmailValidator : public Validator {
public:
    using Validator::Validator;
    bool Validate(void* email) const override {
        const std::regex pattern(R"(\w+(\.|_)?\w*@\w+(\.\w+)+)");
        return std::regex_match(std::string((char*)email), pattern);
    }
};

class PasswordValidator : public Validator {
public:
    using Validator::Validator;

    bool Validate(void* password) const override {
        const std::regex pattern(R"(^(?=.*[a-z])(?=.*[A-Z])(?=.*\d)(?=.*[!@#$%^&*-+])[A-Za-z\d!@#$%^&*-+]{8,64}$)");

        return std::regex_match(std::string((char*)password), pattern);
    }
};
