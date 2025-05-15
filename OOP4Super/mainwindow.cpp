#include "mainwindow.h"
#include "qtscenedrawer.h"
#include "ui_mainwindow.h"
#include "facade.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QPainter>
#include <cmath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QtSceneDrawer* sceneDrawer = ui->widget;
    facade = new Facade(sceneDrawer);

    ui->stepInput->setValue(DEFAULT_STEP);
    ui->normMinInput->setValue(DEFAULT_MIN);
    ui->normMaxInput->setValue(DEFAULT_MAX);
    ui->scaleSpinBox->setValue(DEFAULT_SCALE);


    connect(ui->openFileButton, &QPushButton::clicked, this, &MainWindow::openFile);
    connect(ui->normalizeButton, &QPushButton::clicked, this, &MainWindow::normalizeData);
    connect(ui->resetCameraButton, &QPushButton::clicked, this, &MainWindow::resetCamera);

    connect(ui->xRotateSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            this, &MainWindow::rotateScene);
    connect(ui->yRotateSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            this, &MainWindow::rotateScene);
    connect(ui->zRotateSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            this, &MainWindow::rotateScene);

    connect(ui->xTranslateSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            this, &MainWindow::translateScene);
    connect(ui->yTranslateSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            this, &MainWindow::translateScene);
    connect(ui->zTranslateSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            this, &MainWindow::translateScene);

    connect(ui->scaleSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            this, &MainWindow::scaleScene);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete facade;
}

void MainWindow::openFile()
{
    QString filePath = QFileDialog::getOpenFileName(this,
                                                    "Open CSV File", "", "CSV Files (*.csv)");

    if (filePath.isEmpty()) return;

    currentFilePath = filePath;
    ui->filenameLabel->setText(QFileInfo(filePath).fileName());

    NormalizationParameters params;
    params.min = ui->normMinInput->value();
    params.max = ui->normMaxInput->value();
    params.step = ui->stepInput->value();



    FacadeOperationResult result = facade->loadScene(currentFilePath.toUtf8().data(), params);
    if(params.min >= params.max)
        result = FacadeOperationResult(false, "Min step >= Max step");
    if (!result.isSuccess()) {
        QMessageBox::critical(this, "Error", result.getErrorMessage().c_str());
        return;
    }

    update();
}

void MainWindow::normalizeData()
{
    if (currentFilePath.isEmpty()) {
        QMessageBox::warning(this, "Warning", "No file loaded");
        return;
    }

    NormalizationParameters params;
    params.min = ui->normMinInput->value();
    params.max = ui->normMaxInput->value();
    params.step = ui->stepInput->value();


    FacadeOperationResult result = facade->loadScene(currentFilePath.toUtf8().data(), params);
    if(params.min >= params.max)
        result = FacadeOperationResult(false, "Min step >= Max step");
    if (!result.isSuccess()) {
        QMessageBox::critical(this, "Error", result.getErrorMessage().c_str());
        return;
    }
    else{
        scaleScene();
        if (!result.isSuccess()) {
            QMessageBox::critical(this, "Error", result.getErrorMessage().c_str());
            return;
        }
    }

    update();
}

void MainWindow::rotateScene()
{
    float x = ui->xRotateSpinBox->value() * M_PI / RADIAN;
    float y = ui->yRotateSpinBox->value() * M_PI / RADIAN;
    float z = ui->zRotateSpinBox->value() * M_PI / RADIAN;

    facade->rotateScene(x, y, z);


    float xt = ui->xTranslateSpinBox->value();
    float yt = ui->yTranslateSpinBox->value();
    float zt = ui->zTranslateSpinBox->value();

    facade->moveScene(xt, yt, zt);


    float scale = ui->scaleSpinBox->value() / DEFAULT_COEF;
    facade->scaleScene(scale, scale, scale);
    facade->drawScene();

    update();
}

void MainWindow::translateScene()
{
    float x = ui->xRotateSpinBox->value() * M_PI / RADIAN;
    float y = ui->yRotateSpinBox->value() * M_PI / RADIAN;
    float z = ui->zRotateSpinBox->value() * M_PI / RADIAN;

    facade->rotateScene(x, y, z);


    float xt = ui->xTranslateSpinBox->value();
    float yt = ui->yTranslateSpinBox->value();
    float zt = ui->zTranslateSpinBox->value();

    facade->moveScene(xt, yt, zt);


    float scale = ui->scaleSpinBox->value() / DEFAULT_COEF;
    facade->scaleScene(scale, scale, scale);
    facade->drawScene();

    update();
}

void MainWindow::scaleScene()
{
    float x = ui->xRotateSpinBox->value() * M_PI / RADIAN;
    float y = ui->yRotateSpinBox->value() * M_PI / RADIAN;
    float z = ui->zRotateSpinBox->value() * M_PI / RADIAN;

    facade->rotateScene(x, y, z);


    float xt = ui->xTranslateSpinBox->value();
    float yt = ui->yTranslateSpinBox->value();
    float zt = ui->zTranslateSpinBox->value();

    facade->moveScene(xt, yt, zt);


    float scale = ui->scaleSpinBox->value() / DEFAULT_COEF;
    facade->scaleScene(scale, scale, scale);
    facade->drawScene();

    update();
}

void MainWindow::resetCamera()
{

    ui->xRotateSpinBox->setValue(DEFAULT_VAL);
    ui->yRotateSpinBox->setValue(DEFAULT_VAL);
    ui->zRotateSpinBox->setValue(DEFAULT_VAL);
    ui->xTranslateSpinBox->setValue(DEFAULT_VAL);
    ui->yTranslateSpinBox->setValue(DEFAULT_VAL);
    ui->zTranslateSpinBox->setValue(DEFAULT_VAL);
    ui->scaleSpinBox->setValue(DEFAULT_SCALE);


    if (!currentFilePath.isEmpty()) {
        normalizeData();
    }
}
