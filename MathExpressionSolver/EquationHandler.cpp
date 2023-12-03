#include "EquationHandler.h"
#include <stdexcept>

EquationHandler::EquationHandler() {}

std::string EquationHandler::processEquation(const std::string& equation) {
    // Check if the input is an equation
    if (!lexer.containsEquation(equation)) {
        throw std::runtime_error("Input is not a valid equation.");
    }

    // Split the equation into two parts
    auto equationParts = lexer.splitEquation(equation);

    // Rearrange the equation
    std::string rearrangedEquation = processor.rearrangeEquation(equationParts);

    return rearrangedEquation;
}