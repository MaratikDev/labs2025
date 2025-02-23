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
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *incrementButton;
    QPushButton *decrementButton;
    QPushButton *updateButton;
    QLineEdit *valueEdit;
    QLabel *currentValueLabel;
    QLabel *clickCountLabel;
    QLabel *currentValue;
    QLabel *clickCount;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        incrementButton = new QPushButton(centralwidget);
        incrementButton->setObjectName("incrementButton");
        incrementButton->setGeometry(QRect(320, 230, 93, 29));
        decrementButton = new QPushButton(centralwidget);
        decrementButton->setObjectName("decrementButton");
        decrementButton->setGeometry(QRect(320, 280, 93, 29));
        updateButton = new QPushButton(centralwidget);
        updateButton->setObjectName("updateButton");
        updateButton->setGeometry(QRect(320, 330, 93, 29));
        valueEdit = new QLineEdit(centralwidget);
        valueEdit->setObjectName("valueEdit");
        valueEdit->setGeometry(QRect(310, 190, 113, 26));
        currentValueLabel = new QLabel(centralwidget);
        currentValueLabel->setObjectName("currentValueLabel");
        currentValueLabel->setGeometry(QRect(270, 110, 101, 20));
        clickCountLabel = new QLabel(centralwidget);
        clickCountLabel->setObjectName("clickCountLabel");
        clickCountLabel->setGeometry(QRect(270, 150, 91, 20));
        currentValue = new QLabel(centralwidget);
        currentValue->setObjectName("currentValue");
        currentValue->setGeometry(QRect(390, 110, 63, 20));
        clickCount = new QLabel(centralwidget);
        clickCount->setObjectName("clickCount");
        clickCount->setGeometry(QRect(390, 150, 63, 20));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 26));
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
        incrementButton->setText(QCoreApplication::translate("MainWindow", "Increment", nullptr));
        decrementButton->setText(QCoreApplication::translate("MainWindow", "Decrement", nullptr));
        updateButton->setText(QCoreApplication::translate("MainWindow", "Update", nullptr));
        currentValueLabel->setText(QCoreApplication::translate("MainWindow", "Current value", nullptr));
        clickCountLabel->setText(QCoreApplication::translate("MainWindow", "Click count", nullptr));
        currentValue->setText(QString());
        clickCount->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
