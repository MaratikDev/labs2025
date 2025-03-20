#ifndef ROWDATA_H
#define ROWDATA_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct RowData {
    void** data;
    struct RowData* next;
} RowData;

void freeRowData(RowData* newNode);
void addElement(RowData* row, RowData* newNode);

#endif // ROWDATA_H
