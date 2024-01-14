#include "ShuntingYard.h"
#include <stdexcept>

#include "ShuntingYard.h"
#include <stdexcept>

std::vector<Token*> ShuntingYard::infixToPostfix(const std::vector<Token*>& infixTokens) {
    std::stack<Token*> operatorStack;
    std::vector<Token*> postfixTokens;

    for (const auto& token : infixTokens) {
        if (token->getType() == TokenType::Number ||
            token->getType() == TokenType::Variable ||
            token->getType() == TokenType::DollarVariable) {
            // Variables (x,y,z etc.) are not implemented yet
            // $1 $2 are just numbers stored somewhere else so we treat them as numbers.
            postfixTokens.push_back(token);
        }
        else if (isOperator(token)) {
            // Handle Order of Operations with Operators
            while (!operatorStack.empty() &&
                isHigherPrecedence(static_cast<OperatorToken*>(operatorStack.top()),
                    static_cast<OperatorToken*>(token))) {
                postfixTokens.push_back(operatorStack.top());
                operatorStack.pop();
            }
            operatorStack.push(token);
        }
        else if (token->getType() == TokenType::Parenthesis) {
            ParenthesisToken* pt = static_cast<ParenthesisToken*>(token);
            if (pt->getIsOpen()) {
                operatorStack.push(token);
            }
            else {
                // Handle Order of Operations with Parentheses
                while (!operatorStack.empty() &&
                    operatorStack.top()->getType() != TokenType::Parenthesis) {
                    postfixTokens.push_back(operatorStack.top());
                    operatorStack.pop();
                }
                if (!operatorStack.empty()) {
                    operatorStack.pop(); // Pop the matching opening parenthesis
                }
                else {
                    throw std::runtime_error("Mismatched parentheses");
                }
            }
        }
    }

    // After processing all tokens, pop any remaining operators from the stack
    while (!operatorStack.empty()) {
        if (operatorStack.top()->getType() == TokenType::Parenthesis) {
            // If there's a parenthesis left in the stack, it's unmatched
            throw std::runtime_error("Mismatched parentheses");
        }
        postfixTokens.push_back(operatorStack.top());

        operatorStack.pop();
    }

    return postfixTokens;
}


bool ShuntingYard::isOperator(const Token* token) const {
    return token->getType() == TokenType::Operator;
}

bool ShuntingYard::isHigherPrecedence(const OperatorToken* op1, const OperatorToken* op2) const {
    if (!op1 || !op2) return false;
    return op1->getPrecedence() > op2->getPrecedence() ||
        (op1->getPrecedence() == op2->getPrecedence() && op1->getIsLeftAssociative());
}
