#pragma once

#include "Token.h"
#include <vector>
#include <stack>

class ShuntingYard {
public:
    std::vector<Token*> infixToPostfix(const std::vector<Token*>& infixTokens);
private:
    bool isOperator(const Token* token) const;
    bool isHigherPrecedence(const OperatorToken* op1, const OperatorToken* op2) const;
};