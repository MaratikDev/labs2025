#include "logic.h"

void doInitialize(AppContext* context){
    context->head = NULL;
    context->filterRegion[0] = '\0';
    context->tableMetrics.correctRows = 0;
    context->tableMetrics.totalRows = 0;
    context->tableLogic.columnCount = 0;
    context->tableLogic.columnName = NULL;
    context->tableMetrics.min = 0;
    context->tableMetrics.max = 0;
    context->tableMetrics.median = 0;
}
void changeFilterRegion(AppContext* context, char* filterRegion){
    strncpy(context->filterRegion,filterRegion,MAX_REGION_LENGTH-1);
    context->filterRegion[MAX_REGION_LENGTH - 1] = '\0';
}
void doOpenFile(AppContext* context, char* fileName){
    strncpy(context->filename,fileName,MAX_FILENAME_LENGTH-1);
    context->filename[MAX_FILENAME_LENGTH - 1] = '\0';
}
ResultLogic doLoadData(AppContext* context, char* filterRegion){
    ResultLogic result = Ok;
    if (!strlen(context->filename)) {
        result = FileNotFound;
    }
    else{
    result = loadDataFromCSV(context, filterRegion);
    }
    return result;
}
ResultLogic doCalculateMetrics(AppContext* context, int columnIndex, char* filterRegion){
    ResultLogic result = SuccessMetricCalculated;
    context->tableMetrics.min = 0;
    context->tableMetrics.max = 0;
    context->tableMetrics.median = 0;

    if (columnIndex < 3 || columnIndex > context->tableLogic.columnCount) {
        result = InsultColumn;
    }
    else {
        RowData* current = context->head;
        int count = 0;
        char* endptr;
        double value;
        double* values = (double*)malloc(context->tableMetrics.correctRows * sizeof(double));
        if (!values) {
            result = MemoryFail;
        }
        else {
            while (current != NULL) {
                if (strcmp((char*)current->data[1], filterRegion) == 0) {
                    value = strtod(current->data[columnIndex-1],&endptr);// втррой параметр ссылка на оставшкюся часть строки кторую не удалось преобразовть
                    values[count] = value;
                    count++;

                }
                current = current->next;
            }
            if (count != 0) {
                qsort(values, count, sizeof(double), compareDouble);
                context->tableMetrics.min = values[0];
                context->tableMetrics.max = values[count - 1];
                context->tableMetrics.median = (count % 2 == 0) ? (values[count / 2 - 1] + values[count / 2]) / 2 : values[count / 2];
            }
            else {
                result = NoCorrectRows;
            }
            free(values);
        }
    }
    return result;
}
int compareDouble(const void* a, const void* b) {
    double arg1 = *(const double*)a;
    double arg2 = *(const double*)b;
    int result = 0;
    if (arg2 - arg1 > EPS)
        result = -1;
    if (arg1 - arg2 > EPS)
        result = 1;
    return result;
}

ResultLogic loadRowsFromCSV(AppContext* context, FILE* file, char* filterRegion) {
    ResultLogic result = Ok;
    RowData* tail = NULL;
    char line[MAX_SYMBOLS_IN_A_ROW];

    while (fgets(line, sizeof(line), file)) {
        context->tableMetrics.totalRows++;
        RowData* newNode = (RowData*)malloc(sizeof(RowData));

        if (!newNode) {
            for (int i = 0; i < context->tableLogic.columnCount; i++) {
                free(context->tableLogic.columnName[i]);
            }
            free(context->tableLogic.columnName);
            result = MemoryFail;
            break;
        }
        else {
            int isCorrect = 1;
            char* token = strtok(line, ",");

            // Выделяем память для массива data (char**)
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
                        free(newNode->data);
                        free(newNode);

                        isCorrect = 0;
                        break;
                    }
                    strcpy(newNode->data[column], token);
                    token = strtok(NULL, ",");
                    column++;
                }

                // Если строка некорректна (не хватает токенов), освобождаем память и пропускаем её
                if (column < context->tableLogic.columnCount) {
                    for (int i = 0; i < column; i++) {
                        free(newNode->data[i]);
                    }
                    free(newNode->data);
                    free(newNode);

                    isCorrect = 0;
                }
            }

            // Если строка корректна, добавляем её в список
            if (isCorrect && ((strcmp(filterRegion, newNode->data[REGION_INDEX]) == 0)||(strlen(filterRegion)==0)) ) {
                context->tableMetrics.correctRows++;
                newNode->next = NULL;
                if (!context->head) {
                    context->head = newNode;
                }
                else {
                    tail->next = newNode;
                }
                tail = newNode;

            }
        }
    }

           fclose(file);
           return result;

}

ResultLogic loadDataFromCSV(AppContext* context, char* filterRegion) {
    ResultLogic result = Ok;
    FILE* file = fopen(context->filename, "r");
    if (!file) {
        result = FileNotFound;
    } else {
        char line[MAX_SYMBOLS_IN_A_ROW];
        if (fgets(line, sizeof(line), file)) {
            char* token = strtok(line, ",");
            while (token != NULL && result == Ok) {
                char** newColumnName = (char**)realloc(context->tableLogic.columnName, (context->tableLogic.columnCount + 1) * sizeof(char*));
                if (!newColumnName) {
                    for (int i = 0; i < context->tableLogic.columnCount; i++) {
                        free(context->tableLogic.columnName[i]);
                    }
                    free(context->tableLogic.columnName);
                    result = MemoryFail;
                } else {
                    context->tableLogic.columnName = newColumnName;
                    context->tableLogic.columnName[context->tableLogic.columnCount] = (char*)malloc(MAX_NAME_LENGTH * sizeof(char));
                    if (!context->tableLogic.columnName[context->tableLogic.columnCount]) {
                        for (int i = 0; i < context->tableLogic.columnCount; i++) {
                            free(context->tableLogic.columnName[i]);
                        }
                        free(context->tableLogic.columnName);
                        result = MemoryFail;
                    } else {
                        strncpy(context->tableLogic.columnName[context->tableLogic.columnCount], token, MAX_NAME_LENGTH-1);
                        context->tableLogic.columnName[context->tableLogic.columnCount][MAX_NAME_LENGTH-1] = '\0';
                        context->tableLogic.columnCount++;
                        token = strtok(NULL, ",");
                    }
                }
            }
        } else {
            result = WrongFormat;
        }
    }

    if (result == Ok) {
        result = loadRowsFromCSV(context, file, filterRegion);
    }

    return result;
}


