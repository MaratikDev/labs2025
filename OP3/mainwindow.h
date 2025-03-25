#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "appcontext.h"
#include "entrypoint.h"
#include "graph.h"

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
    Graph *graphWidget;

    // Действия, выполняемые по нажатиям на кнопки интерфейса
    void onOpenFileButtonClicked();
    void onLoadDataButtonClicked();
    void onCalculateMetricsButtonClicked();
    void updateLabels();
    void initialize();
    std::map<ResultLogic, char*> errorMessages;
    std::string convertErrorToString(ResultLogic result, std::map<ResultLogic, char*>& errorMessages);
    void showErrorMessage(ResultLogic result);
    void refreshTable();
    void regionChanged();
    void updateGraph(int columnIndex);
};
#endif // MAINWINDOW_H
