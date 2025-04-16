#include "factoryCommand.h"
#include "commands.h"

Command* CommandFactory::createPlus(double a, double b) const { return new PlusCommand(a, b); }
Command* CommandFactory::createMinus(double a, double b) const { return new MinusCommand(a, b); }
Command* CommandFactory::createMultiply(double a, double b) const { return new MultiplyCommand(a, b); }
Command* CommandFactory::createDivide(double a, double b) const { return new DivideCommand(a, b); }

Command* CommandFactory::createSqrt(double a, double) const { return new SqrtCommand(a); }
Command* CommandFactory::createSin(double a, double) const { return new SinCommand(a); }
Command* CommandFactory::createCos(double a, double) const { return new CosCommand(a); }
Command* CommandFactory::createTan(double a, double) const { return new TanCommand(a); }
Command* CommandFactory::createCot(double a, double) const { return new CotCommand(a); }
Command* CommandFactory::createInv(double a, double) const { return new InvCommand(a); }
