#pragma once
#include "Validator.h"

class EmailValidator : public Validator {
public:
    using Validator::Validator;
    bool Validate(const void* email) const override;
};

class PasswordValidator : public Validator {
public:
    using Validator::Validator;

    bool Validate(const void* password) const override;
};
