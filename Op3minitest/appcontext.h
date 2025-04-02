#ifndef APPCONTEXT_H
#define APPCONTEXT_H
#define MAX_REGION_LENGTH 100
#define MAX_FILENAME_LENGTH 256
#define EPS 0.00001
#define REGION_INDEX 1
#define MAX_SYMBOLS_IN_A_ROW 1024
#define MAX_NAME_LENGTH 256
#define COMMA ","
#define MAX_YEAR 9999

// Структура, описывающая контекст приложения.
// Включает переменные, описывающие состояние компонентов интерфейса,
// изменяемые в основной (бизнес) логике приложения.



struct RowData;

typedef struct TableMetrics{
    double min;
    double max;
    double median;
    int minYear; // это нужно для графика
    int maxYear;
    int avgMetric; // int что б красивее было

    double sumX;
    double sumY;
    double sumsquareX;
    double sumXY;
    double coefB0;
    double coefB1;
}TableMetrics;

typedef struct TableLogic{
    int columnCount;
    char** columnName;
    int totalRows;
    int correctRows;
    struct RowData* head;
}TableLogic;

typedef struct {
    char filename[MAX_FILENAME_LENGTH];
    char filterRegion[MAX_REGION_LENGTH];
    TableMetrics tableMetrics;
    TableLogic tableLogic;
}AppContext;

typedef enum {
    Ok,
    MemoryFail,
    FileNotFound,
    WrongFormat,
    SuccessMetricCalculated,
    InsultColumn,
    NoCorrectRows
}ResultLogic;

#endif // APPCONTEXT_H
