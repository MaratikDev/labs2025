#include "logic.h"

void doInitialize(AppContext* context){
    context->tableLogic.head = NULL;
    context->filterRegion[0] = '\0';
    context->tableLogic.correctRows = 0;
    context->tableLogic.totalRows = 0;
    context->tableLogic.columnCount = 0;
    context->tableLogic.columnName = NULL;
    context->tableMetrics.min = 0;
    context->tableMetrics.max = 0;
    context->tableMetrics.median = 0;
    context->tableMetrics.minYear = MAX_YEAR;
    context->tableMetrics.maxYear = 0;
    context->tableMetrics.sumX = 0;
    context->tableMetrics.sumY = 0;
    context->tableMetrics.sumXY = 0;
    context->tableMetrics.sumsquareX = 0;
    context->tableMetrics.coefB0 = 0;
    context->tableMetrics.coefB1 = 0;

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
    context->tableMetrics.minYear = MAX_YEAR;
    context->tableMetrics.avgMetric = 0;
    context->tableMetrics.coefB0 = 0;
    context->tableMetrics.coefB1 = 0;
    context->tableMetrics.sumX = 0;
    context->tableMetrics.sumXY = 0;
    context->tableMetrics.sumY = 0;
    context->tableMetrics.sumsquareX = 0;


    if (columnIndex < 1 || columnIndex > context->tableLogic.columnCount) {
        result = InsultColumn;
    }
    else {
        RowData* current = context->tableLogic.head;
        int count = 0;
        char* endptr;
        double value;
        int year;
        double* values = (double*)malloc(context->tableLogic.correctRows * sizeof(double));
        if (!values) {
            result = MemoryFail;
        }
        else {
            while (current != NULL) {
                if ((strcmp((char*)current->data[1], filterRegion) == 0) || (strlen(filterRegion)==0)) {
                    year = strtod(current->data[0],&endptr);
                    value = strtod(current->data[columnIndex-1],&endptr);// втррой параметр ссылка на оставшкюся часть строки кторую не удалось преобразовть
                    if(endptr != current->data[columnIndex-1]){
                        values[count] = value;
                        count++;
                        context->tableMetrics.avgMetric += value;
                        context->tableMetrics.sumX += year;
                        context->tableMetrics.sumY += value;
                        context->tableMetrics.sumsquareX += year*year;
                        context->tableMetrics.sumXY += value*year;
                        if (year<context->tableMetrics.minYear){
                            context->tableMetrics.minYear = year;
                        }
                        if(year>context->tableMetrics.maxYear){
                            context->tableMetrics.maxYear = year;
                        }
                    }
                }
                current = current->next;
            }
            if (count != 0) {
                qsort(values, count, sizeof(double), compareDouble);
                context->tableMetrics.min = values[0];
                context->tableMetrics.max = values[count - 1];
                context->tableMetrics.median = (count % 2 == 0) ? (values[count / 2 - 1] + values[count / 2]) / 2 : values[count / 2];
                context->tableMetrics.avgMetric /= count;
                context->tableMetrics.coefB0 = ((count*context->tableMetrics.sumXY) - (context->tableMetrics.sumX * context->tableMetrics.sumY))/
                                               ((count*context->tableMetrics.sumsquareX) - context->tableMetrics.sumX * context->tableMetrics.sumX);
                context->tableMetrics.coefB1 = (context->tableMetrics.sumY - context->tableMetrics.coefB0 * context->tableMetrics.sumX) / count;
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
        result = addElement(context, filterRegion, &tail, line);
        if(result != Ok)
            break;
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
            char* token = strtok(line, COMMA);
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
                        token = strtok(NULL, COMMA);
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


