#ifndef ENTRYPOINT_H
#define ENTRYPOINT_H

#include "appcontext.h"
#include "logic.h"

// Перечисляемый тип (enum) и структуры описываются существительными
// Операции, описывающие действия, выполняемые в (бизнес) логике приложения
enum Operation {
    OpenFile,
    LoadData,
    CalculateMetrics,
    Initialize,
    SaveFilterRegion
};

// Структура, описывающая дополнительные поля-значения, необходимые для выполнения операции
typedef struct {
    char filename[MAX_FILENAME_LENGTH];
    int columnIndex;
    char filterRegion[MAX_REGION_LENGTH];
} AppParams;

// Единая точа входа - метод, являющийся прослойкой между слоем представления (Presentation)
// и слоем (бизнес) логики приложения.
ResultLogic doOperation(Operation operation, AppContext* context, AppParams* params);



#endif // ENTRYPOINT_H
