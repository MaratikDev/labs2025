#include "RowData.h"

void freeRowData(RowData* newNode) {
    free(newNode->data);
    free(newNode);
}

void addElement(RowData* head, RowData* newNode) {
    if (head == NULL || newNode == NULL) {
        return;
    }
    else{
        newNode->next = NULL;
        head->next = newNode;
    }
}
