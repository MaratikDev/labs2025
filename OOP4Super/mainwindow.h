#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include "facade.h"
#include "qtscenedrawer.h"
#include "scenedrawerbase.h"

#define DEFAULT_STEP 1
#define DEFAULT_MIN 0
#define DEFAULT_MAX 1
#define DEFAULT_SCALE 100
#define RADIAN 180
#define DEFAULT_COEF 50
#define DEFAULT_VAL 0
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();




private:
    void openFile();
    void normalizeData();
    void rotateScene();
    void translateScene();
    void scaleScene();
    void resetCamera();
    Ui::MainWindow *ui;
    Facade* facade;
    QString currentFilePath;
};

#endif // MAINWINDOW_H
