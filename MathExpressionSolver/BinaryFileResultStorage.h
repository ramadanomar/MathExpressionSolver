#pragma once
#pragma once
#include "IResultStorage.h"

class BinaryFileResultStorage : public IResultStorage {
public:
    BinaryFileResultStorage();
    void saveResult(const Result& result) override;
    std::vector<Result> loadResults() const override;
};
