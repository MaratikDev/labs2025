#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include "QClipboard"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // Волшебный метод генерирующий код
    ui->setupUi(this);
    // Функция связи сигналов (кнопок интерфейса) и слотов - функий обратного вызова (callback)
    connect(ui->updateButton, &QPushButton::clicked, this, &MainWindow::onUpdateValueClicked);
    connect(ui->copyButton, &QPushButton::clicked, this, &MainWindow::onCopyClicked);
    doOperation(Initialization, &context, NULL);
    updateLabels();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onUpdateValueClicked() {
    AppParams param;
    param.inputSystem = ui->inputSystem->text().toInt();
    param.outputSystem = ui->outputSystem->text().toInt();

    QString inputText = ui->inputValue->text();
    if (!inputText.isEmpty()) {
        strncpy(param.inputValue, inputText.toStdString().c_str(), MAX_LENGTH_OF_NUMBER - 1);
        param.inputValue[MAX_LENGTH_OF_NUMBER - 1] = '\0';
    } else {
        param.inputValue[0] = '\0';
    }

    switch(doOperation(Update, &context, &param)){

    case Ok:
        break;
    case OutOfFourBytes:
        QMessageBox::critical(this, "Ошибка", "Слишком большое число");
        break;
    case WrongSystem:
        QMessageBox::critical(this, "Ошибка", "Проблема с системой счисления!");
        break;
    case UnacceptableNumber:
        QMessageBox::critical(this, "Ошибка", "Проблема с введенным числом и системой счисления!");
        break;
    case Empty:
        QMessageBox::critical(this, "Ошибка", "Что то не пошло не так....Неверный ввод или его отсутвие)");
        break;
    }

    updateLabels();
}
void MainWindow::onCopyClicked(){
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(context.outputValue);
}

void MainWindow::updateLabels() {
    ui->output->setText(QString::fromUtf8(context.outputValue));
}



