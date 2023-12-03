#include "EquationHandler.h"
#include <iostream>

int main() {
    EquationHandler equationHandler;
    std::string inputEquation = "7x+390 = 23x * 12";

    try {
        std::string result = equationHandler.processEquation(inputEquation);
        std::cout << "Processed Equation: " << result << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
