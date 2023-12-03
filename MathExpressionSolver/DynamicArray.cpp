#include "DynamicArray.h"
#include <stdexcept> 

DynamicArray::DynamicArray() : array(nullptr), capacity(0), currentSize(0) {}

DynamicArray::~DynamicArray() {
    delete[] array;
}

void DynamicArray::push_back(Token* value) {
    if (currentSize == capacity) {
        resize();
    }
    array[currentSize++] = value;
}

Token* DynamicArray::at(size_t index) const {
    if (index >= currentSize) {
        throw std::out_of_range("Index out of range");
    }
    return array[index];
}

size_t DynamicArray::size() const {
    return currentSize;
}

bool DynamicArray::empty() const {
    return currentSize == 0;
}

void DynamicArray::resize() {
    size_t newCapacity = (capacity == 0) ? 1 : capacity * 2;
    Token** newArray = new Token * [newCapacity];

    for (size_t i = 0; i < currentSize; i++) {
        // Nu va face buffer overrun pentru ca newCapacity > capacity
        newArray[i] = array[i];
    }

    // Deleting the old array
    delete[] array;

    array = newArray;
    capacity = newCapacity;
}