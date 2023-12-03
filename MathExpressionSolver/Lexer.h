#pragma once

#include "Token.h"
#include <string>
#include <vector>

class Lexer {
public:
    std::vector<Token*> tokenize(const std::string& input);

private:
    bool isDigit(char c) const;
    bool isAlpha(char c) const;
};