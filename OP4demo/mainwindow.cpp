#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    surfaceWidget = new SurfaceWidget(this);
    ui->verticalLayout->insertWidget(0, surfaceWidget);

    initialize();

    connect(ui->openFileButton, &QPushButton::clicked, this, &MainWindow::onOpenFileButtonClicked);
    connect(ui->normalizeButton, &QPushButton::clicked, this, &MainWindow::onNormalizeButtonClicked);
    connect(ui->xRotateSlider, &QSlider::valueChanged, this, &MainWindow::onXRotateSliderChanged);
    connect(ui->yRotateSlider, &QSlider::valueChanged, this, &MainWindow::onYRotateSliderChanged);
    connect(ui->zRotateSlider, &QSlider::valueChanged, this, &MainWindow::onZRotateSliderChanged);
    connect(ui->xTranslateSlider, &QSlider::valueChanged, this, &MainWindow::onXTranslateSliderChanged);
    connect(ui->yTranslateSlider, &QSlider::valueChanged, this, &MainWindow::onYTranslateSliderChanged);
    connect(ui->zTranslateSlider, &QSlider::valueChanged, this, &MainWindow::onZTranslateSliderChanged);
    connect(ui->scaleSlider, &QSlider::valueChanged, this, &MainWindow::onScaleSliderChanged);
    connect(ui->resetCameraButton, &QPushButton::clicked, this, &MainWindow::onResetCameraButtonClicked);
}

void MainWindow::initialize()
{
    AppParams params = {0};
    doOperation(Initialize, &context, &params);
    surfaceWidget->setContext(&context);

    errorMessages[Ok] = "Success";
    errorMessages[MemoryFail] = "Memory allocation error";
    errorMessages[FileNotFound] = "File not found";
    errorMessages[WrongFormat] = "Invalid file format";
    errorMessages[InvalidStep] = "Invalid step value";
    errorMessages[InvalidNormalizationRange] = "Invalid normalization range (min must be less than max)";
    errorMessages[NoDataLoaded] = "No data loaded";

    ui->stepInput->setValue(1.0);
    ui->normMinInput->setValue(0.0);
    ui->normMaxInput->setValue(1.0);
}

void MainWindow::onOpenFileButtonClicked()
{
    AppParams params = {0};
    QString filename = QFileDialog::getOpenFileName(this, "Open CSV", "", "CSV Files (*.csv)");
    if (filename.isEmpty()) return;

    strncpy(params.filename, filename.toStdString().c_str(), MAX_FILENAME_LENGTH-1);

    ResultLogic result = doOperation(OpenFile, &context, &params);
    if (result == Ok) {
        ui->filenameLabel->setText(filename);
        surfaceWidget->update();
    } else {
        showErrorMessage(result);
    }
}

void MainWindow::onNormalizeButtonClicked()
{
    AppParams params = {0};
    params.step = ui->stepInput->value();
    params.normMin = ui->normMinInput->value();
    params.normMax = ui->normMaxInput->value();

    ResultLogic result = doOperation(NormalizeData, &context, &params);
    if (result == Ok) {
        surfaceWidget->update();
    } else {
        showErrorMessage(result);
    }
}

void MainWindow::onXRotateSliderChanged(int value)
{
    AppParams params = {0};
    params.angle = value;
    doOperation(RotateCameraX, &context, &params);
    surfaceWidget->update();
}

void MainWindow::onYRotateSliderChanged(int value)
{
    AppParams params = {0};
    params.angle = value;
    doOperation(RotateCameraY, &context, &params);
    surfaceWidget->update();
}

void MainWindow::onZRotateSliderChanged(int value)
{
    AppParams params = {0};
    params.angle = value;
    doOperation(RotateCameraZ, &context, &params);
    surfaceWidget->update();
}

void MainWindow::onXTranslateSliderChanged(int value)
{
    AppParams params = {0};
    params.translation = value / 10.0;
    doOperation(TranslateCameraX, &context, &params);
    surfaceWidget->update();
}

void MainWindow::onYTranslateSliderChanged(int value)
{
    AppParams params = {0};
    params.translation = value / 10.0;
    doOperation(TranslateCameraY, &context, &params);
    surfaceWidget->update();
}

void MainWindow::onZTranslateSliderChanged(int value)
{
    AppParams params = {0};
    params.translation = value / 10.0;
    doOperation(TranslateCameraZ, &context, &params);
    surfaceWidget->update();
}

void MainWindow::onScaleSliderChanged(int value)
{
    AppParams params = {0};
    params.scale = value / 50.0;
    doOperation(ScaleCamera, &context, &params);
    surfaceWidget->update();
}

void MainWindow::onResetCameraButtonClicked()
{
    AppParams params = {0};
    doOperation(ResetCamera, &context, &params);
    ui->xRotateSlider->setValue(0);
    ui->yRotateSlider->setValue(0);
    ui->zRotateSlider->setValue(0);
    ui->xTranslateSlider->setValue(0);
    ui->yTranslateSlider->setValue(0);
    ui->zTranslateSlider->setValue(0);
    ui->scaleSlider->setValue(50);
    surfaceWidget->update();
}

void MainWindow::showErrorMessage(ResultLogic result)
{
    QMessageBox::critical(this, "Error", errorMessages[result]);
}

MainWindow::~MainWindow()
{
    delete ui;
}
