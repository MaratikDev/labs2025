#ifndef APPCONTEXT_H
#define APPCONTEXT_H

#define MAX_FILENAME_LENGTH 256
#define MAX_DATA_POINTS 1000
#define MAX_DATA_SIZE 100
#define EPS 0.00001

typedef struct {
    double x, y, z;
} Point3D;

typedef struct {
    double minVal;
    double maxVal;
    double normMin;
    double normMax;
    double step;
} SurfaceMetrics;

typedef struct {
    int rows;
    int cols;
    double data[MAX_DATA_SIZE][MAX_DATA_SIZE];
    Point3D normalizedData[MAX_DATA_SIZE][MAX_DATA_SIZE];
} SurfaceData;

typedef struct {
    double xAngle;
    double yAngle;
    double zAngle;
    double scale;
    double xTranslate;
    double yTranslate;
    double zTranslate;
} CameraSettings;

typedef struct {
    char filename[MAX_FILENAME_LENGTH];
    SurfaceData surface;
    SurfaceMetrics metrics;
    CameraSettings camera;
    int isDataLoaded;
    int isNormalized;
} AppContext;

typedef enum {
    Ok,
    MemoryFail,
    FileNotFound,
    WrongFormat,
    InvalidStep,
    InvalidNormalizationRange,
    NoDataLoaded
} ResultLogic;

#endif // APPCONTEXT_H
