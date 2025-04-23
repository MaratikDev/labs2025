#include "surfacewidget.h"
#include <QPainter>
#include <cmath>

SurfaceWidget::SurfaceWidget(QWidget *parent) : QWidget(parent), context(nullptr)
{
    setMinimumSize(WIDGET_SIZE, WIDGET_SIZE);
}

void SurfaceWidget::setContext(AppContext* context)
{
    this->context = context;
    update();
}

//все что ниже закоменчено, это я еще не знал что нужно как матрицы считать поворт точки

//M-PI это типо число пи
/*QPoint SurfaceWidget::project3DTo2D(double x, double y, double z)
{
    double scale = context->camera.scale;
    double distance = DISTANCE;
//пи это типо как в математике 180 градусов
//поэтому мы берем angle/180 что б получить насколько мы поернулись и перевести все в еденичную окрпужность домоножив на пи
// одним словом: переводим в радианы
    double xRot = context->camera.xAngle * M_PI / PI_RADIAN;
    double yRot = context->camera.yAngle * M_PI / PI_RADIAN;
    double zRot = context->camera.zAngle * M_PI / PI_RADIAN;
    double x1;
    double y1;
    double z1;
//X
    y1 = y * cos(xRot) - z * sin(xRot);
    z1 = y * sin(xRot) + z * cos(xRot);
    y = y1;
    z = z1;

//Y
    x1 = x * cos(yRot) + z * sin(yRot);
    z1 = -x * sin(yRot) + z * cos(yRot);
    x = x1;
    z = z1;
//Z
    x1 = x * cos(zRot) - y * sin(zRot);
    y1 = x * sin(zRot) + y * cos(zRot);
    x = x1; y = y1;

    x += context->camera.xTranslate;
    y += context->camera.yTranslate;
    z += context->camera.zTranslate;

//тупейший factor: чтоб когда елозили по Z оно типо приближалось/отдалялось (я это подсмторел)
    double factor = distance / (distance + z);
    int px = width() / 2 + (x * factor * scale);
    int py = height() / 2 - (y * factor * scale);

    return QPoint(px, py);
}*/

QPoint SurfaceWidget::project3DTo2D(double x, double y, double z)
{
    Matrix4x4 rotationMatrix = {{
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    }};

    double xRad = context->camera.xAngle * M_PI / PI_RADIAN;
    double yRad = context->camera.yAngle * M_PI / PI_RADIAN;
    double zRad = context->camera.zAngle * M_PI / PI_RADIAN;

    //  X
    Matrix4x4 rotX = {{
        {1, 0, 0, 0},
        {0, cos(xRad), -sin(xRad), 0},
        {0, sin(xRad), cos(xRad), 0},
        {0, 0, 0, 1}
    }};
    rotationMatrix = multiplyMatrices(rotationMatrix, rotX);

    //  Y
    Matrix4x4 rotY = {{
        {cos(yRad), 0, sin(yRad), 0},
        {0, 1, 0, 0},
        {-sin(yRad), 0, cos(yRad), 0},
        {0, 0, 0, 1}
    }};
    rotationMatrix = multiplyMatrices(rotationMatrix, rotY);

    //  Z
    Matrix4x4 rotZ = {{
        {cos(zRad), -sin(zRad), 0, 0},
        {sin(zRad), cos(zRad), 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    }};
    rotationMatrix = multiplyMatrices(rotationMatrix, rotZ);

    //перемножаем точку на матрицу
    double point[COUNT_OF_DIRECTIONS] = {x, y, z, 1};
    double rotatedPoint[COUNT_OF_DIRECTIONS];
    multiplyMatrixVector(rotationMatrix, point, rotatedPoint);


    double scale = context->camera.scale;
    double distance = DISTANCE;

    double tx = rotatedPoint[0] + context->camera.xTranslate;
    double ty = rotatedPoint[1] + context->camera.yTranslate;
    double tz = rotatedPoint[2] + context->camera.zTranslate;

    double factor = distance / (distance + tz);
    int px = width() / 2 + (tx * factor * scale);
    int py = height() / 2 - (ty * factor * scale);


    return QPoint(px, py);
}

//координаты
void SurfaceWidget::drawAxes(QPainter &painter)
{
    painter.setPen(QPen(Qt::red, 2));
    QPoint origin = project3DTo2D(0, 0, 0);
    QPoint xEnd = project3DTo2D(1, 0, 0);
    painter.drawLine(origin, xEnd);

    painter.setPen(QPen(Qt::green, 2));
    QPoint yEnd = project3DTo2D(0, 1, 0);
    painter.drawLine(origin, yEnd);

    painter.setPen(QPen(Qt::blue, 2));
    QPoint zEnd = project3DTo2D(0, 0, 1);
    painter.drawLine(origin, zEnd);
}

void SurfaceWidget::drawSurface(QPainter &painter)
{
    if (!context->isNormalized)
        return;

    painter.setPen(QPen(Qt::blue, 1));

    //чтоб получить сетку надо сначала соединять линии по Y, а потом по X(1й цикл: вертикальные 2й цикл:горизонтальные)

    for (int i = 0; i < context->surface.rows; i++) {
        QPoint prevPoint;
        bool first = true;

        for (int j = 0; j < context->surface.cols; j++) {
            Point3D p = context->surface.normalizedData[i][j];
            QPoint currentPoint = project3DTo2D(p.x, p.y, p.z);

            if (!first) {
                painter.drawLine(prevPoint, currentPoint);
            }
            prevPoint = currentPoint;
            first = false;
        }
    }

    for (int j = 0; j < context->surface.cols; j++) {
        QPoint prevPoint;
        bool first = true;

        for (int i = 0; i < context->surface.rows; i++) {
            Point3D p = context->surface.normalizedData[i][j];
            QPoint currentPoint = project3DTo2D(p.x, p.y, p.z);

            if (!first) {
                painter.drawLine(prevPoint, currentPoint);
            }
            prevPoint = currentPoint;
            first = false;
        }
    }
}

void SurfaceWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.fillRect(rect(), Qt::white);

    if (!context || !context->isDataLoaded) return;

    drawAxes(painter);
    drawSurface(painter);
}






Matrix4x4 SurfaceWidget::multiplyMatrices(const Matrix4x4 &a, const Matrix4x4 &b)
{
    Matrix4x4 result = {{{0}}};

    for (int i = 0; i < COUNT_OF_DIRECTIONS; ++i) {
        for (int j = 0; j < COUNT_OF_DIRECTIONS; ++j) {
            for (int k = 0; k < COUNT_OF_DIRECTIONS; ++k) {
                result.m[i][j] += a.m[i][k] * b.m[k][j];
            }
        }
    }

    return result;
}

void SurfaceWidget::multiplyMatrixVector(const Matrix4x4 &m, const double v[COUNT_OF_DIRECTIONS], double result[COUNT_OF_DIRECTIONS])
{
    for (int i = 0; i < COUNT_OF_DIRECTIONS; ++i) {
        result[i] = 0;
        for (int j = 0; j < COUNT_OF_DIRECTIONS; ++j) {
            result[i] += m.m[i][j] * v[j];
        }
    }
}
