#pragma once

#include <string>
#include <iostream>

class Menu {
public:
    void run();
    void evaluateExpression(const std::string& expression);
    double calculateExpression(const std::string& expression);
    void evaluateExpressionToFile(const std::string& expression, std::ostream& outputStream);
};
