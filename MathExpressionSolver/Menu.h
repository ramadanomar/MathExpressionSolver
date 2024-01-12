#pragma once

#include <string>
#include <iostream>
#include "FileValidator.h"

class Menu {
    FileValidator* validator;

public:
    Menu(FileValidator* validator) : validator(validator) {}
    void run();
    void evaluateExpression(const std::string& expression);
    double calculateExpression(const std::string& expression);
    void evaluateExpressionToFile(const std::string& expression, std::ostream& outputStream);
};
