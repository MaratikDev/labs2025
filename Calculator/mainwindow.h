#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "calculator.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private:
    Ui::MainWindow *ui;
    bool previousEqual;
    Calculator calculator;
    void onDigitClicked();
    void onOperatorClicked();
    void onFunctionClicked();
    void onEqualsClicked();
    void onReciprocalClicked();
    void onClearClicked();
    void onBackspaceClicked();
    void onParenthesisClicked();
    void onDotClicked();
    void updateDisplay(const QString& text);
};

#endif // MAINWINDOW_H
