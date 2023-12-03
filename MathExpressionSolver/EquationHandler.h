#pragma once

#include "Lexer.h"
#include "EquationProcessor.h"
#include <string>

class EquationHandler {
public:
    EquationHandler();
    std::string processEquation(const std::string& equation);

private:
    Lexer lexer;
    EquationProcessor processor;
};
