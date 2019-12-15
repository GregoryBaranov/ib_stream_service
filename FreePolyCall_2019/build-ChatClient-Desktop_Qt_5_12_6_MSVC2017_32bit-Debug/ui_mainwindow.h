/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
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
#include <QtWidgets/QListView>
#include <QtWidgets/QListWidget>
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
    QWidget *pnlChat;
    QGridLayout *gridLayout_5;
    QPushButton *send;
    QListView *MessageBoardList;
    QTextEdit *textEdit;
    QWidget *pnlSettings;
    QGridLayout *gridLayout_4;
    QPushButton *btnShowLogs;
    QWidget *GroupUserListWidget;
    QGridLayout *gridLayout_3;
    QListWidget *listViewUser;
    QLineEdit *lineSearchUserList;
    QPushButton *To_Ban_Button;
    QPushButton *Mute_Button;
    QLineEdit *hostEdit;
    QPushButton *BtnUserControl;
    QPushButton *Disconnect;
    QLabel *lable_session_num;
    QLineEdit *TitleEdit;
    QSpinBox *spinPort;
    QPushButton *Connect;
    QSpacerItem *verticalSpacer;
    QWidget *pnlStream;
    QGridLayout *gridLayout_7;
    QPushButton *StopSession;
    QPushButton *StartSession;
    QLabel *label_2;
    QWidget *titleBar;
    QGridLayout *gridLayout_2;
    QPushButton *ChatBtn;
    QPushButton *Settings;
    QPushButton *btn_maximize;
    QPushButton *btn_close;
    QLabel *label;
    QPushButton *btn_minimize;
    QWidget *pnlLogs;
    QGridLayout *gridLayout_6;
    QTextEdit *logBoard;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1227, 624);
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
        pnlChat = new QWidget(centralWidget);
        pnlChat->setObjectName(QString::fromUtf8("pnlChat"));
        pnlChat->setMaximumSize(QSize(500, 16777215));
        gridLayout_5 = new QGridLayout(pnlChat);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        send = new QPushButton(pnlChat);
        send->setObjectName(QString::fromUtf8("send"));
        send->setMinimumSize(QSize(80, 60));
        send->setMaximumSize(QSize(16777215, 16777215));
        send->setAutoDefault(true);

        gridLayout_5->addWidget(send, 1, 1, 1, 1);

        MessageBoardList = new QListView(pnlChat);
        MessageBoardList->setObjectName(QString::fromUtf8("MessageBoardList"));
        MessageBoardList->setStyleSheet(QString::fromUtf8(""));

        gridLayout_5->addWidget(MessageBoardList, 0, 0, 1, 2);

        textEdit = new QTextEdit(pnlChat);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setMaximumSize(QSize(16777215, 60));

        gridLayout_5->addWidget(textEdit, 1, 0, 1, 1);


        gridLayout->addWidget(pnlChat, 1, 1, 2, 1);

        pnlSettings = new QWidget(centralWidget);
        pnlSettings->setObjectName(QString::fromUtf8("pnlSettings"));
        pnlSettings->setMaximumSize(QSize(302, 16777215));
        gridLayout_4 = new QGridLayout(pnlSettings);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        btnShowLogs = new QPushButton(pnlSettings);
        btnShowLogs->setObjectName(QString::fromUtf8("btnShowLogs"));

        gridLayout_4->addWidget(btnShowLogs, 8, 0, 1, 2);

        GroupUserListWidget = new QWidget(pnlSettings);
        GroupUserListWidget->setObjectName(QString::fromUtf8("GroupUserListWidget"));
        GroupUserListWidget->setMinimumSize(QSize(0, 70));
        gridLayout_3 = new QGridLayout(GroupUserListWidget);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        listViewUser = new QListWidget(GroupUserListWidget);
        listViewUser->setObjectName(QString::fromUtf8("listViewUser"));

        gridLayout_3->addWidget(listViewUser, 1, 0, 1, 4);

        lineSearchUserList = new QLineEdit(GroupUserListWidget);
        lineSearchUserList->setObjectName(QString::fromUtf8("lineSearchUserList"));
        lineSearchUserList->setMinimumSize(QSize(0, 40));

        gridLayout_3->addWidget(lineSearchUserList, 0, 0, 1, 4);

        To_Ban_Button = new QPushButton(GroupUserListWidget);
        To_Ban_Button->setObjectName(QString::fromUtf8("To_Ban_Button"));

        gridLayout_3->addWidget(To_Ban_Button, 2, 0, 1, 1);

        Mute_Button = new QPushButton(GroupUserListWidget);
        Mute_Button->setObjectName(QString::fromUtf8("Mute_Button"));

        gridLayout_3->addWidget(Mute_Button, 2, 3, 1, 1);


        gridLayout_4->addWidget(GroupUserListWidget, 13, 0, 1, 2);

        hostEdit = new QLineEdit(pnlSettings);
        hostEdit->setObjectName(QString::fromUtf8("hostEdit"));
        hostEdit->setMinimumSize(QSize(0, 40));

        gridLayout_4->addWidget(hostEdit, 1, 0, 1, 2);

        BtnUserControl = new QPushButton(pnlSettings);
        BtnUserControl->setObjectName(QString::fromUtf8("BtnUserControl"));

        gridLayout_4->addWidget(BtnUserControl, 9, 0, 1, 2);

        Disconnect = new QPushButton(pnlSettings);
        Disconnect->setObjectName(QString::fromUtf8("Disconnect"));
        Disconnect->setMinimumSize(QSize(0, 40));

        gridLayout_4->addWidget(Disconnect, 6, 0, 1, 1);

        lable_session_num = new QLabel(pnlSettings);
        lable_session_num->setObjectName(QString::fromUtf8("lable_session_num"));
        lable_session_num->setMinimumSize(QSize(0, 40));
        lable_session_num->setStyleSheet(QString::fromUtf8(""));

        gridLayout_4->addWidget(lable_session_num, 5, 1, 1, 1);

        TitleEdit = new QLineEdit(pnlSettings);
        TitleEdit->setObjectName(QString::fromUtf8("TitleEdit"));
        TitleEdit->setMinimumSize(QSize(0, 40));

        gridLayout_4->addWidget(TitleEdit, 0, 0, 1, 2);

        spinPort = new QSpinBox(pnlSettings);
        spinPort->setObjectName(QString::fromUtf8("spinPort"));
        spinPort->setMinimumSize(QSize(0, 40));

        gridLayout_4->addWidget(spinPort, 5, 0, 1, 1);

        Connect = new QPushButton(pnlSettings);
        Connect->setObjectName(QString::fromUtf8("Connect"));
        Connect->setMinimumSize(QSize(0, 40));

        gridLayout_4->addWidget(Connect, 6, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_4->addItem(verticalSpacer, 14, 0, 1, 1);


        gridLayout->addWidget(pnlSettings, 1, 2, 1, 1);

        pnlStream = new QWidget(centralWidget);
        pnlStream->setObjectName(QString::fromUtf8("pnlStream"));
        gridLayout_7 = new QGridLayout(pnlStream);
        gridLayout_7->setSpacing(6);
        gridLayout_7->setContentsMargins(11, 11, 11, 11);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        StopSession = new QPushButton(pnlStream);
        StopSession->setObjectName(QString::fromUtf8("StopSession"));
        StopSession->setMinimumSize(QSize(0, 40));

        gridLayout_7->addWidget(StopSession, 1, 1, 1, 1);

        StartSession = new QPushButton(pnlStream);
        StartSession->setObjectName(QString::fromUtf8("StartSession"));
        StartSession->setMinimumSize(QSize(0, 40));

        gridLayout_7->addWidget(StartSession, 1, 0, 1, 1);

        label_2 = new QLabel(pnlStream);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_7->addWidget(label_2, 0, 0, 1, 2);


        gridLayout->addWidget(pnlStream, 1, 0, 2, 1);

        titleBar = new QWidget(centralWidget);
        titleBar->setObjectName(QString::fromUtf8("titleBar"));
        titleBar->setMinimumSize(QSize(0, 70));
        titleBar->setMaximumSize(QSize(16777215, 70));
        gridLayout_2 = new QGridLayout(titleBar);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        ChatBtn = new QPushButton(titleBar);
        ChatBtn->setObjectName(QString::fromUtf8("ChatBtn"));
        ChatBtn->setMinimumSize(QSize(100, 50));
        ChatBtn->setMaximumSize(QSize(90, 16777215));
        ChatBtn->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        gridLayout_2->addWidget(ChatBtn, 0, 1, 1, 1);

        Settings = new QPushButton(titleBar);
        Settings->setObjectName(QString::fromUtf8("Settings"));
        Settings->setMinimumSize(QSize(100, 50));
        Settings->setMaximumSize(QSize(90, 16777215));
        Settings->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        gridLayout_2->addWidget(Settings, 0, 2, 1, 1);

        btn_maximize = new QPushButton(titleBar);
        btn_maximize->setObjectName(QString::fromUtf8("btn_maximize"));
        btn_maximize->setMinimumSize(QSize(52, 50));
        btn_maximize->setMaximumSize(QSize(52, 50));
        btn_maximize->setStyleSheet(QString::fromUtf8("font: 14pt \"MS Shell Dlg 2\";"));
        btn_maximize->setAutoDefault(true);

        gridLayout_2->addWidget(btn_maximize, 0, 4, 1, 1);

        btn_close = new QPushButton(titleBar);
        btn_close->setObjectName(QString::fromUtf8("btn_close"));
        btn_close->setMinimumSize(QSize(52, 50));
        btn_close->setMaximumSize(QSize(52, 50));
        btn_close->setStyleSheet(QString::fromUtf8("font: 14pt \"MS Shell Dlg 2\";"));
        btn_close->setAutoDefault(true);

        gridLayout_2->addWidget(btn_close, 0, 5, 1, 1);

        label = new QLabel(titleBar);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(0, 50));
        label->setMaximumSize(QSize(16777215, 16777215));
        label->setStyleSheet(QString::fromUtf8("background-color: rgb(61, 61, 61);\n"
"color: rgb(255, 255, 255);\n"
"padding:1px;"));

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        btn_minimize = new QPushButton(titleBar);
        btn_minimize->setObjectName(QString::fromUtf8("btn_minimize"));
        btn_minimize->setMinimumSize(QSize(52, 50));
        btn_minimize->setMaximumSize(QSize(52, 50));
        btn_minimize->setStyleSheet(QString::fromUtf8("font: 14pt \"MS Shell Dlg 2\";"));
        btn_minimize->setAutoDefault(true);

        gridLayout_2->addWidget(btn_minimize, 0, 3, 1, 1);


        gridLayout->addWidget(titleBar, 0, 0, 1, 3);

        pnlLogs = new QWidget(centralWidget);
        pnlLogs->setObjectName(QString::fromUtf8("pnlLogs"));
        pnlLogs->setMaximumSize(QSize(16777215, 300));
        gridLayout_6 = new QGridLayout(pnlLogs);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        logBoard = new QTextEdit(pnlLogs);
        logBoard->setObjectName(QString::fromUtf8("logBoard"));
        logBoard->setMaximumSize(QSize(16777215, 300));

        gridLayout_6->addWidget(logBoard, 0, 1, 1, 1);


        gridLayout->addWidget(pnlLogs, 3, 0, 1, 3);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        send->setDefault(true);
        btn_maximize->setDefault(true);
        btn_close->setDefault(true);
        btn_minimize->setDefault(true);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        actionNew_connect->setText(QApplication::translate("MainWindow", "New connect...", nullptr));
        actionExit->setText(QApplication::translate("MainWindow", "Exit", nullptr));
        send->setText(QApplication::translate("MainWindow", "Send", nullptr));
        btnShowLogs->setText(QApplication::translate("MainWindow", "Logs", nullptr));
        lineSearchUserList->setPlaceholderText(QApplication::translate("MainWindow", "Search...", nullptr));
        To_Ban_Button->setText(QApplication::translate("MainWindow", "To ban", nullptr));
        Mute_Button->setText(QApplication::translate("MainWindow", "Mute", nullptr));
        BtnUserControl->setText(QApplication::translate("MainWindow", "User control", nullptr));
        Disconnect->setText(QApplication::translate("MainWindow", "Disconnect", nullptr));
        lable_session_num->setText(QString());
        Connect->setText(QApplication::translate("MainWindow", "Connect", nullptr));
        StopSession->setText(QApplication::translate("MainWindow", "\320\236\321\201\321\202\320\260\320\275\320\276\320\262\320\270\321\202\321\214", nullptr));
        StartSession->setText(QApplication::translate("MainWindow", "\320\227\320\260\320\277\321\203\321\201\321\202\320\270\321\202\321\214", nullptr));
        label_2->setText(QString());
        ChatBtn->setText(QString());
        Settings->setText(QString());
        btn_maximize->setText(QString());
        btn_close->setText(QString());
        label->setText(QString());
        btn_minimize->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
