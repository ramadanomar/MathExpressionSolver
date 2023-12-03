#pragma once

#include "Token.h"

class Stack {
public:
    Stack();
    ~Stack();

    void push(Token* value);
    Token* pop();
    Token* top() const;
    bool empty() const;
    size_t size() const;

private:
    void resize();

    Token** array;
    size_t capacity;
    size_t currentSize;
};
