#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <string>
#include "deikstra.h"

class Calculator {
public:
    Calculator();
    double evaluate(const std::string& expression) const;
private:
    Deikstra deikstra;
};

#endif // CALCULATOR_H
