#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <map>
#include "appcontext.h"
#include "entrypoint.h"
#include "surfacewidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onOpenFileButtonClicked();
    void onNormalizeButtonClicked();
    void onXRotateSliderChanged(int value);
    void onYRotateSliderChanged(int value);
    void onZRotateSliderChanged(int value);
    void onXTranslateSliderChanged(int value);
    void onYTranslateSliderChanged(int value);
    void onZTranslateSliderChanged(int value);
    void onScaleSliderChanged(int value);
    void onResetCameraButtonClicked();

private:
    Ui::MainWindow *ui;
    AppContext context;
    SurfaceWidget *surfaceWidget;
    std::map<ResultLogic, QString> errorMessages;
    void initialize();
    void showErrorMessage(ResultLogic result);
};

#endif // MAINWINDOW_H
