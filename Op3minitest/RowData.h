#ifndef ROWDATA_H
#define ROWDATA_H

#include "appcontext.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct RowData {
    void** data;
    struct RowData* next;
} RowData;

void freeRowData(RowData* newNode);
ResultLogic addElement(AppContext *context, char* filterRegion, RowData** tail, char* line);

#endif // ROWDATA_H
