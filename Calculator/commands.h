#ifndef COMMANDS_H
#define COMMANDS_H

#include <stdexcept>
#include <cmath>
#include "exceptions.h"

class Command {
public:
    virtual ~Command() = default;
    virtual double execute() const = 0;
    virtual int precedence() const = 0;
    virtual bool isFunction() const { return false; }
};

class PlusCommand : public Command {
    double a, b;
public:
    PlusCommand(double a, double b);
    double execute() const override;
    int precedence() const override;
};

class MinusCommand : public Command {
    double a, b;
public:
    MinusCommand(double a, double b);
    double execute() const override;
    int precedence() const override;
};

class MultiplyCommand : public Command {
    double a, b;
public:
    MultiplyCommand(double a, double b);
    double execute() const override;
    int precedence() const override;
};

class DivideCommand : public Command {
    double a, b;
public:
    DivideCommand(double a, double b);
    double execute() const override;
    int precedence() const override;
};

class SqrtCommand : public Command {
    double a;
public:
    SqrtCommand(double a);
    double execute() const override;
    int precedence() const override;
    bool isFunction() const override;
};

class SinCommand : public Command {
    double a;
public:
    SinCommand(double a);
    double execute() const override;
    int precedence() const override;
    bool isFunction() const override;
};

class CosCommand : public Command {
    double a;
public:
    CosCommand(double a);
    double execute() const override;
    int precedence() const override;
    bool isFunction() const override;
};

class TanCommand : public Command {
    double a;
public:
    TanCommand(double a);
    double execute() const override;
    int precedence() const override;
    bool isFunction() const override;
};

class CotCommand : public Command {
    double a;
public:
    CotCommand(double a);
    double execute() const override;
    int precedence() const override;
    bool isFunction() const override;
};

class InvCommand : public Command {
    double a;
public:
    InvCommand(double a);
    double execute() const override;
    int precedence() const override;
    bool isFunction() const override;
};

#endif // COMMANDS_H
