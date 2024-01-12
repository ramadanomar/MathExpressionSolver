#include "Menu.h"
#include "RegexFileValidator.h"
#include "AlwaysValidFileValidator.h"

#include "BinaryFileResultStorage.h"

#include <fstream>
#include <iostream>
#include <map>

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

int main(int argc, char* argv[]) {
    RegexFileValidator validator;
    // AlwaysValidFileValidator validator;
    BinaryFileResultStorage storage;

    Menu menu(&validator, &storage);
    auto args = parseArgs(argc, argv);

    std::ifstream inputFile;
    if (args.find("-i") != args.end()) {
        if (!validator.isValid(args["-i"])) {
            std::cerr << "Invalid input file name." << std::endl;
            return 1;
        }
        inputFile.open(args["-i"]);
        if (!inputFile.is_open()) {
            std::cerr << "Failed to open input file." << std::endl;
            return 1;
        }
    }

    std::ofstream outputFile;
    std::ostream* outputStream = &std::cout;
    if (args.find("-o") != args.end()) {
        if (!validator.isValid(args["-o"])) {
            std::cerr << "Invalid output file name." << std::endl;
            return 1;
        }
        outputFile.open(args["-o"]);
        if (!outputFile.is_open()) {
            std::cerr << "Failed to create output file." << std::endl;
            return 1;
        }
        outputStream = &outputFile;
    }

    if (inputFile.is_open()) {
        std::string line;
        while (std::getline(inputFile, line)) {
            menu.evaluateExpressionToFile(line, *outputStream);
        }
    }
    else {
        menu.run();
    }

    return 0;
}
