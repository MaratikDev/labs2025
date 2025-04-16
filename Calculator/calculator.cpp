#include "calculator.h"

Calculator::Calculator() {}

double Calculator::evaluate(const std::string& expression) const {
    return deikstra.evaluate(expression);
}


