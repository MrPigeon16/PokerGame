#pragma once
#include <string>


class Validator {
public:
    Validator(const std::string serviceName, const std::string methodName) : serviceName(serviceName), methodName(methodName) {}
    virtual bool Validate(void* arg) const = 0;
    const std::string serviceName;
    const std::string methodName;
};
