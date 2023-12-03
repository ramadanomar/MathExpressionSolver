#pragma once

#include "Token.h"
#include "DynamicArray.h"
#include <string>
#include <utility>

class Lexer {
public:
    DynamicArray tokenize(const std::string& input);
private:
    bool isDigit(char c) const;
    bool isAlpha(char c) const;
    bool isVariableToken(const Token* token) const;
    bool isNumberToken(const Token* token) const;
    DynamicArray  tokenizeExpression(const std::string& expression);
};