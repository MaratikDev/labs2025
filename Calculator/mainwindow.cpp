#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Цифровые кнопки
    for (int i = 0; i < 10; ++i) {
        connect(findChild<QPushButton*>(QString("button%1").arg(i)),
                &QPushButton::clicked, this, &MainWindow::onDigitClicked);
    }

    // Операторы
    QStringList operators = {"Plus", "Minus", "Multiply", "Divide"};
    for (const auto& op : operators) {
        connect(findChild<QPushButton*>(QString("button%1").arg(op)),
                &QPushButton::clicked, this, &MainWindow::onOperatorClicked);
    }

    // Функции
    QStringList functions = {"Sqrt", "Sin", "Cos", "Tan", "Cot"};
    for (const auto& func : functions) {
        connect(findChild<QPushButton*>(QString("button%1").arg(func)),
                &QPushButton::clicked, this, &MainWindow::onFunctionClicked);
    }

    // Скобки
    connect(ui->buttonLeftParen, &QPushButton::clicked, this, &MainWindow::onParenthesisClicked);
    connect(ui->buttonRightParen, &QPushButton::clicked, this, &MainWindow::onParenthesisClicked);

    // Прочие кнопки
    connect(ui->buttonReciprocal, &QPushButton::clicked, this, &MainWindow::onReciprocalClicked);
    connect(ui->buttonEquals, &QPushButton::clicked, this, &MainWindow::onEqualsClicked);
    connect(ui->buttonClear, &QPushButton::clicked, this, &MainWindow::onClearClicked);
    connect(ui->buttonDel, &QPushButton::clicked, this, &MainWindow::onBackspaceClicked);
    connect(ui->buttonDot, &QPushButton::clicked, this, &MainWindow::onDotClicked);
    previousEqual = false;
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::onDigitClicked() {
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    updateDisplay(ui->display->text() + button->text());
    previousEqual = false;
}

void MainWindow::onOperatorClicked() {
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    QString op;
    if (button == ui->buttonPlus)
        op = "+";
    else if (button == ui->buttonMinus)
        op = "-";
    else if (button == ui->buttonMultiply)
        op = "*";
    else if (button == ui->buttonDivide)
        op = "/";

    updateDisplay(ui->display->text() + op);
    previousEqual = false;
}

void MainWindow::onFunctionClicked() {
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    QString func;

    if (button == ui->buttonSqrt) func = "sqrt(";
    else if (button == ui->buttonSin) func = "sin(";
    else if (button == ui->buttonCos) func = "cos(";
    else if (button == ui->buttonTan) func = "tan(";
    else if (button == ui->buttonCot) func = "cot(";
    updateDisplay(ui->display->text() + func);
    previousEqual = false;
}

void MainWindow::onEqualsClicked() {
    try {
        double result = calculator.evaluate(ui->display->text().toStdString());
        updateDisplay(QString::number(result));
        previousEqual = true;
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Error", e.what());
    }
}

void MainWindow::onReciprocalClicked() {
    try {
        double result = calculator.evalReciprocal(ui->display->text().toStdString());
        updateDisplay(QString::number(result));
        previousEqual = true;
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Error", e.what());
    }
}

void MainWindow::onClearClicked() {
    updateDisplay("");
    previousEqual = false;
}

void MainWindow::onBackspaceClicked() {
    if(previousEqual)
        updateDisplay("");
    else{
        QString text = ui->display->text();
        if (!text.isEmpty()) {
            text.chop(1);
            updateDisplay(text);
        }
    }
}

void MainWindow::onParenthesisClicked() {
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    updateDisplay(ui->display->text() + button->text());
    previousEqual = false;
}

void MainWindow::onDotClicked() {
    QString text = ui->display->text();
    if (text.isEmpty() || text.endsWith(" ")) {
        text += "0";
    }
    updateDisplay(text + ".");
    previousEqual = false;
}


//Почти бесполезно
void MainWindow::updateDisplay(const QString& text) {
    ui->display->setText(text);
}
