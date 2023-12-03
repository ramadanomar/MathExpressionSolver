#pragma once

#include "Token.h"
#include "DynamicArray.h"


class ShuntingYard {
public:
    DynamicArray infixToPostfix(DynamicArray& infixTokens);
private:
    bool isOperator(const Token* token) const;
    bool isHigherPrecedence(const OperatorToken* op1, const OperatorToken* op2) const;
};