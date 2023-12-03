#include "Lexer.h"
#include "ShuntingYard.h"
#include <iostream>
#include <vector>

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
    std::string input = "7*(4+390)/38*23";
    Lexer lexer;
    ShuntingYard shuntingYard;

    std::pair<std::vector<Token*>, std::vector<Token*>> equationParts;

    try {
        if (lexer.containsEquation(input)) {
            equationParts = lexer.splitEquation(input);

            std::cout << "Left Side Tokens:\n";
            for (const auto& token : equationParts.first) {
                std::cout << tokenTypeToString(token->getType()) << ": " << token->getValue() << std::endl;
            }

			std::cout << "\nLeft Side RPN Tokens:\n";
            auto leftSideRPN = shuntingYard.infixToPostfix(equationParts.first);
            for (const auto& token : leftSideRPN) {
				std::cout << tokenTypeToString(token->getType()) << ": " << token->getValue() << std::endl;
			}

            std::cout << "\nRight Side Tokens:\n";
            for (const auto& token : equationParts.second) {
                std::cout << tokenTypeToString(token->getType()) << ": " << token->getValue() << std::endl;
            }

            std::cout << "\nRight Side RPN Tokens:\n";
            for (const auto& token : shuntingYard.infixToPostfix(equationParts.second)) {
				std::cout << tokenTypeToString(token->getType()) << ": " << token->getValue() << std::endl;
			}
        }
        else {
            // Nu este equatie
            auto tokens = lexer.tokenize(input);
            for (const auto& token : tokens) {
                std::cout << tokenTypeToString(token->getType()) << ": " << token->getValue() << std::endl;
            }

            std::cout << "\nRPN Tokens:\n";
            for (const auto& token : shuntingYard.infixToPostfix(tokens)) {
                std::cout << tokenTypeToString(token->getType()) << ": " << token->getValue() << std::endl;
            }
        }
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Error processing input: " << e.what() << std::endl;
        return 1;
    }

    // Clean up tokens for equations
    for (auto& token : equationParts.first) {
        delete token;
    }
    for (auto& token : equationParts.second) {
        delete token;
    }

    return 0;
}


