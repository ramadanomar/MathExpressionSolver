#pragma once

#include <string>

class Menu {
public:
    void run();
    void evaluateExpression(const std::string& expression);
    double calculateExpression(const std::string& expression);
};