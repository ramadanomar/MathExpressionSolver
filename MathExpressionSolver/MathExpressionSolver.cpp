#include "Lexer.h"
#include "ShuntingYard.h"
#include "ExpressionEvaluator.h"
#include <iostream>
#include <iomanip>
#include <vector>

constexpr int OUTPUT_PRECISION = 4;

// Helper function to convert TokenType to string
std::string tokenTypeToString(TokenType type) {
    switch (type) {
    case TokenType::Number:     return "Number";
    case TokenType::Operator:   return "Operator";
    case TokenType::Variable:   return "Variable";
    case TokenType::Parenthesis: return "Parenthesis";
    default:                    return "Unknown";
    }
}

int main() {
    // Set output precision only for floating point numbers (currently we have all numbers as double, we should either use a fixed point or atleast differentiate output)
    std::cout << std::fixed << std::setprecision(OUTPUT_PRECISION);

    std::string input = "[(2*3)^2]/4-(6+2)#3";
    Lexer lexer;
    ShuntingYard shuntingYard;
    ExpressionEvaluator evaluator;

    // Aparent nu trb sa implementez ecuatii ca nu sunt intr o echipa
    try {
            // Nu este ecuatie
            auto tokens = lexer.tokenize(input);
            for (const auto& token : tokens) {
                std::cout << tokenTypeToString(token->getType()) << ": " << token->getValue() << std::endl;
            }

            std::cout << "\nRPN Tokens:\n";
            for (const auto& token : shuntingYard.infixToPostfix(tokens)) {
                std::cout << tokenTypeToString(token->getType()) << ": " << token->getValue() << std::endl;
            }

            double result = evaluator.evaluate(shuntingYard.infixToPostfix(tokens));
            std::cout << "\nResult: " << result << std::endl;
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Error processing input: " << e.what() << std::endl;
        return 1;
    }


    return 0;
}


