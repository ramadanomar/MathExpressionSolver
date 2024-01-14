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

    virtual void run();
    virtual void evaluateExpression(const std::string& expression);
    virtual double calculateExpression(const std::string& expression);
    virtual void evaluateExpressionToFile(const std::string& expression, std::ostream& outputStream);

    virtual ~Menu() = default;
};
