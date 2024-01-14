#include "BinaryFileResultStorage.h"
#include <fstream>
#include <stdexcept>
#include <cstdio>

BinaryFileResultStorage::BinaryFileResultStorage() {
    // Delete the existing results file (if it exists) to start fresh
    const char* filename = "results.bin";
    if (std::ifstream(filename)) {
        std::remove(filename);
    }

    // Clear any in-memory results cache (Might not be necessary but just to be safe)
    results.clear();
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

    results.push_back(result);  // Cache the result in memory
}

std::vector<Result> BinaryFileResultStorage::loadResults() const {
    return results;  // Return the in-memory cache of results
}

void BinaryFileResultStorage::loadFromFile() const {
    std::ifstream inFile("results.bin", std::ios::binary);
    if (!inFile) {
        return;  // If the file doesn't exist, just return
    }

    results.clear();  // Purge in-memory cache of results

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
}

bool BinaryFileResultStorage::hasResult(int index) const {
    return index >= 0 && static_cast<size_t>(index) < results.size();
}

double BinaryFileResultStorage::getResult(int index) const {
    if (!hasResult(index)) {
        throw std::runtime_error("Result not found for index: " + std::to_string(index));
    }
    return results[index].value;
}
