#pragma once

class DoubleStack {
public:
    DoubleStack();
    ~DoubleStack();

    void push(double value);
    double pop();
    double top() const;
    bool empty() const;
    size_t size() const;

private:
    void resize();

    double* array;
    size_t capacity;
    size_t currentSize;
};
