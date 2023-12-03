#include "DoubleStack.h"
#include <stdexcept>

DoubleStack::DoubleStack() : array(nullptr), capacity(0), currentSize(0) {}

DoubleStack::~DoubleStack() {
    delete[] array;
}

void DoubleStack::push(double value) {
    if (currentSize == capacity) {
        resize();
    }
    array[currentSize++] = value;
}

double DoubleStack::pop() {
    if (empty()) {
        throw std::runtime_error("Pop operation on an empty stack");
    }
    return array[--currentSize];
}

double DoubleStack::top() const {
    if (empty()) {
        throw std::runtime_error("Top operation on an empty stack");
    }
    return array[currentSize - 1];
}

bool DoubleStack::empty() const {
    return currentSize == 0;
}

size_t DoubleStack::size() const {
    return currentSize;
}

void DoubleStack::resize() {
    size_t newCapacity = (capacity == 0) ? 1 : capacity * 2;
    double* newArray = new double[newCapacity];

    for (size_t i = 0; i < currentSize; ++i) {
        newArray[i] = array[i];
    }

    delete[] array;
    array = newArray;
    capacity = newCapacity;
}
