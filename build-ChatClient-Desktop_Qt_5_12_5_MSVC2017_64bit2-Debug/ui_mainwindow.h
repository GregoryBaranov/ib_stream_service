/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNew_connect;
    QAction *actionExit;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QWidget *pnlSettings;
    QGridLayout *gridLayout_4;
    QPushButton *DarkDesign;
    QSpinBox *spinPort;
    QLineEdit *hostEdit;
    QPushButton *Disconnect;
    QSpacerItem *verticalSpacer;
    QPushButton *connect;
    QPushButton *WhiteDesign;
    QPushButton *send;
    QLineEdit *messageEdt;
    QWidget *titleBar;
    QGridLayout *gridLayout_2;
    QLabel *label;
    QPushButton *btn_close;
    QPushButton *btn_maximize;
    QPushButton *btn_minimize;
    QPushButton *Settings;
    QTextEdit *messageBoard;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(957, 447);
        actionNew_connect = new QAction(MainWindow);
        actionNew_connect->setObjectName(QString::fromUtf8("actionNew_connect"));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        pnlSettings = new QWidget(centralWidget);
        pnlSettings->setObjectName(QString::fromUtf8("pnlSettings"));
        gridLayout_4 = new QGridLayout(pnlSettings);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        DarkDesign = new QPushButton(pnlSettings);
        DarkDesign->setObjectName(QString::fromUtf8("DarkDesign"));

        gridLayout_4->addWidget(DarkDesign, 4, 0, 1, 1);

        spinPort = new QSpinBox(pnlSettings);
        spinPort->setObjectName(QString::fromUtf8("spinPort"));

        gridLayout_4->addWidget(spinPort, 2, 0, 1, 2);

        hostEdit = new QLineEdit(pnlSettings);
        hostEdit->setObjectName(QString::fromUtf8("hostEdit"));
        hostEdit->setMinimumSize(QSize(280, 40));

        gridLayout_4->addWidget(hostEdit, 1, 0, 1, 2);

        Disconnect = new QPushButton(pnlSettings);
        Disconnect->setObjectName(QString::fromUtf8("Disconnect"));
        Disconnect->setMinimumSize(QSize(0, 40));

        gridLayout_4->addWidget(Disconnect, 3, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_4->addItem(verticalSpacer, 5, 0, 1, 2);

        connect = new QPushButton(pnlSettings);
        connect->setObjectName(QString::fromUtf8("connect"));
        connect->setMinimumSize(QSize(0, 40));

        gridLayout_4->addWidget(connect, 3, 1, 1, 1);

        WhiteDesign = new QPushButton(pnlSettings);
        WhiteDesign->setObjectName(QString::fromUtf8("WhiteDesign"));

        gridLayout_4->addWidget(WhiteDesign, 4, 1, 1, 1);


        gridLayout->addWidget(pnlSettings, 0, 5, 5, 1);

        send = new QPushButton(centralWidget);
        send->setObjectName(QString::fromUtf8("send"));
        send->setMinimumSize(QSize(80, 40));
        send->setMaximumSize(QSize(16777215, 16777215));
        send->setAutoDefault(true);

        gridLayout->addWidget(send, 2, 1, 1, 1);

        messageEdt = new QLineEdit(centralWidget);
        messageEdt->setObjectName(QString::fromUtf8("messageEdt"));
        messageEdt->setMinimumSize(QSize(0, 40));
        messageEdt->setMaximumSize(QSize(16777215, 16777215));

        gridLayout->addWidget(messageEdt, 2, 0, 1, 1);

        titleBar = new QWidget(centralWidget);
        titleBar->setObjectName(QString::fromUtf8("titleBar"));
        gridLayout_2 = new QGridLayout(titleBar);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label = new QLabel(titleBar);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMaximumSize(QSize(16777215, 16777215));
        label->setStyleSheet(QString::fromUtf8("background-color: rgb(61, 61, 61);\n"
"color: rgb(255, 255, 255);"));

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        btn_close = new QPushButton(titleBar);
        btn_close->setObjectName(QString::fromUtf8("btn_close"));
        btn_close->setMinimumSize(QSize(52, 50));
        btn_close->setMaximumSize(QSize(52, 50));
        btn_close->setStyleSheet(QString::fromUtf8("font: 14pt \"MS Shell Dlg 2\";"));
        btn_close->setAutoDefault(true);

        gridLayout_2->addWidget(btn_close, 0, 4, 1, 1);

        btn_maximize = new QPushButton(titleBar);
        btn_maximize->setObjectName(QString::fromUtf8("btn_maximize"));
        btn_maximize->setMinimumSize(QSize(52, 50));
        btn_maximize->setMaximumSize(QSize(52, 50));
        btn_maximize->setStyleSheet(QString::fromUtf8("font: 14pt \"MS Shell Dlg 2\";"));
        btn_maximize->setAutoDefault(true);

        gridLayout_2->addWidget(btn_maximize, 0, 3, 1, 1);

        btn_minimize = new QPushButton(titleBar);
        btn_minimize->setObjectName(QString::fromUtf8("btn_minimize"));
        btn_minimize->setMinimumSize(QSize(52, 50));
        btn_minimize->setMaximumSize(QSize(52, 50));
        btn_minimize->setStyleSheet(QString::fromUtf8("font: 14pt \"MS Shell Dlg 2\";"));
        btn_minimize->setAutoDefault(true);

        gridLayout_2->addWidget(btn_minimize, 0, 2, 1, 1);

        Settings = new QPushButton(titleBar);
        Settings->setObjectName(QString::fromUtf8("Settings"));
        Settings->setMinimumSize(QSize(100, 50));
        Settings->setMaximumSize(QSize(90, 16777215));
        Settings->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        gridLayout_2->addWidget(Settings, 0, 1, 1, 1);


        gridLayout->addWidget(titleBar, 0, 0, 1, 2);

        messageBoard = new QTextEdit(centralWidget);
        messageBoard->setObjectName(QString::fromUtf8("messageBoard"));
        messageBoard->setMinimumSize(QSize(0, 0));
        messageBoard->setMaximumSize(QSize(16777215, 16777215));
        messageBoard->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        messageBoard->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        gridLayout->addWidget(messageBoard, 1, 0, 1, 2);

        gridLayout->setColumnStretch(0, 1);
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        send->setDefault(true);
        btn_close->setDefault(true);
        btn_maximize->setDefault(true);
        btn_minimize->setDefault(true);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        actionNew_connect->setText(QApplication::translate("MainWindow", "New connect...", nullptr));
        actionExit->setText(QApplication::translate("MainWindow", "Exit", nullptr));
        DarkDesign->setText(QApplication::translate("MainWindow", "Dark", nullptr));
        Disconnect->setText(QApplication::translate("MainWindow", "Disconnect", nullptr));
        connect->setText(QApplication::translate("MainWindow", "Connect", nullptr));
        WhiteDesign->setText(QApplication::translate("MainWindow", "White", nullptr));
        send->setText(QApplication::translate("MainWindow", "Send", nullptr));
        label->setText(QApplication::translate("MainWindow", " Chat", nullptr));
        btn_close->setText(QString());
        btn_maximize->setText(QString());
        btn_minimize->setText(QString());
        Settings->setText(QApplication::translate("MainWindow", "Settings", nullptr));
#ifndef QT_NO_ACCESSIBILITY
        messageBoard->setAccessibleDescription(QString());
#endif // QT_NO_ACCESSIBILITY
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
