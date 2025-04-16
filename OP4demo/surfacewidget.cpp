#include "surfacewidget.h"
#include <QPainter>
#include <cmath>

SurfaceWidget::SurfaceWidget(QWidget *parent) : QWidget(parent), context(nullptr)
{
    setMinimumSize(400, 400);
}

void SurfaceWidget::setContext(AppContext* context)
{
    this->context = context;
    update();
}

QPoint SurfaceWidget::project3DTo2D(double x, double y, double z)
{
    double scale = context->camera.scale;
    double distance = 5.0;

    double xRot = context->camera.xAngle * M_PI / 180.0;
    double yRot = context->camera.yAngle * M_PI / 180.0;
    double zRot = context->camera.zAngle * M_PI / 180.0;

    double y1 = y * cos(xRot) - z * sin(xRot);
    double z1 = y * sin(xRot) + z * cos(xRot);
    y = y1; z = z1;

    double x1 = x * cos(yRot) + z * sin(yRot);
    z1 = -x * sin(yRot) + z * cos(yRot);
    x = x1; z = z1;

    x1 = x * cos(zRot) - y * sin(zRot);
    y1 = x * sin(zRot) + y * cos(zRot);
    x = x1; y = y1;

    x += context->camera.xTranslate;
    y += context->camera.yTranslate;
    z += context->camera.zTranslate;

    double factor = distance / (distance + z);
    int px = width() / 2 + (x * factor * scale * 50);
    int py = height() / 2 - (y * factor * scale * 50);

    return QPoint(px, py);
}

void SurfaceWidget::drawAxes(QPainter &painter)
{
    painter.setPen(QPen(Qt::red, 2));
    QPoint origin = project3DTo2D(0, 0, 0);
    QPoint xEnd = project3DTo2D(2, 0, 0);
    painter.drawLine(origin, xEnd);

    painter.setPen(QPen(Qt::green, 2));
    QPoint yEnd = project3DTo2D(0, 2, 0);
    painter.drawLine(origin, yEnd);

    painter.setPen(QPen(Qt::blue, 2));
    QPoint zEnd = project3DTo2D(0, 0, 2);
    painter.drawLine(origin, zEnd);
}

void SurfaceWidget::drawSurface(QPainter &painter)
{
    if (!context->isNormalized) return;

    painter.setPen(QPen(Qt::blue, 1));

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
