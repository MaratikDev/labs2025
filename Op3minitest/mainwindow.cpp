#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <string.h>
#include <stdlib.h>
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

    connect(ui->regionComboBox, &QComboBox::currentTextChanged, this, &MainWindow::onGraphSettingsChanged);
    connect(ui->columnComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::onGraphSettingsChanged);
    connect(ui->fromYearSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::onGraphSettingsChanged);
    connect(ui->toYearSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::onGraphSettingsChanged);
    updateLabels();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initialize(){
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    doOperation(Initialize, &context, NULL);
    errorMessages[Ok] = "Ошибок нет";
    errorMessages[MemoryFail] = "Ошибка с выделением памяти";
    errorMessages[FileNotFound] = "Проблема с нахождением файла";
    errorMessages[WrongFormat] = "Что то не пошло не так....Неверный ввод или его отсутвие)";

    errorMessages[SuccessMetricCalculated] = "Ошибок нет";
    errorMessages[InsultColumn] = "Столбцы метрик начинаются с 3 и их не больше чем в таблице)";
    errorMessages[NoCorrectRows] = "Нет подходящих строк";
}

void MainWindow::updateRegionsComboBox()
{
    ui->regionComboBox->clear();
    ui->regionComboBox->addItem(""); // Пустой элемент для всех регионов
    QSet<QString> regions = getUniqueRegions();
    for (const QString& region : regions) {
        ui->regionComboBox->addItem(region);
    }
}

void MainWindow::updateColumnsComboBox()
{
    ui->columnComboBox->clear();
    QVector<int> metricColumns = getMetricColumns();
    for (int col : metricColumns) {
        ui->columnComboBox->addItem(context.tableLogic.columnName[col], col);
    }
}

void MainWindow::onGraphSettingsChanged()
{
    if (context.tableLogic.head) {
        int columnIndex = ui->columnComboBox->currentData().toInt();
        if (columnIndex > 0) {
            updateGraph(columnIndex);
        }
    }
}

QSet<QString> MainWindow::getUniqueRegions()
{
    QSet<QString> regions;
    RowData* current = context.tableLogic.head;
    while (current != NULL) {
        regions.insert(QString::fromUtf8((char*)current->data[REGION_INDEX]));
        current = current->next;
    }
    return regions;
}

QVector<int> MainWindow::getMetricColumns()
{
    QVector<int> columns;
    // Предполагаем, что метрики начинаются с 3-го столбца (индекс 2)
    for (int i = 2; i < context.tableLogic.columnCount; ++i) {
        columns.append(i);
    }
    return columns;
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
    strncpy(param.filterRegion, ui->regionComboBox->currentText().toStdString().c_str(),MAX_REGION_LENGTH-1);
    initialize(); //Иначе стобцы будут добавляться к существующим
    std::string description;
    ResultLogic result = doOperation(LoadData, &context, &param);
    refreshTable();
    showErrorMessage(result);
    updateRegionsComboBox();
    updateColumnsComboBox();
    populateYearRange();
}

std::string MainWindow::convertErrorToString(ResultLogic result, std::map<ResultLogic, char*>& errorMessages){
    auto it = errorMessages.find(result);
    return it->second;
}
void MainWindow::showErrorMessage(ResultLogic result){
    if(result == Ok){
        QMessageBox::information(this, "Успех",
                                 QString("Данные успешно загружены.\nВсего строк считано: %1\nКорректных строк: %2\nНекорректных строк: %3")
                                     .arg(context.tableLogic.totalRows)
                                     .arg(context.tableLogic.correctRows)
                                     .arg(context.tableLogic.totalRows - context.tableLogic.correctRows));
    }
    else if(result == SuccessMetricCalculated){

    }
    else if(result == NoCorrectRows){
        QMessageBox::warning(this,"Внимание", QString::fromStdString(convertErrorToString(result, errorMessages)));
    }
    else{
        QMessageBox::critical(this, "Ошибка", QString::fromStdString(convertErrorToString(result, errorMessages)));
    }
}
void MainWindow::onCalculateMetricsButtonClicked() {
    AppParams param;
    strncpy(param.filterRegion, ui->regionComboBox->currentText().toStdString().c_str(),MAX_REGION_LENGTH-1);
    param.columnIndex = ui->columnComboBox->currentIndex();
    refreshTable();

    ResultLogic result = doOperation(CalculateMetrics, &context, &param);
    if (result == SuccessMetricCalculated){
        refreshTable();
        updateGraph(param.columnIndex);
    }
    showErrorMessage(result);
    updateLabels();

}

void MainWindow::updateGraph(int columnIndex) {
    QVector<QString> selectedRegions;
    if (!ui->regionComboBox->currentText().isEmpty()) {
        selectedRegions.append(ui->regionComboBox->currentText());
    }

    ui->graphWidget->setData(&context, columnIndex);
    ui->graphWidget->setFilter(selectedRegions,
                               ui->fromYearSpinBox->value(),
                               ui->toYearSpinBox->value());
    ui->graphWidget->drawGraph();
}

void MainWindow::updateLabels() {
    ui->minOutput->setText(QString::number(context.tableMetrics.min));
    ui->medianOutput->setText(QString::number(context.tableMetrics.median));
    ui->maxOutput->setText(QString::number(context.tableMetrics.max));
}
void MainWindow::regionChanged(){
    AppParams param;
    QString inputText = ui->regionComboBox->currentText();
    if (!inputText.isEmpty()) {
        strncpy(param.filterRegion, inputText.toStdString().c_str(), MAX_REGION_LENGTH - 1);
        param.filterRegion[MAX_REGION_LENGTH - 1] = '\0';
    } else {
        param.filterRegion[0] = '\0';
    }
    doOperation(SaveFilterRegion, &context, &param);
}
void MainWindow::refreshTable(){
    ui->tableWidget->clear();
    ui->graphWidget->clearMask();
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(context.tableLogic.columnCount);

    QStringList headers;
    for(int i = 0; i<context.tableLogic.columnCount;i++)
        headers << context.tableLogic.columnName[i];

    ui->tableWidget->setHorizontalHeaderLabels(headers);
    RowData* current = context.tableLogic.head;
    for(int row = 0;current!=NULL;row++,current = current->next){
        if(strlen(context.filterRegion) == 0 || strcmp(context.filterRegion,(char*)current->data[REGION_INDEX])== 0 ){
            ui->tableWidget->insertRow(row);
            for (int i = 0; i < (context.tableLogic.columnCount); i++) {
                ui->tableWidget->setItem(row, i, new QTableWidgetItem(QString::fromUtf8((char*)current->data[i])));
            }
        }
        else{
            row--;
        }

    }

}

void MainWindow::populateYearRange()
{
    if (!context.tableLogic.head) return;

    int minYear = MAX_YEAR;
    int maxYear = 0;
    RowData* current = context.tableLogic.head;
    while (current != NULL) {
        char* endptr;
        int year = strtod((char*)current->data[0], &endptr);
        if (year < minYear) minYear = year;
        if (year > maxYear) maxYear = year;
        current = current->next;
    }

    ui->fromYearSpinBox->setValue(minYear);
    ui->toYearSpinBox->setValue(maxYear);
}



