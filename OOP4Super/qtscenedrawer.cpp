#include "qtscenedrawer.h"
#include <QPainter>

QtSceneDrawer::QtSceneDrawer(QWidget *parent) :
    QWidget(parent)
{

    setMinimumSize(WIDGET_SIZE, WIDGET_SIZE);
}
void QtSceneDrawer::drawScene(Scene scene) {
    currentScene = scene;
    update();
}


QPoint QtSceneDrawer::project3D(point3D p) {

    const float distance = DISTANCE;
    const float scale = SCALE;


    float f = distance / (distance + p.z);
    if (f<0.0001)
        f = 0.0001;
    const int x = width()/2 + (scale * f * p.x);
    const int y = height()/2 - (scale * f * p.y);
    //qDebug()<<x;
    //qDebug()<<y;

    return QPoint(x, y);
}

void QtSceneDrawer::paintEvent(QPaintEvent* event) {
    Q_UNUSED(event);
    QPainter painter(this);
    painter.fillRect(rect(), Qt::white);
    int count = 0;

    if (!currentScene.getFigures().empty()) {
        for (auto& figure : currentScene.getFigures()) {
            switch(count){
            case 0:
                painter.setPen(QPen(Qt::red, 2));
                break;
            case 1:
                painter.setPen(QPen(Qt::green, 2));
                break;
            case 2:
                painter.setPen(QPen(Qt::blue, 2));
                break;
            default:
                painter.setPen(QPen(Qt::blue, 1));
                break;
            }

            for (auto& edge : figure.getEdges()) {
                point3D p1 = edge.getBegin().getPosition();
                point3D p2 = edge.getEnd().getPosition();
                //qDebug()<<p1.x;
                //qDebug()<<p2.x;
                QPoint point1 = project3D(p1);
                QPoint point2 = project3D(p2);

                painter.drawLine(point1, point2);
            }
            count++;
        }
    }
}
