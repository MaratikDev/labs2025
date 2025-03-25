#include "RowData.h"


void freeRowData(RowData* newNode) {
    free(newNode->data);
    free(newNode);
}

ResultLogic addElement(AppContext* context, char* filterRegion, RowData** tail, char* line) {
    ResultLogic result = Ok;

        context->tableLogic.totalRows++;
        RowData* newNode = (RowData*)malloc(sizeof(RowData));

        if (!newNode) {
            for (int i = 0; i < context->tableLogic.columnCount; i++) {
                free(context->tableLogic.columnName[i]);
            }
            free(context->tableLogic.columnName);
            result = MemoryFail;
            return result;
        }
        else {
            int isCorrect = 1;
            char* token = strtok(line, COMMA);
            newNode->data = (void**)malloc(context->tableLogic.columnCount * sizeof(void*));
            if (!newNode->data) {
                result = MemoryFail;
                free(newNode);

                isCorrect = 0;
            }
            else {
                int column = 0;

                // Обрабатываем каждый токен в строке
                while (token != NULL && column < context->tableLogic.columnCount) {
                    newNode->data[column] = (char*)malloc((strlen(token) + 1) * sizeof(char));
                    if (!newNode->data[column]) {
                        result = MemoryFail;
                        for (int i = 0; i < column; i++) {
                            free(newNode->data[i]);
                        }
                        freeRowData(newNode);

                        isCorrect = 0;
                        break;
                    }
                    strcpy(newNode->data[column], token);
                    token = strtok(NULL, COMMA);
                    column++;
                }


                if (column < context->tableLogic.columnCount) {
                    for (int i = 0; i < column; i++) {
                        free(newNode->data[i]);
                    }
                    freeRowData(newNode);

                    isCorrect = 0;
                }
            }

            if (isCorrect && ((strcmp(filterRegion, newNode->data[REGION_INDEX]) == 0)||(strlen(filterRegion)==0)) ) {
                context->tableLogic.correctRows++;
                newNode->next = NULL;
                if (!context->tableLogic.head) {
                    context->tableLogic.head = newNode;
                }
                else {
                    newNode->next = NULL;
                    (*tail)->next = newNode;
                }
                *tail = newNode;
            }
        }
        return result;
}
