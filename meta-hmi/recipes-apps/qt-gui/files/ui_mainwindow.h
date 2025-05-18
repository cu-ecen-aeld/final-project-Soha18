/********************************************************************************
** Form generated from reading UI file 'mainwindowAqWXuZ.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef MAINWINDOWAQWXUZ_H
#define MAINWINDOWAQWXUZ_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *widget;
    QGridLayout *gridLayout;
    QLabel *label;
    QLCDNumber *lcdNumber;
    QCheckBox *checkBox;
    QLabel *label_2;
    QLCDNumber *lcdNumber_2;
    QSlider *horizontalSlider;
    QLabel *label_3;
    QLCDNumber *lcdNumber_3;
    QPushButton *pushButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1201, 672);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(60, 70, 1001, 461));
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(40);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        lcdNumber = new QLCDNumber(widget);
        lcdNumber->setObjectName(QString::fromUtf8("lcdNumber"));
        sizePolicy.setHeightForWidth(lcdNumber->sizePolicy().hasHeightForWidth());
        lcdNumber->setSizePolicy(sizePolicy);
        QFont font1;
        font1.setPointSize(40);
        lcdNumber->setFont(font1);

        gridLayout->addWidget(lcdNumber, 0, 1, 1, 1);

        checkBox = new QCheckBox(widget);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        sizePolicy.setHeightForWidth(checkBox->sizePolicy().hasHeightForWidth());
        checkBox->setSizePolicy(sizePolicy);
        QFont font2;
        font2.setPointSize(36);
        checkBox->setFont(font2);

        gridLayout->addWidget(checkBox, 0, 2, 1, 1);

        label_2 = new QLabel(widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);
        label_2->setFont(font);

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        lcdNumber_2 = new QLCDNumber(widget);
        lcdNumber_2->setObjectName(QString::fromUtf8("lcdNumber_2"));
        sizePolicy.setHeightForWidth(lcdNumber_2->sizePolicy().hasHeightForWidth());
        lcdNumber_2->setSizePolicy(sizePolicy);
        lcdNumber_2->setFont(font1);

        gridLayout->addWidget(lcdNumber_2, 1, 1, 1, 1);

        horizontalSlider = new QSlider(widget);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(horizontalSlider, 1, 2, 1, 1);

        label_3 = new QLabel(widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);
        label_3->setFont(font);

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        lcdNumber_3 = new QLCDNumber(widget);
        lcdNumber_3->setObjectName(QString::fromUtf8("lcdNumber_3"));
        sizePolicy.setHeightForWidth(lcdNumber_3->sizePolicy().hasHeightForWidth());
        lcdNumber_3->setSizePolicy(sizePolicy);
        lcdNumber_3->setFont(font1);

        gridLayout->addWidget(lcdNumber_3, 2, 1, 1, 1);

        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        sizePolicy.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy);
        QFont font3;
        font3.setPointSize(50);
        font3.setBold(true);
        font3.setWeight(75);
        pushButton->setFont(font3);

        gridLayout->addWidget(pushButton, 2, 2, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1201, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Temperature", nullptr));
        checkBox->setText(QCoreApplication::translate("MainWindow", "Manual", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Pressure", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Humidity", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Exit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // MAINWINDOWAQWXUZ_H

