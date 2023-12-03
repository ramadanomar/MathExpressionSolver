#include "ShuntingYard.h"
#include "DynamicArray.h"
#include "Stack.h"
#include <stdexcept>

DynamicArray ShuntingYard::infixToPostfix(DynamicArray& infixTokens) {
    Stack operatorStack;
    DynamicArray postfixTokens;

    for (const auto& token : infixTokens) {
        if (token->getType() == TokenType::Number || token->getType() == TokenType::Variable) {
            postfixTokens.push_back(token);
        }
        else if (isOperator(token)) {
            while (!operatorStack.empty() && isHigherPrecedence(static_cast<OperatorToken*>(operatorStack.top()), static_cast<OperatorToken*>(token))) {
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
                while (!operatorStack.empty() && operatorStack.top()->getType() != TokenType::Parenthesis) {
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

    while (!operatorStack.empty()) {
        if (operatorStack.top()->getType() == TokenType::Parenthesis) {
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
