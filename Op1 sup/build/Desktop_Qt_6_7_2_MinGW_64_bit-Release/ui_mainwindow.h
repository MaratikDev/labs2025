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
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout;
    QLabel *label_val;
    QLineEdit *inputValue;
    QLabel *label_sysin;
    QLineEdit *inputSystem;
    QLabel *label_sysout;
    QLineEdit *outputSystem;
    QPushButton *updateButton;
    QLabel *result;
    QLineEdit *output;
    QPushButton *copyButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(641, 590);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout_4 = new QVBoxLayout(centralwidget);
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        label_val = new QLabel(centralwidget);
        label_val->setObjectName("label_val");
        label_val->setAlignment(Qt::AlignmentFlag::AlignBottom|Qt::AlignmentFlag::AlignHCenter);

        verticalLayout->addWidget(label_val);

        inputValue = new QLineEdit(centralwidget);
        inputValue->setObjectName("inputValue");
        inputValue->setAlignment(Qt::AlignmentFlag::AlignHCenter|Qt::AlignmentFlag::AlignTop);

        verticalLayout->addWidget(inputValue);

        label_sysin = new QLabel(centralwidget);
        label_sysin->setObjectName("label_sysin");
        label_sysin->setAlignment(Qt::AlignmentFlag::AlignBottom|Qt::AlignmentFlag::AlignHCenter);

        verticalLayout->addWidget(label_sysin);

        inputSystem = new QLineEdit(centralwidget);
        inputSystem->setObjectName("inputSystem");
        inputSystem->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(inputSystem);

        label_sysout = new QLabel(centralwidget);
        label_sysout->setObjectName("label_sysout");
        label_sysout->setAlignment(Qt::AlignmentFlag::AlignBottom|Qt::AlignmentFlag::AlignHCenter);

        verticalLayout->addWidget(label_sysout);

        outputSystem = new QLineEdit(centralwidget);
        outputSystem->setObjectName("outputSystem");
        outputSystem->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(outputSystem);

        updateButton = new QPushButton(centralwidget);
        updateButton->setObjectName("updateButton");

        verticalLayout->addWidget(updateButton);

        result = new QLabel(centralwidget);
        result->setObjectName("result");
        result->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(result);

        output = new QLineEdit(centralwidget);
        output->setObjectName("output");
        output->setAlignment(Qt::AlignmentFlag::AlignCenter);
        output->setReadOnly(true);

        verticalLayout->addWidget(output);

        copyButton = new QPushButton(centralwidget);
        copyButton->setObjectName("copyButton");

        verticalLayout->addWidget(copyButton);


        verticalLayout_4->addLayout(verticalLayout);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 641, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label_val->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:18pt;\">\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \321\207\320\270\321\201\320\273\320\276 \320\264\320\273\321\217 \320\277\320\265\321\200\320\265\320\262\320\276\320\264\320\260</span></p></body></html>", nullptr));
        label_sysin->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:18pt;\">\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \321\201\320\270\321\201\321\202\320\265\320\274\321\203 \321\201\321\207\320\270\321\201\320\273\320\265\320\275\320\270\321\217 \320\270\320\267 \320\272\320\276\321\202\320\276\321\200\320\276\320\271 \320\277\320\265\321\200\320\265\320\262\320\276\320\264\320\270\321\202\320\265</span></p></body></html>", nullptr));
        label_sysout->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:18pt;\">\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \321\201\320\270\321\201\321\202\320\265\320\274\321\203 \321\201\321\207\320\270\321\201\320\273\320\265\320\275\320\270\321\217 \320\262 \320\272\320\276\321\202\320\276\321\200\321\203\321\216 \320\277\320\265\321\200\320\265\320\262\320\276\320\264\320\270\321\202\320\265</span></p></body></html>", nullptr));
        updateButton->setText(QCoreApplication::translate("MainWindow", "\320\232\320\276\320\275\320\262\320\265\321\200\321\202\320\270\321\200\320\276\320\262\320\260\321\202\321\214", nullptr));
        result->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:18pt;\">\320\240\320\265\320\267\321\203\320\273\321\214\321\202\320\260\321\202</span></p></body></html>", nullptr));
        copyButton->setText(QCoreApplication::translate("MainWindow", "\320\232\320\276\320\277\320\270\321\200\320\276\320\262\320\260\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
