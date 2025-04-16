#include "entrypoint.h"
#include "logic.h"

ResultLogic doOperation(enum Operation operation, AppContext* context, AppParams* params)
{
    switch(operation) {
    case Initialize:
        doInitialize(context);
        break;
    case OpenFile:
        doOpenFile(context, params->filename);
        return loadDataFromCSV(context);
    case NormalizeData:
        return doNormalizeData(context, params->step, params->normMin, params->normMax);
    case RotateCameraX:
        doRotateCameraX(context, params->angle);
        break;
    case RotateCameraY:
        doRotateCameraY(context, params->angle);
        break;
    case RotateCameraZ:
        doRotateCameraZ(context, params->angle);
        break;
    case TranslateCameraX:
        doTranslateCameraX(context, params->translation);
        break;
    case TranslateCameraY:
        doTranslateCameraY(context, params->translation);
        break;
    case TranslateCameraZ:
        doTranslateCameraZ(context, params->translation);
        break;
    case ScaleCamera:
        doScaleCamera(context, params->scale);
        break;
    case ResetCamera:
        doResetCamera(context);
        break;
    }
    return Ok;
}
