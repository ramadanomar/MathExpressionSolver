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

        // Save result to storage
        if (resultStorage) {
            resultStorage->saveResult(Result(input, result));
        }
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

    auto getResult = [this](int index) -> double {
        if (!this->resultStorage->hasResult(index)) {
            throw std::runtime_error("Equation number " + std::to_string(index) + " was not found");
        }
        return this->resultStorage->getResult(index);
    };

    return evaluator.evaluate(shuntingYard.infixToPostfix(tokens), getResult);

}

void Menu::evaluateExpressionToFile(const std::string& expression, std::ostream& outputStream) {
    outputStream << std::fixed << std::setprecision(OUTPUT_PRECISION);
    try {
        double result = calculateExpression(expression);
        outputStream << "Result: " << result << std::endl;

        // Save result to storage
        if (resultStorage) {
            resultStorage->saveResult(Result(expression, result));
        }
    }
    catch (const std::runtime_error& e) {
        outputStream << "Error: " << e.what() << std::endl;
    }
}