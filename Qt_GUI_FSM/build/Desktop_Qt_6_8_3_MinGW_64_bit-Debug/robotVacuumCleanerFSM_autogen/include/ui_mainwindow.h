/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
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
    QGraphicsView *fsmView;
    QGraphicsView *mapView;
    QPushButton *startButton;
    QPushButton *dockButton;
    QGraphicsView *batteryView;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1051, 767);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        fsmView = new QGraphicsView(centralwidget);
        fsmView->setObjectName("fsmView");
        fsmView->setGeometry(QRect(20, 30, 1021, 221));
        mapView = new QGraphicsView(centralwidget);
        mapView->setObjectName("mapView");
        mapView->setGeometry(QRect(20, 270, 1021, 451));
        startButton = new QPushButton(centralwidget);
        startButton->setObjectName("startButton");
        startButton->setGeometry(QRect(850, 290, 171, 71));
        dockButton = new QPushButton(centralwidget);
        dockButton->setObjectName("dockButton");
        dockButton->setGeometry(QRect(850, 370, 171, 71));
        batteryView = new QGraphicsView(centralwidget);
        batteryView->setObjectName("batteryView");
        batteryView->setGeometry(QRect(905, 40, 111, 61));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1051, 22));
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
        startButton->setText(QCoreApplication::translate("MainWindow", "Start Cleaning", nullptr));
        dockButton->setText(QCoreApplication::translate("MainWindow", "Return to Dock", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
