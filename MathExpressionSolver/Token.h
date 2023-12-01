#pragma once

#include <string>
#include <map>

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

class OperatorToken : public Token {
private:
    int precedence;
    bool isLeftAssociative;

public:
    OperatorToken(std::string value, int precedence, bool isLeftAssociative)
        : Token(TokenType::Operator, std::move(value)), precedence(precedence), isLeftAssociative(isLeftAssociative) {}

    int getPrecedence() const { return precedence; }
    bool getIsLeftAssociative() const { return isLeftAssociative; }

    static const OperatorProperties& getProperties(char op) {
        static const std::map<char, OperatorProperties> operators = {
            {'+', {1, true}},
            {'-', {1, true}},
            {'*', {2, true}},
            {'/', {2, true}},
            {'^', {3, false}},
            {'=', {0, false}},  // equality
            {'#', {4, false}}   // sqrt
        };

        return operators.at(op);
    }
};


class ParenthesisToken : public Token {
private:
    bool isOpen;

public:
    ParenthesisToken(std::string value, bool isOpen)
        : Token(TokenType::Parenthesis, std::move(value)), isOpen(isOpen) {}

    bool getIsOpen() const { return isOpen; }
};