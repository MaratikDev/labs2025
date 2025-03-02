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
    errorMessages[Ok] = "Ошибок нет";
    errorMessages[OutOfFourBytes] = "Слишком большое число";
    errorMessages[WrongSystem] = "Проблема с системой счисления!";
    errorMessages[UnacceptableNumber] = "Проблема с введенным числом и системой счисления!";
    errorMessages[Empty] = "Что то не пошло не так....Неверный ввод или его отсутвие)";
    // Функция связи сигналов (кнопок интерфейса) и слотов - функий обратного вызова (callback)
    connect(ui->convertButton, &QPushButton::clicked, this, &MainWindow::onConvertValueClicked);
    connect(ui->copyButton, &QPushButton::clicked, this, &MainWindow::onCopyClicked);
    connect(ui->inputValue, &QLineEdit::textChanged, this, &MainWindow::inputValueChanged);
    connect(ui->inputSystem, &QLineEdit::textChanged, this, &MainWindow::inputSystemChanged);
    connect(ui->outputSystem, &QLineEdit::textChanged, this, &MainWindow::outputSystemChanged);
    connect(ui->ChangeButton, &QPushButton::clicked, this, &MainWindow::changeValuesClicked);
    doOperation(Initialization, &context, NULL);
    updateLabels();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onConvertValueClicked() {
    AppParams param;
    std::string description;
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
    description = convertErrorToString(result, errorMessages);
    showErrorMessage(description);
    updateLabels();
}
std::string MainWindow::convertErrorToString(ResultLogic result, std::map<ResultLogic, char*>& errorMessages){
    auto it = errorMessages.find(result);
    return it->second;
}
void MainWindow::showErrorMessage(const std::string& description){
    if(description == "Ошибок нет")
        return;
    QMessageBox::critical(this, "Ошибка", QString::fromStdString(description));
}
void MainWindow::onCopyClicked(){
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(context.outputValue);
}

void MainWindow::updateLabels() {
    ui->output->setText(QString::fromUtf8(context.outputValue));
    ui->inputValue->setText(QString::fromUtf8(context.inputValue));
    ui->inputSystem->setText(QString::number(context.inputSystem));
    ui->outputSystem->setText(QString::number(context.outputSystem));
}
void MainWindow::inputValueChanged(){
    AppParams param;
    QString inputText = ui->inputValue->text();
    if (!inputText.isEmpty()) {
        strncpy(param.inputValue, inputText.toStdString().c_str(), MAX_LENGTH_OF_NUMBER - 1);
        param.inputValue[MAX_LENGTH_OF_NUMBER - 1] = '\0';
    } else {
        param.inputValue[0] = '\0';
    }
    doOperation(SaveInputValue, &context, &param);
}
void MainWindow::inputSystemChanged(){
    AppParams param;
    param.inputSystem = ui->inputSystem->text().toInt();
    doOperation(SaveInputSystem, &context, &param);
}
void MainWindow::outputSystemChanged(){
    AppParams param;
    param.outputSystem = ui->outputSystem->text().toInt();
    doOperation(SaveOutputSystem, &context, &param);
}
void MainWindow::changeValuesClicked(){
    doOperation(ChangeValues, &context, NULL);
    updateLabels();
}
