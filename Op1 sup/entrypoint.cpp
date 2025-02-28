#include "entrypoint.h"


ResultLogic doOperation(Operation operation, AppContext* context, AppParams* params) {
    ResultLogic result = Ok;
    switch(operation) {
    case Convert:
        result = convert(context, params->inputValue, params->inputSystem, params->outputSystem);
        break;
    case Initialization:
        initialize(context);
        result = Ok;
        break;
    case SaveInputValue:
        saveInputValue(context, params->inputValue);
        break;
    case SaveInputSystem:
        saveInputSystem(context, params->inputSystem);
        break;
    case SaveOutputSystem:
        saveOutputSystem(context, params->outputSystem);
        break;
    case ChangeValues:
        changeValues(context);
        break;
    }

    return result;
}


