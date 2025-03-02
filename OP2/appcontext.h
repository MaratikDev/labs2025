#ifndef APPCONTEXT_H
#define APPCONTEXT_H
#define MAX_REGION_LENGTH 100
#define MAX_FILENAME_LENGTH 256
// Структура, описывающая контекст приложения.
// Включает переменные, описывающие состояние компонентов интерфейса,
// изменяемые в основной (бизнес) логике приложения.
typedef struct RowData{
    int year;
    char region[MAX_REGION_LENGTH];
    double* metrics;
    struct RowData *next;
}RowData;

typedef struct {
    char filename[MAX_FILENAME_LENGTH];
    RowData* head;
    int totalRows;
    int correctRows;
    int inCorrectRows;
    int currentRow;
    double min;
    double max;
    double median;
    int columnCount;
    char** columnName;
}AppContext;

typedef enum {
    Ok,
    MemoryFail,
    FileNotFound,
    WrongFormat,
}ResultError;

#endif // APPCONTEXT_H
