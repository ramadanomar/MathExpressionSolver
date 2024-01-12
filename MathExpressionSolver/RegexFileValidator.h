#pragma once
#include "FileValidator.h"
#include <regex>

class RegexFileValidator : public FileValidator {
public:
    bool isValid(const std::string& filename) const override {
        static const std::regex pattern(R"(^[a-zA-Z0-9](?:[a-zA-Z0-9 ._-]*[a-zA-Z0-9])?\.[a-zA-Z0-9_-]+$)");
        return std::regex_match(filename, pattern);
    }
};
