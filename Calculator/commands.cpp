#include "commands.h"
#include <cmath>

PlusCommand::PlusCommand(double a, double b) : a(a), b(b) {}
double PlusCommand::execute() const { return a + b; }
int PlusCommand::precedence() const { return 2; }

MinusCommand::MinusCommand(double a, double b) : a(a), b(b) {}
double MinusCommand::execute() const { return a - b; }
int MinusCommand::precedence() const { return 2; }

MultiplyCommand::MultiplyCommand(double a, double b) : a(a), b(b) {}
double MultiplyCommand::execute() const { return a * b; }
int MultiplyCommand::precedence() const { return 3; }

DivideCommand::DivideCommand(double a, double b) : a(a), b(b) {}
double DivideCommand::execute() const {
    if (b == 0) throw InfinityProblem("Division by zero");
    return a / b;
}
int DivideCommand::precedence() const { return 3; }

SqrtCommand::SqrtCommand(double a) : a(a) {}
double SqrtCommand::execute() const {
    if (a < 0) throw NegativeSqrt("Square root of negative number");
    return sqrt(a);
}
int SqrtCommand::precedence() const { return 5; }
bool SqrtCommand::isFunction() const { return true; }

SinCommand::SinCommand(double a) : a(a) {}
double SinCommand::execute() const { return sin(a); }
int SinCommand::precedence() const { return 5; }
bool SinCommand::isFunction() const { return true; }

CosCommand::CosCommand(double a) : a(a) {}
double CosCommand::execute() const { return cos(a); }
int CosCommand::precedence() const { return 5; }
bool CosCommand::isFunction() const { return true; }

TanCommand::TanCommand(double a) : a(a) {}
double TanCommand::execute() const {
    if (cos(a) == 0) throw InfinityProblem("Tan undefined");
    return tan(a);
}
int TanCommand::precedence() const { return 5; }
bool TanCommand::isFunction() const { return true; }

CotCommand::CotCommand(double a) : a(a) {}
double CotCommand::execute() const {
    if (sin(a) == 0) throw InfinityProblem("Cot undefined");
    return 1.0 / tan(a);
}
int CotCommand::precedence() const { return 5; }
bool CotCommand::isFunction() const { return true; }

InvCommand::InvCommand(double a) : a(a) {}
double InvCommand::execute() const {
    if (a == 0) throw InfinityProblem("Division by 0");
    return 1.0 / a;
}
int InvCommand::precedence() const { return 5; }
bool InvCommand::isFunction() const { return true; }
