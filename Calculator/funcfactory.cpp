#include "funcfactory.h"
#include "commands.h"

Command* FuncFactory::createSqrt(double a) const { return new SqrtCommand(a); }
Command* FuncFactory::createSin(double a) const { return new SinCommand(a); }
Command* FuncFactory::createCos(double a) const { return new CosCommand(a); }
Command* FuncFactory::createTan(double a) const { return new TanCommand(a); }
Command* FuncFactory::createCot(double a) const { return new CotCommand(a); }
Command* FuncFactory::createInv(double a) const { return new InvCommand(a); }
