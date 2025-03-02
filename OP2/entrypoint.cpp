#include "entrypoint.h"

void doOperation(Operation operation, AppContext* context, AppParams* params) {
    switch(operation) {
    case OpenFile:
        doOpenFile(context, params->filename);
        break;
    case LoadData:
        doLoadData(context);
        break;
    case CalculateMetrics:
        doCalculateMetrics(context, params->columnIndex, params->filterRegion);
        break;
    case Initialize:
        doInitialize(context);
        break;
    }//добавить инициализацию для контекста
}




