#include "BinaryFileResultStorage.h"
#include <fstream>
#include <stdexcept>
#include <cstdio>

BinaryFileResultStorage::BinaryFileResultStorage() {
    // Check if results.bin exists and delete it
    if (std::ifstream("results.bin")) {
        std::remove("results.bin");
    }
}

void BinaryFileResultStorage::saveResult(const Result& result) {
    std::ofstream outFile("results.bin", std::ios::binary | std::ios::app);

    if (!outFile) {
		throw std::runtime_error("Unable to create/read results file for storing expression values");
	}

	size_t expressionLength = result.expression.size();

	outFile.write(reinterpret_cast<const char*>(&expressionLength), sizeof(expressionLength));
	outFile.write(result.expression.c_str(), expressionLength);

	outFile.write(reinterpret_cast<const char*>(&result.value), sizeof(result.value));
	outFile.close();
}

std::vector<Result> BinaryFileResultStorage::loadResults() const {
    std::vector<Result> results;
    std::ifstream inFile("results.bin", std::ios::binary);
    if (!inFile) {
        throw std::runtime_error("Unable to open file for reading.");
    }

    while (inFile.peek() != EOF) {
        size_t expressionLength = 0;
        inFile.read(reinterpret_cast<char*>(&expressionLength), sizeof(expressionLength));
        std::string expression(expressionLength, ' ');
        inFile.read(&expression[0], expressionLength);
        double value = 0.0;
        inFile.read(reinterpret_cast<char*>(&value), sizeof(value));
        results.emplace_back(expression, value);
    }
    inFile.close();

    return results;
}