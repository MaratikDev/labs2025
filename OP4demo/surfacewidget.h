#ifndef SURFACEWIDGET_H
#define SURFACEWIDGET_H

#include <QWidget>
#include "appcontext.h"

class SurfaceWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SurfaceWidget(QWidget *parent = nullptr);
    void setContext(AppContext* context);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    AppContext* context;
    QPoint project3DTo2D(double x, double y, double z);
    void drawAxes(QPainter &painter);
    void drawSurface(QPainter &painter);
    Matrix4x4 multiplyMatrices(const Matrix4x4 &a, const Matrix4x4 &b);
    void multiplyMatrixVector(const Matrix4x4 &m, const double v[4], double result[4]);
};

#endif // SURFACEWIDGET_H
