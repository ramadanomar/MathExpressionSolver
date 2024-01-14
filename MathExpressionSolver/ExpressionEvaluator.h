#pragma once

#include "Token.h"
#include <vector>
#include <stack>
#include <string>
#include <functional>

class ExpressionEvaluator {
public:
    double evaluate(const std::vector<Token*>& tokens, std::function<double(int)> getResult);

private:
    double applyOperation(double a, double b, const std::string& op);
};
