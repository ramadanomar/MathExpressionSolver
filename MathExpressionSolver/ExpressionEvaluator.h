#pragma once

#include "Token.h"
#include <vector>
#include <string>
#include <stack>

class ExpressionEvaluator {
public:
    double evaluate(const std::vector<Token*>& tokens);

private:
    double applyOperation(double a, double b, const std::string& op);
};
