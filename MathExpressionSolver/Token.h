#pragma once

#include <string>
#include <stdexcept>
#include <unordered_map>

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
	explicit Token(TokenType type, std::string value): type(type), value(std::move(value)) {}
	virtual ~Token() = default;

	TokenType getType() const { return type; }
	const std::string& getValue() const { return value; }
};

class NumberToken : public Token {
public:
	explicit NumberToken(std::string value) : Token(TokenType::Number, std::move(value)) {}
};


class OperatorToken : public Token {
private:
	int precedence;
	bool isLeftAssociative;

	static const std::unordered_map<char, OperatorProperties>& getOperatorPropertiesMap() {
		static const std::unordered_map<char, OperatorProperties> operator_properties = {
			{'+', {1, true}},
			{'-', {1, true}},
			{'*', {2, true}},
			{'/', {2, true}},
			{'^', {3, false}},
			{'=', {0, false}},
			{'#', {4, false}}
		};
		return operator_properties;
	}

public:
	OperatorToken(std::string value, int precedence, bool isLeftAssociative)
		: Token(TokenType::Operator, std::move(value)), precedence(precedence), isLeftAssociative(isLeftAssociative) {}

	static OperatorProperties getOperatorProperties(char op) {
		const auto& properties_map = getOperatorPropertiesMap();
		auto it = properties_map.find(op);
		if (it != properties_map.end()) {
			return it->second;
		}
		throw std::invalid_argument("Invalid operator read: " + std::string(1,op));
	}

	int getPrecedence() const { return precedence; }
	bool getIsLeftAssociative() const { return isLeftAssociative; }

	static bool isValidOperator(char op) {
		const auto& properties_map = getOperatorPropertiesMap();
		return properties_map.find(op) != properties_map.end();
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