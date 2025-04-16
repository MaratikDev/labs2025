#ifndef COMMAND_FACTORY_H
#define COMMAND_FACTORY_H

#include "commands.h"

class CommandFactory {
public:
    typedef Command* (CommandFactory::*CommandCreator)(double, double) const;

    Command* createPlus(double a, double b) const;
    Command* createMinus(double a, double b) const;
    Command* createMultiply(double a, double b) const;
    Command* createDivide(double a, double b) const;
    Command* createSqrt(double a, double ) const;
    Command* createSin(double a, double ) const;
    Command* createCos(double a, double ) const;
    Command* createTan(double a, double ) const;
    Command* createCot(double a, double ) const;
    Command* createInv(double a, double ) const;
};

#endif // COMMAND_FACTORY_H
