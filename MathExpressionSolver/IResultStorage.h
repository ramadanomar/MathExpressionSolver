#pragma once
#include "Result.h"
#include <vector>

class IResultStorage {
public:
    virtual void saveResult(const Result& result) = 0;
    virtual std::vector<Result> loadResults() const = 0;
    virtual bool hasResult(int index) const = 0; // Ensure this matches the derived class
    virtual double getResult(int index) const = 0; // Ensure this matches the derived class
    virtual ~IResultStorage() = default;
};
