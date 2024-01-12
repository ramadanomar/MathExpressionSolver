#pragma once
#pragma once
#include <string>

class FileValidator {
public:
    virtual bool isValid(const std::string& filename) const = 0;
    virtual ~FileValidator() = default;
};
