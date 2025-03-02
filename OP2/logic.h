
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
    void doLoadData(AppContext* context);
    void doCalculateMetrics(AppContext* context, int columnIndex, char* filterRegion);
    void doInitialize(AppContext* context);
    RowData* loadDataFromCSV(AppContext* context);
    int compareDouble(const void* a, const void* b);

#ifdef __cplusplus
}
#endif

#endif // LOGIC_H
