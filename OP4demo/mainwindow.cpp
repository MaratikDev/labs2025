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

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initialize()
{
    doOperation(Initialize, &context, NULL);
    surfaceWidget->setContext(&context);

    errorMessages[Ok] = "Success";
    errorMessages[MemoryFail] = "Memory allocation error";
    errorMessages[FileNotFound] = "File not found";
    errorMessages[WrongFormat] = "Invalid file format";
    errorMessages[InvalidStep] = "Invalid step value";
    errorMessages[InvalidNormalizationRange] = "Invalid normalization range (min must be less than max)";
    errorMessages[NoDataLoaded] = "No data loaded";

    ui->stepInput->setValue(1);
    ui->normMinInput->setValue(0);
    ui->normMaxInput->setValue(1);
}

void MainWindow::onOpenFileButtonClicked()
{

    AppParams param;
    QString filename = QFileDialog::getOpenFileName(this, "Open CSV", "", "CSV Files (*.csv)");
    ui->filenameLabel->setText(filename);
    strncpy(param.filename, filename.toStdString().c_str(),MAX_FILENAME_LENGTH-1);
    ResultLogic result = doOperation(OpenFile, &context, &param);
    if (result == Ok) {
        ui->filenameLabel->setText(filename);
        surfaceWidget->update();
    }
    else {
        showErrorMessage(result);
    }
}

void MainWindow::onNormalizeButtonClicked()
{
    AppParams params;
    params.step = ui->stepInput->value();
    params.normMin = ui->normMinInput->value();
    params.normMax = ui->normMaxInput->value();

    ResultLogic result = doOperation(NormalizeData, &context, &params);
    if (result == Ok) {
        surfaceWidget->update();
    }
    else {
        showErrorMessage(result);
    }
}

void MainWindow::onXRotateSliderChanged(int value)
{
    AppParams params;
    params.angle = value;
    doOperation(RotateCameraX, &context, &params);
    surfaceWidget->update();
}

void MainWindow::onYRotateSliderChanged(int value)
{
    AppParams params;
    params.angle = value;
    doOperation(RotateCameraY, &context, &params);
    surfaceWidget->update();
}

void MainWindow::onZRotateSliderChanged(int value)
{
    AppParams params;
    params.angle = value;
    doOperation(RotateCameraZ, &context, &params);
    surfaceWidget->update();
}

void MainWindow::onXTranslateSliderChanged(int value)
{
    AppParams params;
    params.translation = value;
    doOperation(TranslateCameraX, &context, &params);
    surfaceWidget->update();
}

void MainWindow::onYTranslateSliderChanged(int value)
{
    AppParams params;
    params.translation = value;
    doOperation(TranslateCameraY, &context, &params);
    surfaceWidget->update();
}

void MainWindow::onZTranslateSliderChanged(int value)
{
    AppParams params;
    params.translation = value;
    doOperation(TranslateCameraZ, &context, &params);
    surfaceWidget->update();
}

void MainWindow::onScaleSliderChanged(int value)
{
    AppParams params;
    params.scale = value;
    doOperation(ScaleCamera, &context, &params);
    surfaceWidget->update();
}

void MainWindow::onResetCameraButtonClicked()
{
    AppParams params;
    doOperation(ResetCamera, &context, &params);
    ui->xRotateSlider->setValue(DEFAULT_VALUE);
    ui->yRotateSlider->setValue(DEFAULT_VALUE);
    ui->zRotateSlider->setValue(DEFAULT_VALUE);
    ui->xTranslateSlider->setValue(DEFAULT_VALUE);
    ui->yTranslateSlider->setValue(DEFAULT_VALUE);
    ui->zTranslateSlider->setValue(DEFAULT_VALUE);
    ui->scaleSlider->setValue(DEFAULT_SCALE);
    surfaceWidget->update();
}

void MainWindow::showErrorMessage(ResultLogic result)
{
    QMessageBox::critical(this, "Error", errorMessages[result]);
}

