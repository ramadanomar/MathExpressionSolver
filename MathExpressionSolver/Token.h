#pragma once

#include <string>
#include <stdexcept>

enum class TokenType {
    Number,
    Operator,
    Variable,
    Parenthesis
};

struct OperatorProperties {
    int precedence;
    bool isLeftAssociative;
};

class Token {
private:
    TokenType type;
    std::string value;

public:
    Token(TokenType type, std::string value) : type(type), value(std::move(value)) {}
    virtual ~Token() = default;

    TokenType getType() const { return type; }
    const std::string& getValue() const { return value; }
};

class NumberToken : public Token {
public:
    NumberToken(std::string value) : Token(TokenType::Number, std::move(value)) {}
};


class OperatorToken : public Token {
private:
    int precedence;
    bool isLeftAssociative;

    static OperatorProperties _getOperatorProperties(char op) {
        switch (op) {
        case '+': return { 1, true };
        case '-': return { 1, true };
        case '*': return { 2, true };
        case '/': return { 2, true };
        case '^': return { 3, false };
        case '=': return { 0, false };  // equality
        case '#': return { 4, false };  // root
        default: throw std::invalid_argument("Invalid operator");
        }
    }

public:
    OperatorToken(std::string value, int precedence, bool isLeftAssociative)
        : Token(TokenType::Operator, std::move(value)), precedence(precedence), isLeftAssociative(isLeftAssociative) {}
    
    static OperatorProperties getOperatorProperties(char op) {
		return _getOperatorProperties(op);
	}

    int getPrecedence() const { return precedence; }
    bool getIsLeftAssociative() const { return isLeftAssociative; }

    static bool isValidOperator(char op) {
        switch (op) {
        case '+':
        case '-':
        case '*':
        case '/':
        case '^':
        case '=':
        case '#':
            return true;
        default:
            return false;
        }
    }
};

class VariableToken : public Token {
public:
    VariableToken(std::string value) : Token(TokenType::Variable, std::move(value)) {}
};


class ParenthesisToken : public Token {
private:
    bool isOpen;

public:
    ParenthesisToken(std::string value, bool isOpen)
        : Token(TokenType::Parenthesis, std::move(value)), isOpen(isOpen) {}

    bool getIsOpen() const { return isOpen; }
};