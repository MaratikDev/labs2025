/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *openFileButton;
    QLineEdit *fileNameLabel;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *regionInput;
    QLabel *label_2;
    QLineEdit *columnInput;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *loadDataButton;
    QPushButton *calculateMetricsButton;
    QTableWidget *tableWidget;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_3;
    QLineEdit *minOutput;
    QLabel *label_4;
    QLineEdit *maxOutput;
    QLabel *label_5;
    QLineEdit *medianOutput;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        openFileButton = new QPushButton(centralwidget);
        openFileButton->setObjectName("openFileButton");

        horizontalLayout->addWidget(openFileButton);

        fileNameLabel = new QLineEdit(centralwidget);
        fileNameLabel->setObjectName("fileNameLabel");
        fileNameLabel->setReadOnly(true);

        horizontalLayout->addWidget(fileNameLabel);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label = new QLabel(centralwidget);
        label->setObjectName("label");

        horizontalLayout_2->addWidget(label);

        regionInput = new QLineEdit(centralwidget);
        regionInput->setObjectName("regionInput");

        horizontalLayout_2->addWidget(regionInput);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");

        horizontalLayout_2->addWidget(label_2);

        columnInput = new QLineEdit(centralwidget);
        columnInput->setObjectName("columnInput");

        horizontalLayout_2->addWidget(columnInput);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        loadDataButton = new QPushButton(centralwidget);
        loadDataButton->setObjectName("loadDataButton");

        horizontalLayout_3->addWidget(loadDataButton);

        calculateMetricsButton = new QPushButton(centralwidget);
        calculateMetricsButton->setObjectName("calculateMetricsButton");

        horizontalLayout_3->addWidget(calculateMetricsButton);


        verticalLayout->addLayout(horizontalLayout_3);

        tableWidget = new QTableWidget(centralwidget);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setEnabled(true);
        tableWidget->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);
        tableWidget->setRowCount(0);
        tableWidget->setColumnCount(0);
        tableWidget->horizontalHeader()->setStretchLastSection(true);

        verticalLayout->addWidget(tableWidget);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");

        horizontalLayout_4->addWidget(label_3);

        minOutput = new QLineEdit(centralwidget);
        minOutput->setObjectName("minOutput");
        minOutput->setReadOnly(true);

        horizontalLayout_4->addWidget(minOutput);

        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");

        horizontalLayout_4->addWidget(label_4);

        maxOutput = new QLineEdit(centralwidget);
        maxOutput->setObjectName("maxOutput");
        maxOutput->setReadOnly(true);

        horizontalLayout_4->addWidget(maxOutput);

        label_5 = new QLabel(centralwidget);
        label_5->setObjectName("label_5");

        horizontalLayout_4->addWidget(label_5);

        medianOutput = new QLineEdit(centralwidget);
        medianOutput->setObjectName("medianOutput");
        medianOutput->setReadOnly(true);

        horizontalLayout_4->addWidget(medianOutput);


        verticalLayout->addLayout(horizontalLayout_4);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Data Visualizer", nullptr));
        openFileButton->setText(QCoreApplication::translate("MainWindow", "Open File", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Region:", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Column:", nullptr));
        loadDataButton->setText(QCoreApplication::translate("MainWindow", "Load Data", nullptr));
        calculateMetricsButton->setText(QCoreApplication::translate("MainWindow", "Calculate Metrics", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Min:", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Max:", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Median:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
