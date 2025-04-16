#ifndef FUNCFACTORY_H
#define FUNCFACTORY_H

#include "commands.h"

class FuncFactory {
public:
    typedef Command* (FuncFactory::*FuncCreator)(double) const;

    Command* createSqrt(double a) const;
    Command* createSin(double a) const;
    Command* createCos(double a) const;
    Command* createTan(double a) const;
    Command* createCot(double a) const;
    Command* createInv(double a) const;
};

#endif // FUNCFACTORY_H
