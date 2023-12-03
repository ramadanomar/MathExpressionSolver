#include "Lexer.h"
#include <cctype>
#include <stdexcept>
#include <vector>


// TREBUIE SA DEALOCAM TOKENURILE DUPA CE LE FOLOSIM ALTFEL AVEM MEMORY LEAKS
std::vector<Token*> Lexer::tokenize(const std::string& input) {
    std::vector<Token*> tokens;

    for (size_t i = 0; i < input.length(); ++i) {
        char c = input[i];

        // Nu folosim switch ca avem un caracter (trb sa facem un case pt fiecare caracter) si e mai greu de citit
        if (isDigit(c) || (c == '.' && i + 1 < input.length() && isDigit(input[i + 1]))) {
            // Citirea numerelor (inclusiv numere cu .)
            std::string numStr(1, c);
            while (i + 1 < input.length() && (isDigit(input[i + 1]) || input[i + 1] == '.')) {
                numStr += input[++i];
            }
            tokens.push_back(new NumberToken(numStr));
        }
        else if (OperatorToken::isValidOperator(c)) {
            // Operatori
            auto props = OperatorToken::getOperatorProperties(c);
            tokens.push_back(new OperatorToken(std::string(1, c), props.precedence, props.isLeftAssociative));
        }
        else if (isAlpha(c)) {
            // Variabile
            // TODO: Singleton ca sa nu rezolv ecuatii cu mai multe necunoscute (deocamdata)
            std::string varStr(1, c);
            while (i + 1 < input.length() && isAlpha(input[i + 1])) {
                varStr += input[++i];
            }
            tokens.push_back(new VariableToken(varStr));
        }
        else if (c == '(' || c == '[') {
            // Pt precedenta, shunting foloseste doar paranteze rotunde dar pot fi mai multe paranteze deschise deci e ok (cred)
            tokens.push_back(new ParenthesisToken(std::string(1, c), true));
        }
        else if (c == ')' || c == ']') {
            tokens.push_back(new ParenthesisToken(std::string(1, c), false));
        }
        else if (std::isspace(c)) {
            // Ignoram spatiile
            continue;
        }
        else {
            // nu e niciunul din cele de mai sus
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
