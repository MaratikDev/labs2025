#include "logic.h"

void doInitialize(AppContext* context){
    context->head = NULL;
    context->correctRows = 0;
    context->inCorrectRows = 0;
    context->totalRows = 0;
    context->columnCount = 0;
    context->columnName = NULL;
    context->min = 0;
    context->max = 0;
    context->median = 0;
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
    ResultLogic result = Success;
    context->min = 0;
    context->max = 0;
    context->median = 0;
    if (columnIndex < 3 || columnIndex > context->columnCount) {//отсчет идет с года, но если с года то columnIndex < 1 || columnIndex >= context->columnCount
        result = InsultColumn;
    }
    else{
        RowData* current = context->head;
        int count = 0;
        double* values = (double*)malloc(context->correctRows * sizeof(double));
        if (!values) {
            result = MemoryFail;
        }
        else{
            while (current != NULL) {
                if (strcmp(current->region, filterRegion) == 0) {
                    values[count] = current->metrics[columnIndex-3]; //тут тоже тогда поменять на -1
                    count++;
                }
                current = current->next;
            }
            if (count != 0) {
                qsort(values, count, sizeof(double), compareDouble);
                context->min = values[0];
                context->max = values[count - 1];
                context->median = (count % 2 == 0) ? (values[count / 2 - 1] + values[count / 2]) / 2 : values[count / 2];
            }
            else{
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
    if (arg1 < arg2)
        return -1;
    if (arg1 > arg2)
        return 1;
    return 0;
}

ResultLogic loadRowsFromCSV(AppContext* context, FILE* file, char* filterRegion) {
    ResultLogic result = Ok;
    RowData* tail = NULL;
    char line[1024];

    while (fgets(line, sizeof(line), file) && result == Ok) {
        context->totalRows++;
        RowData* newNode = (RowData*)malloc(sizeof(RowData));

        if (!newNode) {
            for (int i = 0; i < context->columnCount; i++) {
                free(context->columnName[i]);
            }
            free(context->columnName);
            result = MemoryFail;
            break;
        }
        else {
            int isCorrect = 1;
            char* token = strtok(line, ",");

            if (token) {
                newNode->year = atoi(token);
                token = strtok(NULL, ",");
            }
            else {
                context->inCorrectRows++;
                free(newNode);
                isCorrect = 0;
            }

            if (token && isCorrect) {
                strncpy(newNode->region, token, MAX_REGION_LENGTH - 1);
                newNode->region[MAX_REGION_LENGTH - 1] = '\0';
                if((strlen(filterRegion) != 0) && (strcmp(filterRegion,newNode->region) != 0)){
                    context->inCorrectRows++;
                    free(newNode);
                    isCorrect = 0;
                }
            }
            else if (isCorrect) {
                context->inCorrectRows++;
                free(newNode);
                isCorrect = 0;
            }

            if (isCorrect) {
                newNode->metrics = (double*)malloc((context->columnCount - 2) * sizeof(double));
                if (!newNode->metrics) {
                    result = MemoryFail;
                    free(newNode);
                    context->inCorrectRows++;
                }
                else {
                    for (int i = 0; i < context->columnCount - 2 && isCorrect; i++) {
                        token = strtok(NULL, ",");
                        if (token) {
                            newNode->metrics[i] = atof(token);
                        }
                        else {
                            context->inCorrectRows++;
                            free(newNode->metrics);
                            free(newNode);
                            isCorrect = 0;
                        }
                    }

                    if (isCorrect) {
                        newNode->next = NULL;
                        if (!context->head) {
                            context->head = newNode;
                        }
                        else {
                            tail->next = newNode;
                        }
                        tail = newNode;
                        context->correctRows++;
                    }
                }
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
        char line[1024];
        if (fgets(line, sizeof(line), file)) {
            char* token = strtok(line, ",");
            while (token != NULL && result == Ok) {
                char** newColumnName = (char**)realloc(context->columnName, (context->columnCount + 1) * sizeof(char*));
                if (!newColumnName) {
                    for (int i = 0; i < context->columnCount; i++) {
                        free(context->columnName[i]);
                    }
                    free(context->columnName);
                    result = MemoryFail;
                } else {
                    context->columnName = newColumnName;
                    context->columnName[context->columnCount] = (char*)malloc(256 * sizeof(char));
                    if (!context->columnName[context->columnCount]) {
                        for (int i = 0; i < context->columnCount; i++) {
                            free(context->columnName[i]);
                        }
                        free(context->columnName);
                        result = MemoryFail;
                    } else {
                        strncpy(context->columnName[context->columnCount], token, 255);
                        context->columnName[context->columnCount][255] = '\0';
                        context->columnCount++;
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
