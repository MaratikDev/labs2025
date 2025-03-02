#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <string.h>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // Волшебный метод генерирующий код
    ui->setupUi(this);
    initialize();
    // Функция связи сигналов (кнопок интерфейса) и слотов - функий обратного вызова (callback)
    // Одному сигналу может соответствовать несколько слотов
    connect(ui->openFileButton, &QPushButton::clicked, this, &MainWindow::onOpenFileButtonClicked);
    connect(ui->loadDataButton, &QPushButton::clicked, this, &MainWindow::onLoadDataButtonClicked);
    connect(ui->calculateMetricsButton, &QPushButton::clicked, this, &MainWindow::onCalculateMetricsButtonClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initialize(){
    doOperation(Initialize, &context, NULL);
}

void MainWindow::onOpenFileButtonClicked() {
    AppParams param;
    QString filename = QFileDialog::getOpenFileName(this, "Open CSV", "", "CSV Files (*.csv)");
    ui->fileNameLabel->setText(filename);
    strncpy(param.filename, filename.toStdString().c_str(),MAX_FILENAME_LENGTH-1);
    doOperation(OpenFile, &context, &param);
}
void MainWindow::onLoadDataButtonClicked() {
    doOperation(LoadData, &context, NULL);
    if (context.head == NULL) {
        QMessageBox::warning(this, "Ошибка", "Не удалось загрузить данные из файла.");
        return;
    }
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(context.columnCount); // 7 колонок: год, регион и 5 метрик


    QStringList headers;
    for(int i = 0; i<context.columnCount;i++)
        headers << context.columnName[i];

    ui->tableWidget->setHorizontalHeaderLabels(headers);
    RowData* current = context.head;
    int row = 0;
    while (current != NULL) {
        ui->tableWidget->insertRow(row);
        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(current->year)));
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(QString::fromUtf8(current->region)));
        for (int i = 0; i < context.columnCount-2; i++) {
            ui->tableWidget->setItem(row, i+2, new QTableWidgetItem(QString::number(current->metrics[i])));
        }
        current = current->next;
        row++;
    }
    QMessageBox::information(this, "Success",
                             QString("Данные успешно загружены.\nВсего строк считано: %1\nКорректных строк: %2\nНекорректных строк: %3")
                                 .arg(context.totalRows)
                                 .arg(context.correctRows)
                                 .arg(context.inCorrectRows));
}
void MainWindow::onCalculateMetricsButtonClicked() {
    AppParams param;
    strncpy(param.filterRegion, ui->regionInput->text().toStdString().c_str(),MAX_REGION_LENGTH-1);
    param.columnIndex = ui->columnInput->text().toInt();
    doOperation(CalculateMetrics, &context, &param);
    updateLabels();
}

void MainWindow::updateLabels() {
    ui->minOutput->setText(QString::number(context.min));
    ui->medianOutput->setText(QString::number(context.median));
    ui->maxOutput->setText(QString::number(context.max));
}



