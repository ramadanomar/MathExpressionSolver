#include "Menu.h"
#include "Lexer.h"
#include "ShuntingYard.h"
#include "ExpressionEvaluator.h"
#include <iostream>
#include <iomanip>
#include <stdexcept>

constexpr int OUTPUT_PRECISION = 4;

void Menu::run() {
    std::string input;
    std::cout << std::fixed << std::setprecision(OUTPUT_PRECISION);

    while (true) {
        std::cout << "Enter an expression (or type 'exit' to quit): ";
        std::getline(std::cin, input);

        if (input == "exit") {
            break;
        }

        evaluateExpression(input);
    }
}

void Menu::evaluateExpression(const std::string& input) {
    try {
        double result = calculateExpression(input);
        std::cout << std::fixed << std::setprecision(OUTPUT_PRECISION) << "Result: " << result << std::endl;
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Error processing input: " << e.what() << std::endl;
    }
}

double Menu::calculateExpression(const std::string& input) {
    Lexer lexer;
    ShuntingYard shuntingYard;
    ExpressionEvaluator evaluator;

    auto tokens = lexer.tokenize(input);
    return evaluator.evaluate(shuntingYard.infixToPostfix(tokens));
}

void Menu::evaluateExpressionToFile(const std::string& expression, std::ostream& outputStream) {
    outputStream << std::fixed << std::setprecision(OUTPUT_PRECISION);
    try {
        double result = calculateExpression(expression);
        outputStream << "Result: " << result << std::endl;
    }
    catch (const std::runtime_error& e) {
        outputStream << "Error: " << e.what() << std::endl;
    }
}