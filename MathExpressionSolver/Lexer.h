#pragma once

#include "Token.h"
#include <vector>
#include <string>

class Lexer {
private:
    bool isSpace(char c) const;

protected:
    virtual std::vector<Token*> tokenizeExpression(const std::string& expression);
    virtual Token* parseNumber(const std::string& expression, size_t& index);
    virtual Token* createOperatorToken(char c);
    virtual Token* parseVariable(const std::string& expression, size_t& index);
    virtual Token* createParenthesisToken(char c, bool isOpen);
    virtual bool isDigit(char c) const;
    virtual bool isAlpha(char c) const;

public:
    virtual ~Lexer() = default;
    std::vector<Token*> tokenize(const std::string& input);
};
