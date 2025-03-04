
#ifndef LOGIC_H
#define LOGIC_H

#include "appcontext.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>



#ifdef __cplusplus
    extern "C" {
#endif

    // Объявления функций
    void doOpenFile(AppContext* context, char* fileName);
    ResultLogic doLoadData(AppContext* context);
    ResultLogic doCalculateMetrics(AppContext* context, int columnIndex, char* filterRegion);
    void doInitialize(AppContext* context);
    ResultLogic loadDataFromCSV(AppContext* context);
    int compareDouble(const void* a, const void* b);
    ResultLogic loadRowsFromCSV(AppContext* context, FILE* file);
#ifdef __cplusplus
}
#endif

#endif // LOGIC_H
