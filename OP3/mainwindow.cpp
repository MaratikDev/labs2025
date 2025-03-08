#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QLineSeries>
#include <string.h>
#include <QValueAxis>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    errorMessages[Ok] = "Ошибок нет";
    errorMessages[MemoryFail] = "Ошибка с выделением памяти";
    errorMessages[FileNotFound] = "Проблема с нахождением файла";
    errorMessages[WrongFormat] = "Что то не пошло не так....Неверный ввод или его отсутвие)";

    errorMessages[Success] = "Ошибок нет";
    errorMessages[InsultColumn] = "Столбцы метрик начинаются с 3 и их не больше чем в таблице)";
    errorMessages[NoCorrectRows] = "Нет подходящих строк";

    // Волшебный метод генерирующий код
    ui->setupUi(this);
    initialize();
    // Функция связи сигналов (кнопок интерфейса) и слотов - функий обратного вызова (callback)
    // Одному сигналу может соответствовать несколько слотов
    connect(ui->openFileButton, &QPushButton::clicked, this, &MainWindow::onOpenFileButtonClicked);
    connect(ui->loadDataButton, &QPushButton::clicked, this, &MainWindow::onLoadDataButtonClicked);
    connect(ui->calculateMetricsButton, &QPushButton::clicked, this, &MainWindow::onCalculateMetricsButtonClicked);
    updateLabels();
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
    updateLabels();
}
void MainWindow::onLoadDataButtonClicked() {
    AppParams param;
    strncpy(param.filterRegion, ui->regionInput->text().toStdString().c_str(),MAX_REGION_LENGTH-1);
    initialize(); //Иначе стобцы будут добавляться к существующим
    std::string description;
    ResultLogic result = doOperation(LoadData, &context, &param);
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(context.columnCount);

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
    showErrorMessage(result);
}

std::string MainWindow::convertErrorToString(ResultLogic result, std::map<ResultLogic, char*>& errorMessages){
    auto it = errorMessages.find(result);
    return it->second;
}
void MainWindow::showErrorMessage(ResultLogic result){
    if(result == Ok){
        QMessageBox::information(this, "Success",
                                 QString("Данные успешно загружены.\nВсего строк считано: %1\nКорректных строк: %2\nНекорректных строк: %3")
                                     .arg(context.totalRows)
                                     .arg(context.correctRows)
                                     .arg(context.inCorrectRows));
    }
    else if(result == Success){

    }
    else if(result == NoCorrectRows){
        QMessageBox::warning(this,"Внимание", QString::fromStdString(convertErrorToString(result, errorMessages)));
    }
    else{
        QMessageBox::critical(this, "Ошибка", QString::fromStdString(convertErrorToString(result, errorMessages)));
    }
}
void MainWindow::onCalculateMetricsButtonClicked() {
    onLoadDataButtonClicked();
    AppParams param;
    strncpy(param.filterRegion, ui->regionInput->text().toStdString().c_str(),MAX_REGION_LENGTH-1);
    param.columnIndex = ui->columnInput->text().toInt();
    ResultLogic resultMetric = doOperation(CalculateMetrics, &context, &param);
    showErrorMessage(resultMetric);
    if(resultMetric == Success){
        QLineSeries* series = new QLineSeries();
        for(int i = 0; i<context.countOfData;i++){
            series->append(context.yearsDraw[i],context.metricsDraw[i]);            //сделать как во 2 оп чтобы оставались только выделенные регионы(просто вызвать функцию loaddata)
        }
        series->setName(param.filterRegion);

        QChart* chart = new QChart();
        chart->addSeries(series);
        chart->createDefaultAxes();

        QValueAxis* axisX = qobject_cast<QValueAxis*>(chart->axes(Qt::Horizontal).first());
        axisX->setLabelFormat("%d");

        ui->chartView->setChart(chart);
        ui->chartView->setRenderHint(QPainter::Antialiasing);
        updateLabels();
    }
}

void MainWindow::updateLabels() {
    ui->minOutput->setText(QString::number(context.min));
    ui->medianOutput->setText(QString::number(context.median));
    ui->maxOutput->setText(QString::number(context.max));
}



