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
    }
    return result;
}


