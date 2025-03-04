#include "entrypoint.h"

ResultLogic doOperation(Operation operation, AppContext* context, AppParams* params) {
    ResultLogic result = Ok;
    switch(operation) {
    case OpenFile:
        doOpenFile(context, params->filename);
        break;
    case LoadData:
        result = doLoadData(context);
        break;
    case CalculateMetrics:
        result = doCalculateMetrics(context, params->columnIndex, params->filterRegion);
        break;
    case Initialize:
        doInitialize(context);
        break;
    }
    return result;//добавить инициализацию для контекста
}




