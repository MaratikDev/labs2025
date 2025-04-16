#include "operationfactory.h"
#include "commands.h"

Command* OperationFactory::createPlus(double a, double b) const { return new PlusCommand(a, b); }
Command* OperationFactory::createMinus(double a, double b) const { return new MinusCommand(a, b); }
Command* OperationFactory::createMultiply(double a, double b) const { return new MultiplyCommand(a, b); }
Command* OperationFactory::createDivide(double a, double b) const { return new DivideCommand(a, b); }
