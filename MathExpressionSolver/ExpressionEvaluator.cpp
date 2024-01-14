#include "ExpressionEvaluator.h"

#include "Token.h"
#include <stdexcept>
#include <cmath>

double ExpressionEvaluator::evaluate(const std::vector<Token*>& tokens, std::function<double(int)> getResult) {
    std::stack<double> valueStack;

    for (const auto& token : tokens) {
        if (token->getType() == TokenType::Number) {
            valueStack.push(std::stod(token->getValue()));
        }
        else if (token->getType() == TokenType::DollarVariable) {
            int eqIndex = std::stoi(token->getValue().substr(1)); // $1 -> 1 etc. (string to int skipping the $)

            // fetch actual from cache/storage
            double result = getResult(eqIndex);
            valueStack.push(result);
        }
        else if (token->getType() == TokenType::Operator) {
            if (valueStack.size() < 2) {
                throw std::runtime_error("Invalid RPN expression");
            }
            double b = valueStack.top(); valueStack.pop();
            double a = valueStack.top(); valueStack.pop();
            valueStack.push(applyOperation(a, b, token->getValue()));
        }
    }

    if (valueStack.size() != 1) {
        throw std::runtime_error("Invalid RPN expression");
    }

    return valueStack.top();
}

double ExpressionEvaluator::applyOperation(double a, double b, const std::string& op) {
    if (op.length() != 1 || !OperatorToken::isValidOperator(op[0])) {
        throw std::runtime_error("Unsupported operator: " + op);
    }

    char opChar = op[0];
    if (opChar == '+') {
        return a + b;
    }
    else if (opChar == '-') {
        return a - b;
    }
    else if (opChar == '*') {
        return a * b;
    }
    else if (opChar == '/') {
        if (b == 0) throw std::runtime_error("Division by zero");
        return a / b;
    }
    else if (opChar == '^') {
        return std::pow(a, b);
    }
    else if (opChar == '#') {
        if (a < 0 && std::fmod(b, 2) != 1) {
            throw std::runtime_error("Invalid operation: root of a negative number");
        }
        return std::pow(a, 1.0 / b); // y-th root of x
    }
    else {
        throw std::runtime_error("Unsupported operator: " + op);
    }
}