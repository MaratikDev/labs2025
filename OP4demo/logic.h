#ifndef LOGIC_H
#define LOGIC_H

#include "appcontext.h"



void doInitialize(AppContext* context);
void doOpenFile(AppContext* context, char* fileName);
ResultLogic doNormalizeData(AppContext* context, double step, double normMin, double normMax);
void doRotateCameraX(AppContext* context, double angle);
void doRotateCameraY(AppContext* context, double angle);
void doRotateCameraZ(AppContext* context, double angle);
void doTranslateCameraX(AppContext* context, double value);
void doTranslateCameraY(AppContext* context, double value);
void doTranslateCameraZ(AppContext* context, double value);
void doScaleCamera(AppContext* context, double scale);
void doResetCamera(AppContext* context);
ResultLogic loadDataFromCSV(AppContext* context);



#endif // LOGIC_H
