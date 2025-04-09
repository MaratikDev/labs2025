#include "calculator.h"

Calculator::Calculator() {}

double Calculator::evaluate(const std::string& expression) const {
    return deikstra.evaluate(expression);
}

double Calculator::evalReciprocal(const std::string& expression) const {
    if(deikstra.evaluate(expression) != 0 )
        return 1.0/deikstra.evaluate(expression);
    throw InfinityProblem("Devision by zero");
}

