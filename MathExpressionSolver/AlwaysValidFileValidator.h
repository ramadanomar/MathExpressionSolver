#pragma once
#pragma once
#include "FileValidator.h"

class AlwaysValidFileValidator : public FileValidator {
public:
    bool isValid(const std::string& filename) const override {
        return true;  // We should never use this. Good enough until i test regex file validator properly
    }
};
