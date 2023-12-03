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

class NumberToken : public Token {
public:
    NumberToken(std::string value) : Token(TokenType::Number, std::move(value)) {}
};


class OperatorToken : public Token {
private:
    int precedence;
    bool isLeftAssociative;

    static const std::map<char, OperatorProperties>& getOperatorsMap() {
        static const std::map<char, OperatorProperties> operators = {
            {'+', {1, true}},
            {'-', {1, true}},
            {'*', {2, true}},
            {'/', {2, true}},
            {'^', {3, false}},
            {'=', {0, false}},  // equality
            {'#', {4, false}}   // root
        };
        return operators;
    }

public:
    OperatorToken(std::string value, int precedence, bool isLeftAssociative)
        : Token(TokenType::Operator, std::move(value)), precedence(precedence), isLeftAssociative(isLeftAssociative) {}

    int getPrecedence() const { return precedence; }
    bool getIsLeftAssociative() const { return isLeftAssociative; }

    static const OperatorProperties& getOperatorProperties(char op) {
		return getOperatorsMap().at(op);
	}

    static bool isValidOperator(char op) {
    
        // std::map.find()
        // Return Value: The function returns an iterator or a constant iterator which refers to the position where the key is present in the map. 
        // If the key is not present in the map container, it returns an iterator or a constant iterator which refers to map.end(). 
        return getOperatorsMap().find(op) != getOperatorsMap().end();
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