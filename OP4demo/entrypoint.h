#ifndef ENTRYPOINT_H
#define ENTRYPOINT_H

#include "appcontext.h"

enum Operation {
    Initialize,
    OpenFile,
    NormalizeData,
    RotateCameraX,
    RotateCameraY,
    RotateCameraZ,
    TranslateCameraX,
    TranslateCameraY,
    TranslateCameraZ,
    ScaleCamera,
    ResetCamera
};

typedef struct {
    char filename[MAX_FILENAME_LENGTH];
    double step;
    double normMin;
    double normMax;
    double angle;
    double translation;
    double scale;
} AppParams;

ResultLogic doOperation(enum Operation operation, AppContext* context, AppParams* params);

#endif // ENTRYPOINT_H
