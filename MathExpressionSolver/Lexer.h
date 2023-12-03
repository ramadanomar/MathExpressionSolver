#pragma once

#include "Token.h"
#include <string>
#include <vector>
#include <utility>

class Lexer {
public:
    std::vector<Token*> tokenize(const std::string& input);
private:
    bool isDigit(char c) const;
    bool isAlpha(char c) const;
    bool isVariableToken(const Token* token) const;
    bool isNumberToken(const Token* token) const;
    std::vector<Token*> tokenizeExpression(const std::string& expression);
};