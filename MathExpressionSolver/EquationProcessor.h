#pragma once

#include "Lexer.h"
#include <vector>
#include <string>

class EquationProcessor {
public:
    std::string rearrangeEquation(const std::pair<std::vector<Token*>, std::vector<Token*>>& equationParts);
private:
    void moveTerms(std::vector<Token*>& from, std::vector<Token*>& to);
    std::string tokensToString(const std::vector<Token*>& tokens);
};