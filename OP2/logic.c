#include "logic.h"

void doInitialize(AppContext* context){
    context->head = NULL;
    context->correctRows = 0;
    context->inCorrectRows = 0;
    context->totalRows = 0;
    context->columnCount = 0;
    context->columnName = NULL;
}
void doOpenFile(AppContext* context, char* fileName){
    strncpy(context->filename,fileName,MAX_FILENAME_LENGTH-1);
    context->filename[MAX_FILENAME_LENGTH - 1] = '\0';
}
void doLoadData(AppContext* context){
    if (!strlen(context->filename)) {
        return;
    }
    context->head = loadDataFromCSV(context);
}
void doCalculateMetrics(AppContext* context, int columnIndex, char* filterRegion){
    if (columnIndex < 0 || columnIndex >= context->columnCount) {           //если отсчет идет не с года, а с метрики то поставь < 2 к columnIndex
        return;
    }
    RowData* current = context->head;
    int count = 0;
    double* values = (double*)malloc(context->correctRows * sizeof(double));
    if (!values) {
        return;
    }
    while (current != NULL) {
        if (strcmp(current->region, filterRegion) == 0) {
            values[count] = current->metrics[columnIndex];
            count++;
        }
        current = current->next;
    }
    if (count == 0) {
        free(values);
        return;
    }

    qsort(values, count, sizeof(double), compareDouble);
    context->min = values[0];
    context->max = values[count - 1];
    context->median = (count % 2 == 0) ? (values[count / 2 - 1] + values[count / 2]) / 2 : values[count / 2];

    free(values);
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


RowData* loadDataFromCSV(AppContext* context){
    FILE* file = fopen(context->filename, "r");
    if (!file) {
        printf("Ошибка: не удалось открыть файл %s.\n", context->filename);
        return NULL;
    }

    char line[1024];
    RowData* tail = NULL;

    //названия столбцов
    if (fgets(line, sizeof(line), file)) {
        char* token = strtok(line, ",");
        while (token != NULL) {            
            char** newColumnName = (char**)realloc(context->columnName, (context->columnCount + 1) * sizeof(char*));
            if (!newColumnName) {
                printf("Ошибка: не удалось выделить память для названий столбцов.\n");                
                for (int i = 0; i < context->columnCount; i++) {
                    free(context->columnName[i]);
                }
                free(context->columnName);
                fclose(file);
                return NULL;
            }
            context->columnName = newColumnName;

            // Выделяем память для нового названия столбца
            context->columnName[context->columnCount] = (char*)malloc(256 * sizeof(char));
            if (!context->columnName[context->columnCount]) {
                printf("Ошибка: не удалось выделить память для названия столбца %d.\n", context->columnCount);
                for (int i = 0; i < context->columnCount; i++) {
                    free(context->columnName[i]);
                }
                free(context->columnName);
                fclose(file);
                return NULL;
            }


            strncpy(context->columnName[context->columnCount], token, 255);
            context->columnName[context->columnCount][255] = '\0';
            context->columnCount++;

            token = strtok(NULL, ",");
        }
    } else {
        printf("Ошибка: файл пуст или не удалось прочитать заголовок.\n");
        fclose(file);
        return NULL;
    }

    // Чтение данных из файла
    while (fgets(line, sizeof(line), file)) {
        context->totalRows++;
        RowData* newNode = (RowData*)malloc(sizeof(RowData));
        if (!newNode) {
            printf("Ошибка: не удалось выделить память для новой строки данных.\n");
            // Освобождаем память, выделенную для названий столбцов
            for (int i = 0; i < context->columnCount; i++) {
                free(context->columnName[i]);
            }
            free(context->columnName);
            fclose(file);
            return context->head;
        }
        int isCorrect = 1;

        // Парсинг строки
        char* token = strtok(line, ",");
        if (token) {
            newNode->year = atoi(token);
            token = strtok(NULL, ",");
            if (token) {
                strncpy(newNode->region, token, MAX_REGION_LENGTH - 1);
                newNode->region[MAX_REGION_LENGTH - 1] = '\0';
            } else {
                context->inCorrectRows++;
                free(newNode);
                isCorrect = 0;
            }

            newNode->metrics = (double*)malloc((context->columnCount - 2) * sizeof(double));
            if(!newNode->metrics){
                printf("Ошибка: не удалось выделить память для метрик.\n");
                free(newNode);
                context->inCorrectRows++;
                isCorrect = 0;
            }
            else{
                for (int i = 0; i < context->columnCount - 2; i++) {
                    token = strtok(NULL, ",");
                    if (token) {
                        newNode->metrics[i] = atof(token);
                    } else {
                        context->inCorrectRows++;
                        free(newNode);
                        isCorrect = 0;
                        break;
                    }
                }
            }

            if(isCorrect){
            newNode->next = NULL;
            if (!context->head) {
                context->head = newNode;
            } else {
                tail->next = newNode;
            }
            tail = newNode;
            context->correctRows++;
            }


        } else {
            context->inCorrectRows++;
            free(newNode);
        }
    }

           fclose(file);
           return context->head;
}
