#include "Lexer.h"
#include <iostream>
#include <vector>

int main() {
    std::string input = "x + 5.34 + 323 - 64/33$";
    Lexer lexer;
    std::vector<Token*> tokens;

    try {
        tokens = lexer.tokenize(input);
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Error tokenizing input: " << e.what() << std::endl;
        return 1;
    }

    for (const auto& token : tokens) {
        switch (token->getType()) {
        case TokenType::Number:
            std::cout << "nr: " << token->getValue() << std::endl;
            break;
        case TokenType::Operator:
            std::cout << "op: " << token->getValue() << std::endl;
            break;
        case TokenType::Variable:
            std::cout << "var: " << token->getValue() << std::endl;
            break;
        case TokenType::Parenthesis:
            std::cout << "paranteza: " << token->getValue() << std::endl;
            break;
        }
    }

    // garbage collection
    for (auto& token : tokens) {
        delete token;
    }

    return 0;
}
