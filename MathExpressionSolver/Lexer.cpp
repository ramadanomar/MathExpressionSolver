#include "Lexer.h"
#include <cctype>
#include <stdexcept>
#include <vector>

std::vector<Token*> Lexer::tokenize(const std::string& input) {
    return tokenizeExpression(input);
}


std::vector<Token*> Lexer::tokenizeExpression(const std::string& expression) {
    std::vector<Token*> tokens;

    for (size_t i = 0; i < expression.length(); ++i) {
        char c = expression[i];

        if (isDigit(c) || (c == '.' && i + 1 < expression.length() && isDigit(expression[i + 1]))) {
            std::string numStr(1, c);
            while (i + 1 < expression.length() && (isDigit(expression[i + 1]) || expression[i + 1] == '.')) {
                numStr += expression[++i];
            }
            tokens.push_back(new NumberToken(numStr));
        }
        else if (OperatorToken::isValidOperator(c)) {
            auto props = OperatorToken::getOperatorProperties(c);
            tokens.push_back(new OperatorToken(std::string(1, c), props.precedence, props.isLeftAssociative));
        }
        else if (isAlpha(c)) {
            std::string varStr(1, c);
            while (i + 1 < expression.length() && isAlpha(expression[i + 1])) {
                varStr += expression[++i];
            }
            tokens.push_back(new VariableToken(varStr));
        }
        else if (c == '(' || c == '[') {
            // TODO: We currently consider both as paranthesis, we should probably atleast check if the count of ( and [ are equal and not have a ) end a [ for example
            tokens.push_back(new ParenthesisToken(std::string(1, c), true));
        }
        else if (c == ')' || c == ']') {
            tokens.push_back(new ParenthesisToken(std::string(1, c), false));
        }
        else if (std::isspace(c)) {
            // Spaces are ignored
            continue;
        }
        else {
            throw std::runtime_error("Invalid character in input");
        }
    }

    return tokens;
}

bool Lexer::isDigit(char c) const {
    return std::isdigit(static_cast<unsigned char>(c));
}

bool Lexer::isAlpha(char c) const {
    return std::isalpha(static_cast<unsigned char>(c));
}

bool Lexer::isVariableToken(const Token* token) const {
    return token->getType() == TokenType::Variable;
}

bool Lexer::isNumberToken(const Token* token) const {
    return token->getType() == TokenType::Number;
}