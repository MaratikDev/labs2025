#include "commands.h"
#include <cmath>


double PlusCommand::execute(double a, double b) const {
    return a + b;
}
int PlusCommand::precedence() const {
    return 2;
}

double MinusCommand::execute(double a, double b) const {
    return a - b;
}
int MinusCommand::precedence() const {
    return 2;
}

double MultiplyCommand::execute(double a, double b) const {
    return a * b;
}
int MultiplyCommand::precedence() const {
    return 3;
}


double DivideCommand::execute(double a, double b) const {
    if (b == 0)
        throw InfinityProblem("Division by zero");
    return a / b;
}
int DivideCommand::precedence() const {
    return 3;
}


double SqrtCommand::execute(double a, double b) const {
    if (a < 0)
        throw NegativeSqrt("Square root of negative number");
    return sqrt(a);
}
int SqrtCommand::precedence() const {
    return 5;
}
bool SqrtCommand::isFunction() const{
    return true;
}


double SinCommand::execute(double a, double b) const {
    return sin(a);
}
int SinCommand::precedence() const {
    return 5;
}
bool SinCommand::isFunction() const {
    return true;
}


double CosCommand::execute(double a, double b) const {
    return cos(a);
}
int CosCommand::precedence() const {
    return 5;
}
bool CosCommand::isFunction() const {
    return true;
}


double TanCommand::execute(double a, double b) const {
    if (cos(a) == 0)
        throw InfinityProblem("Tan undefined");
    return tan(a);
}
int TanCommand::precedence() const {
    return 5;
}
bool TanCommand::isFunction() const {
    return true;
}


double CotCommand::execute(double a, double b) const {
    if (sin(a) == 0)
        throw InfinityProblem("Cot undefined");
    return 1.0 / tan(a);
}
int CotCommand::precedence() const {
    return 5;
}
bool CotCommand::isFunction() const {
    return true;
}


