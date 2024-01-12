#include "Menu.h"
#include <fstream>
#include <iostream>
#include <map>
#include <regex>

constexpr int OUTPUT_PRECISION = 4;


std::map<std::string, std::string> parseArgs(int argc, char* argv[]) {
    std::map<std::string, std::string> args;
    for (int i = 1; i < argc; i += 2) {
        std::string arg = argv[i];
        if (arg == "-i" || arg == "-o") {
            if (i + 1 < argc) {
                args[arg] = argv[i + 1];
            }
        }
    }
    return args;
}

bool isValidFileName(const std::string& filename) {
    return true;
}

//// Regex found here: https://regexpattern.com/valid-filename/
//bool isValidFileName(const std::string& filename) {
//    std::regex pattern("/^[a-zA-Z0-9](?:[a-zA-Z0-9 ._-]*[a-zA-Z0-9])?\.[a-zA-Z0-9_-]+$/");
//    return std::regex_match(filename, pattern);
//}

int main(int argc, char* argv[]) {
    Menu menu;
    auto args = parseArgs(argc, argv);

    // Input file handling
    std::ifstream inputFile;
    if (args.find("-i") != args.end()) {
        if (!isValidFileName(args["-i"])) {
            std::cerr << "Invalid input file name." << std::endl;
            return 1;
        }
        inputFile.open(args["-i"]);
        if (!inputFile.is_open()) {
            std::cerr << "Failed to open input file." << std::endl;
            return 1;
        }
    }

    // Output file handling
    std::ofstream outputFile;
    std::ostream* outputStream = &std::cout;
    if (args.find("-o") != args.end()) {
        std::string outputFileName = args["-o"];
        if (outputFileName.find('.') == std::string::npos) {
            outputFileName += ".txt"; // Assume .txt extension if none is provided
        }
        if (!isValidFileName(outputFileName)) {
            std::cerr << "Invalid output file name." << std::endl;
            return 1;
        }
        outputFile.open(outputFileName);
        if (!outputFile.is_open()) {
            std::cerr << "Failed to create output file." << std::endl;
            return 1;
        }
        outputStream = &outputFile;
    }

    // Processing
    if (inputFile.is_open()) {
        std::string line;
        while (std::getline(inputFile, line)) {
            menu.evaluateExpressionToFile(line, *outputStream);
        }
    }
    else {
        bool expressionProvided = false;
        for (int i = 1; i < argc && !expressionProvided; i++) {
            if (argv[i][0] != '-') {
                expressionProvided = true;
            }
        }

        if (expressionProvided) {
            std::string expression;
            for (int i = 1; i < argc; i++) {
                if (std::string(argv[i]) == "-o") break;
                if (i > 1) expression += " ";
                expression += argv[i];
            }
            menu.evaluateExpressionToFile(expression, *outputStream);
        }
        else {
            // Meniul Original (Partea 1)
            menu.run();
        }
    }

    return 0;
}