#pragma once

#include "Token.h"
#include "DynamicArray.h"
#include <string>

class ExpressionEvaluator {
public:
    double evaluate(const DynamicArray& tokens);

private:
    double applyOperation(double a, double b, const std::string& op);
};
