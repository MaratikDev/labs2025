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
    methodsOfErrorsMap[Ok] = std::bind(&MainWindow::handleOk, this);
    methodsOfErrorsMap[OutOfFourBytes] = std::bind(&MainWindow::handleOutOfFourBytes, this);
    methodsOfErrorsMap[WrongSystem] = std::bind(&MainWindow::handleWrongSystem, this);
    methodsOfErrorsMap[UnacceptableNumber] = std::bind(&MainWindow::handleUnacceptableNumber, this);
    methodsOfErrorsMap[Empty] = std::bind(&MainWindow::handleEmpty, this);
    // Функция связи сигналов (кнопок интерфейса) и слотов - функий обратного вызова (callback)
    connect(ui->updateButton, &QPushButton::clicked, this, &MainWindow::onConvertValueClicked);
    connect(ui->copyButton, &QPushButton::clicked, this, &MainWindow::onCopyClicked);
    doOperation(Initialization, &context, NULL);
    updateLabels();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onConvertValueClicked() {
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

    ResultLogic result = doOperation(Convert, &context, &param);
    methodsOfErrorsMap[result]();
    updateLabels();
}
void MainWindow::onCopyClicked(){
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(context.outputValue);
}

void MainWindow::updateLabels() {
    ui->output->setText(QString::fromUtf8(context.outputValue));
}
void MainWindow::handleOk() {}

void MainWindow::handleOutOfFourBytes() {
    QMessageBox::critical(this, "Ошибка", "Слишком большое число");
}

void MainWindow::handleWrongSystem() {
    QMessageBox::critical(this, "Ошибка", "Проблема с системой счисления!");
}

void MainWindow::handleUnacceptableNumber() {
    QMessageBox::critical(this, "Ошибка", "Проблема с введенным числом и системой счисления!");
}

void MainWindow::handleEmpty() {
    QMessageBox::critical(this, "Ошибка", "Что то не пошло не так....Неверный ввод или его отсутвие)");
}


