#pragma once
#include "IResultStorage.h"
#include "Result.h"
#include <vector>

class BinaryFileResultStorage : public IResultStorage {
private:
    mutable std::vector<Result> results;  // In-memory cache

    void loadFromFile() const;  // Helper method for loading results from file

public:
    BinaryFileResultStorage();
    void saveResult(const Result& result) override;
    std::vector<Result> loadResults() const override;
    bool hasResult(int index) const override;
    double getResult(int index) const override;
};
