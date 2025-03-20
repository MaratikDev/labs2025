#include "entrypoint.h"

ResultLogic doOperation(Operation operation, AppContext* context, AppParams* params) {
    ResultLogic result = Ok;
    switch(operation) {
    case OpenFile:
        doOpenFile(context, params->filename);
        break;
    case LoadData:
        result = doLoadData(context, params->filterRegion);
        break;
    case CalculateMetrics:
        result = doCalculateMetrics(context, params->columnIndex, params->filterRegion);
        break;
    case Initialize:
        doInitialize(context);
        break;
    case SaveFilterRegion:
        changeFilterRegion(context, params->filterRegion);
    }

    return result;//добавить инициализацию для контекста
}




