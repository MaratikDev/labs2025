#ifndef OPERATIONFACTORY_H
#define OPERATIONFACTORY_H

#include "commands.h"

class OperationFactory {
public:
    typedef Command* (OperationFactory::*OpCreator)(double, double) const;

    Command* createPlus(double a, double b) const;
    Command* createMinus(double a, double b) const;
    Command* createMultiply(double a, double b) const;
    Command* createDivide(double a, double b) const;
};

#endif // OPERATIONFACTORY_H
