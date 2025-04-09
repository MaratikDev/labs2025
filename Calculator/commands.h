#ifndef COMMANDS_H
#define COMMANDS_H

#include <memory>
#include <string>
#include <stdexcept>
#include "exceptions.h"

class Command {
public:
    virtual ~Command() = default;
    virtual double execute(double a, double b = 0) const = 0;
    virtual int precedence() const = 0;
    virtual bool isFunction() const {
        return false;
    }
};

class PlusCommand : public Command {
public:
    double execute(double a, double b) const override;
    int precedence() const override;
};

class MinusCommand : public Command {
public:
    double execute(double a, double b) const override;
    int precedence() const override;
};

class MultiplyCommand : public Command {
public:
    double execute(double a, double b) const override;
    int precedence() const override;
};

class DivideCommand : public Command {
public:
    double execute(double a, double b) const override;
    int precedence() const override;
};

class SqrtCommand : public Command {
public:
    double execute(double a, double b) const override;
    int precedence() const override;
    bool isFunction() const override;
};

class SinCommand : public Command {
public:
    double execute(double a, double b) const override;
    int precedence() const override;
    bool isFunction() const override;
};

class CosCommand : public Command {
public:
    double execute(double a, double b) const override;
    int precedence() const override;
    bool isFunction() const override;
};

class TanCommand : public Command {
public:
    double execute(double a, double b) const override;
    int precedence() const override;
    bool isFunction() const override;
};

class CotCommand : public Command {
public:
    double execute(double a, double b) const override;
    int precedence() const override;
    bool isFunction() const override;
};


#endif // COMMANDS_H
