#ifndef QTSCENEDRAWER_H
#define QTSCENEDRAWER_H

#include <QWidget>
#include "scenedrawerbase.h"
#include "scene.h"
#define WIDGET_SIZE 400
#define DISTANCE 500
#define SCALE 20

class QtSceneDrawer : public QWidget, public SceneDrawerBase
{
    Q_OBJECT

public:
    explicit QtSceneDrawer(QWidget *parent = nullptr);
    virtual ~QtSceneDrawer() = default;
    QPoint project3D(point3D p);
    void drawScene(Scene scene) override;

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    Scene currentScene;
};

#endif // QTSCENEDRAWER_H
