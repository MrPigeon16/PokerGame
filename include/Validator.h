#pragma once
#include <string>


class Validator {
public:
    Validator(const std::string serviceName, const std::string methodName, std::string fieldName) : serviceName(serviceName), methodName(methodName), fieldName(fieldName) {}
    virtual bool Validate(const void* arg) const = 0;
    const std::string serviceName;
    const std::string methodName;
    const std::string fieldName;
};
