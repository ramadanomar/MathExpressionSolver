#include "EquationProcessor.h"
#include <stdexcept>

std::string EquationProcessor::rearrangeEquation(const std::pair<std::vector<Token*>, std::vector<Token*>>& equationParts) {
    auto left = equationParts.first;
    auto right = equationParts.second;

    moveTerms(left, right); // Move variable terms from left to right
    moveTerms(right, left); // Move number terms from right to left

    return tokensToString(left) + " = " + tokensToString(right);
}

void EquationProcessor::moveTerms(std::vector<Token*>& from, std::vector<Token*>& to) {
    Lexer lexer; 

    for (auto it = from.begin(); it != from.end(); ) {
        Token* token = *it;

        if (lexer.isVariableToken(token) || lexer.isNumberToken(token) || token->getType() == TokenType::Parenthesis) {
            // Semnele se schimba cand trecem de la o parte la alta a egalitatii
            if (it != from.begin()) {
                Token* prevToken = *(it - 1);
                if (prevToken->getType() == TokenType::Operator) {
                    std::string op = prevToken->getValue();
                    if (op == "+") op = "-";
                    else if (op == "-") op = "+";
                    else if (op == "*") op = "/";
                    else if (op == "/") op = "*";

                    to.push_back(new OperatorToken(op, OperatorToken::getOperatorProperties(op[0]).precedence, OperatorToken::getOperatorProperties(op[0]).isLeftAssociative));
                }
            }
            else {
                // Termenii fara semn sunt pozitivi
                to.push_back(new OperatorToken("+", OperatorToken::getOperatorProperties('+').precedence, OperatorToken::getOperatorProperties('+').isLeftAssociative));
            }

            // Consideram paranteza ca o singura unitate
            if (token->getType() == TokenType::Parenthesis && static_cast<ParenthesisToken*>(token)->getIsOpen()) {
                auto closeParenIt = std::find_if(it, from.end(), [](Token* t) {
                    return t->getType() == TokenType::Parenthesis && !static_cast<ParenthesisToken*>(t)->getIsOpen();
                    });

                if (closeParenIt == from.end()) {
                    throw std::runtime_error("Unmatched parentheses in expression");
                }

                // Extragem toti termenii din interiorul parantezelor
                std::vector<Token*> parentheticalExpression(it, closeParenIt + 1);
                // Apelam recursiv functia pentru a muta termenii din interiorul parantezelor
                std::vector<Token*> empty;
                moveTerms(parentheticalExpression, empty);

                // Add the modified block to 'to'
                to.insert(to.end(), parentheticalExpression.begin(), parentheticalExpression.end());

                // Erase the block from 'from'
                it = from.erase(it, closeParenIt + 1);
            }
            else {
                // Move the token to the 'to' vector
                to.push_back(token);
                it = from.erase(it);
            }
        }
        else {
            ++it;
        }
    }
}


std::string EquationProcessor::tokensToString(const std::vector<Token*>& tokens) {
    std::string result;
    for (const auto& token : tokens) {
        result += token->getValue();
    }
    return result;
}
