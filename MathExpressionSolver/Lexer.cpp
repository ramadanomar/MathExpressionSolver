#include "Lexer.h"
#include <cctype>
#include <stdexcept>

std::vector<Token*> Lexer::tokenize(const std::string& input) {
    return tokenizeExpression(input);
}

std::vector<Token*> Lexer::tokenizeExpression(const std::string& expression) {
    std::vector<Token*> tokens;

    for (size_t i = 0; i < expression.length(); ++i) {
        char c = expression[i];

        if (isDigit(c) || (c == '.' && i + 1 < expression.length() && isDigit(expression[i + 1]))) {
            tokens.push_back(parseNumber(expression, i));
        }
        else if (OperatorToken::isValidOperator(c)) {
            tokens.push_back(createOperatorToken(c));
        }
        else if (c == '$') {
            if (i + 1 < expression.length() && isDigit(expression[i + 1])) {
                tokens.push_back(parseDollarVariable(expression, i));
            }
            else {
                throw std::runtime_error("Invalid usage of '$'. Expected digit after '$'."); // Nu cred ca putem prinde erorile cu cate ecuatii au fost rezolvate in faza de lexing
            }
        }
        // Variable nu am mai folosit tinand cont ca sunt singur in echipa si era cerinta doar de grup. De aia nu am folosit functia asta pt ecuatii deja rezolvate
        else if (isAlpha(c)) {
            tokens.push_back(parseVariable(expression, i));
        }
        else if (c == '(' || c == '[') {
            tokens.push_back(createParenthesisToken(c, true));
        }
        else if (c == ')' || c == ']') {
            tokens.push_back(createParenthesisToken(c, false));
        }
        else if (isSpace(c)) {
            continue;
        }
        else {
            throw std::runtime_error(std::string("Invalid char '") + c + "' in expression");
        }
    }

    return tokens;
}

Token* Lexer::parseNumber(const std::string& expression, size_t& index) {
    bool decimalPointEncountered = false;
    std::string numStr;

    for (; index < expression.length() && (isDigit(expression[index]) || expression[index] == '.'); ++index) {
        if (expression[index] == '.' && decimalPointEncountered) {
            throw std::runtime_error("Un numar introdus nu este valid. Contine mai multe puncte pt decimale");
        }
        if (expression[index] == '.') {
            decimalPointEncountered = true;
        }
        numStr += expression[index];
    }
    --index; // Necesar ca sa nu sarim peste un caracter la urmatoarea iteratie (din cauza incrementarii din for)

    return new NumberToken(numStr);
}

Token* Lexer::createOperatorToken(char c) {
    auto props = OperatorToken::getOperatorProperties(c);
    return new OperatorToken(std::string(1, c), props.precedence, props.isLeftAssociative);
}

Token* Lexer::parseVariable(const std::string& expression, size_t& index) {
    std::string varStr(1, expression[index]);
    while (++index < expression.length() && isAlpha(expression[index])) {
        varStr += expression[index];
    }
    --index; // Necesar ca sa nu sarim peste un caracter la urmatoarea iteratie (din cauza incrementarii din for)

    return new VariableToken(varStr);
}

Token* Lexer::parseDollarVariable(const std::string& expression, size_t& index) {
    std::string varStr(1, expression[index]); // Start with '$'
    while (++index < expression.length() && isDigit(expression[index])) {
        varStr += expression[index];
    }
    --index;

    return new DollarVariableToken(varStr);
}

Token* Lexer::createParenthesisToken(char c, bool isOpen) {
    return new ParenthesisToken(std::string(1, c), isOpen);
}

bool Lexer::isDigit(char c) const {
    return std::isdigit(static_cast<unsigned char>(c));
}

bool Lexer::isAlpha(char c) const {
    return std::isalpha(static_cast<unsigned char>(c));
}

bool Lexer::isSpace(char c) const {
    return std::isspace(static_cast<unsigned char>(c));
}
