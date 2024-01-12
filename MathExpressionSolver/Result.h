#pragma once
#include <string>

struct Result {
	std::string expression;
	double value;

	Result(const std::string& expr, double val) : expression(expr), value(val) {}
};