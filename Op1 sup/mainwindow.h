#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "appcontext.h"
#include "entrypoint.h"
#include <map>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    // Конструктор класса - вызывается при создании экземпляра класса
    MainWindow(QWidget *parent = nullptr);
    // Дестркутор - вызывается при уничтожении класса
    ~MainWindow();

private:
    // Указатель на объекты интерфейса
    Ui::MainWindow *ui;
    // Структура, храняющая состояние приложения
    AppContext context;

    // Действия, выполняемые по нажатиям на кнопки интерфейса
    void onConvertValueClicked();
    void onCopyClicked();
    void updateLabels();

    void handleOk();
    void handleOutOfFourBytes();
    void handleWrongSystem();
    void handleUnacceptableNumber();
    void handleEmpty();
    std::map<enum ResultLogic, std::function<void()>> methodsOfErrorsMap;
};
#endif // MAINWINDOW_H
