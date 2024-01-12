#pragma once
#pragma once
#include "Result.h"
#include <vector>

class IResultStorage {
public:
    virtual void saveResult(const Result& result) = 0;
    virtual std::vector<Result> loadResults() const = 0;
    virtual ~IResultStorage() = default;
};
