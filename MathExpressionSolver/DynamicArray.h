#pragma once

#include "Token.h"

class DynamicArray {
public:
    DynamicArray();
    ~DynamicArray();

    void push_back(Token* value);
    Token* at(size_t index) const;
    size_t size() const;
    bool empty() const;

    Token** begin() { return array; }
    Token** end() { return array + currentSize; }

    const Token* const* begin() const { return array; }
    const Token* const* end() const { return array + currentSize; }

private:
    void resize();

    Token** array;
    size_t capacity;
    size_t currentSize;
};