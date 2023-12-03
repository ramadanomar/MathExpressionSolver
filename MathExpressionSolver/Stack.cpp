#include "Stack.h"
#include <stdexcept>

Stack::Stack() : array(nullptr), capacity(0), currentSize(0) {}

Stack::~Stack() {
    delete[] array;
}

void Stack::push(Token* value) {
    if (currentSize == capacity) {
        resize();
    }
    array[currentSize++] = value;
}

Token* Stack::pop() {
    if (empty()) {
        throw std::runtime_error("Pop operation on an empty stack");
    }
    return array[--currentSize];
}

Token* Stack::top() const {
    if (empty()) {
        throw std::runtime_error("Top operation on an empty stack");
    }
    return array[currentSize - 1];
}

bool Stack::empty() const {
    return currentSize == 0;
}

size_t Stack::size() const {
    return currentSize;
}

void Stack::resize() {
    size_t newCapacity = (capacity == 0) ? 1 : capacity * 2;
    Token** newArray = new Token * [newCapacity];

    for (size_t i = 0; i < currentSize; ++i) {
        newArray[i] = array[i];
    }

    delete[] array;
    array = newArray;
    capacity = newCapacity;
}
