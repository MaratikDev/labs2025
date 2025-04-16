#include "logic.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

void doInitialize(AppContext* context)
{
    memset(context, 0, sizeof(AppContext));
    context->camera.scale = 1.0;
    context->isDataLoaded = 0;
    context->isNormalized = 0;
}

void doOpenFile(AppContext* context, char* fileName)
{
    strncpy(context->filename, fileName, MAX_FILENAME_LENGTH-1);
    context->filename[MAX_FILENAME_LENGTH-1] = '\0';
}

ResultLogic loadDataFromCSV(AppContext* context)
{
    FILE* file = fopen(context->filename, "r");
    if (!file) return FileNotFound;

    char line[1024];
    int row = 0;

    while (fgets(line, sizeof(line), file) && row < MAX_DATA_SIZE) {
        char* token = strtok(line, ",");
        int col = 0;

        while (token && col < MAX_DATA_SIZE) {
            context->surface.data[row][col] = atof(token);
            token = strtok(NULL, ",");
            col++;
        }

        if (row == 0) {
            context->surface.cols = col;
        } else if (col != context->surface.cols) {
            fclose(file);
            return WrongFormat;
        }

        row++;
    }

    context->surface.rows = row;
    context->isDataLoaded = 1;
    fclose(file);
    return Ok;
}

ResultLogic doNormalizeData(AppContext* context, double step, double normMin, double normMax)
{
    if (!context->isDataLoaded) return NoDataLoaded;
    if (step <= 0) return InvalidStep;
    if (normMin >= normMax) return InvalidNormalizationRange;

    double minVal = context->surface.data[0][0];
    double maxVal = context->surface.data[0][0];

    for (int i = 0; i < context->surface.rows; i++) {
        for (int j = 0; j < context->surface.cols; j++) {
            double val = context->surface.data[i][j];
            if (val < minVal) minVal = val;
            if (val > maxVal) maxVal = val;
        }
    }

    context->metrics.minVal = minVal;
    context->metrics.maxVal = maxVal;
    context->metrics.normMin = normMin;
    context->metrics.normMax = normMax;
    context->metrics.step = step;

    for (int i = 0; i < context->surface.rows; i++) {
        for (int j = 0; j < context->surface.cols; j++) {
            double val = context->surface.data[i][j];
            double normVal = normMin + ((val - minVal) * (normMax - normMin)) / (maxVal - minVal);

            context->surface.normalizedData[i][j].x = i * step;
            context->surface.normalizedData[i][j].y = j * step;
            context->surface.normalizedData[i][j].z = normVal;
        }
    }

    context->isNormalized = 1;
    return Ok;
}

void doRotateCameraX(AppContext* context, double angle)
{
    context->camera.xAngle = angle;
}

void doRotateCameraY(AppContext* context, double angle)
{
    context->camera.yAngle = angle;
}

void doRotateCameraZ(AppContext* context, double angle)
{
    context->camera.zAngle = angle;
}

void doTranslateCameraX(AppContext* context, double value)
{
    context->camera.xTranslate = value;
}

void doTranslateCameraY(AppContext* context, double value)
{
    context->camera.yTranslate = value;
}

void doTranslateCameraZ(AppContext* context, double value)
{
    context->camera.zTranslate = value;
}

void doScaleCamera(AppContext* context, double scale)
{
    context->camera.scale = scale;
}

void doResetCamera(AppContext* context)
{
    context->camera.xAngle = 0;
    context->camera.yAngle = 0;
    context->camera.zAngle = 0;
    context->camera.xTranslate = 0;
    context->camera.yTranslate = 0;
    context->camera.zTranslate = 0;
    context->camera.scale = 1.0;
}
