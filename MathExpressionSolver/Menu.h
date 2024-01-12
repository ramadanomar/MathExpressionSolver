#pragma once

#include <string>
#include <iostream>
#include "FileValidator.h"
#include "IResultStorage.h"
#include "Result.h"

class Menu {
    FileValidator* validator;
    IResultStorage* resultStorage;

public:
    Menu(FileValidator* validator, IResultStorage* storage)
        : validator(validator), resultStorage(storage) {}

    void run();
    void evaluateExpression(const std::string& expression);
    double calculateExpression(const std::string& expression);
    void evaluateExpressionToFile(const std::string& expression, std::ostream& outputStream);
};
