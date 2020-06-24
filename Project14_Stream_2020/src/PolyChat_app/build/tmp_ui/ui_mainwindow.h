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
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNew_connect;
    QAction *actionExit;
    QWidget *centralWidget;
    QGridLayout *gridLayout_4;
    QWidget *pnlChat;
    QGridLayout *gridLayout_5;
    QTextEdit *messageEdit;
    QPushButton *send;
    QListView *MessageBoardList;
    QWidget *pnlStream;
    QGridLayout *gridLayout_7;
    QPushButton *StartSession;
    QPushButton *StopSession;
    QLabel *label_2;
    QWidget *titleBar;
    QGridLayout *gridLayout_2;
    QPushButton *ChatBtn;
    QPushButton *Settings;
    QPushButton *btn_maximize;
    QPushButton *btn_close;
    QLabel *label;
    QPushButton *btn_minimize;
    QStackedWidget *sattingStackedWidget;
    QWidget *page;
    QGridLayout *gridLayout;
    QPushButton *BtnUserControl;
    QGroupBox *groupBoxHost;
    QGridLayout *gridLayout_9;
    QLineEdit *hostEdit;
    QPushButton *Disconnect;
    QSpacerItem *verticalSpacer;
    QGroupBox *groupBoxTitleSession;
    QGridLayout *gridLayout_10;
    QLineEdit *TitleEdit;
    QPushButton *Connect;
    QGroupBox *groupBoxPort;
    QGridLayout *gridLayout_3;
    QSpinBox *spinPort;
    QGroupBox *groupBoxNumSession;
    QGridLayout *gridLayout_8;
    QLineEdit *lable_session_num;
    QWidget *page_2;
    QGridLayout *gridLayout_6;
    QPushButton *closeUserListPanel;
    QLineEdit *lineSearchUserList;
    QListWidget *listViewUser;
    QPushButton *Mute_Button;
    QPushButton *To_Ban_Button;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1167, 701);
        actionNew_connect = new QAction(MainWindow);
        actionNew_connect->setObjectName(QString::fromUtf8("actionNew_connect"));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout_4 = new QGridLayout(centralWidget);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        pnlChat = new QWidget(centralWidget);
        pnlChat->setObjectName(QString::fromUtf8("pnlChat"));
        pnlChat->setMaximumSize(QSize(500, 16777215));
        gridLayout_5 = new QGridLayout(pnlChat);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        messageEdit = new QTextEdit(pnlChat);
        messageEdit->setObjectName(QString::fromUtf8("messageEdit"));
        messageEdit->setMaximumSize(QSize(16777215, 60));

        gridLayout_5->addWidget(messageEdit, 1, 0, 1, 1);

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


        gridLayout_4->addWidget(pnlChat, 1, 1, 1, 1);

        pnlStream = new QWidget(centralWidget);
        pnlStream->setObjectName(QString::fromUtf8("pnlStream"));
        gridLayout_7 = new QGridLayout(pnlStream);
        gridLayout_7->setSpacing(6);
        gridLayout_7->setContentsMargins(11, 11, 11, 11);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        StartSession = new QPushButton(pnlStream);
        StartSession->setObjectName(QString::fromUtf8("StartSession"));
        StartSession->setMinimumSize(QSize(0, 40));

        gridLayout_7->addWidget(StartSession, 1, 0, 1, 1);

        StopSession = new QPushButton(pnlStream);
        StopSession->setObjectName(QString::fromUtf8("StopSession"));
        StopSession->setMinimumSize(QSize(0, 40));

        gridLayout_7->addWidget(StopSession, 1, 1, 1, 1);

        label_2 = new QLabel(pnlStream);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setPixmap(QPixmap(QString::fromUtf8("../../../../Users/swall/Desktop/LOGOPOLIKEK.png")));

        gridLayout_7->addWidget(label_2, 0, 0, 1, 2);


        gridLayout_4->addWidget(pnlStream, 1, 0, 1, 1);

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


        gridLayout_4->addWidget(titleBar, 0, 0, 1, 3);

        sattingStackedWidget = new QStackedWidget(centralWidget);
        sattingStackedWidget->setObjectName(QString::fromUtf8("sattingStackedWidget"));
        sattingStackedWidget->setMaximumSize(QSize(302, 16777215));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        gridLayout = new QGridLayout(page);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        BtnUserControl = new QPushButton(page);
        BtnUserControl->setObjectName(QString::fromUtf8("BtnUserControl"));
        BtnUserControl->setMinimumSize(QSize(0, 40));
        BtnUserControl->setMaximumSize(QSize(280, 16777215));

        gridLayout->addWidget(BtnUserControl, 9, 0, 1, 2);

        groupBoxHost = new QGroupBox(page);
        groupBoxHost->setObjectName(QString::fromUtf8("groupBoxHost"));
        groupBoxHost->setMaximumSize(QSize(16777215, 100));
        gridLayout_9 = new QGridLayout(groupBoxHost);
        gridLayout_9->setSpacing(6);
        gridLayout_9->setContentsMargins(11, 11, 11, 11);
        gridLayout_9->setObjectName(QString::fromUtf8("gridLayout_9"));
        hostEdit = new QLineEdit(groupBoxHost);
        hostEdit->setObjectName(QString::fromUtf8("hostEdit"));
        hostEdit->setMinimumSize(QSize(0, 40));
        hostEdit->setMaximumSize(QSize(280, 16777215));

        gridLayout_9->addWidget(hostEdit, 0, 0, 1, 1);


        gridLayout->addWidget(groupBoxHost, 1, 0, 1, 2);

        Disconnect = new QPushButton(page);
        Disconnect->setObjectName(QString::fromUtf8("Disconnect"));
        Disconnect->setMinimumSize(QSize(0, 40));
        Disconnect->setMaximumSize(QSize(140, 16777215));

        gridLayout->addWidget(Disconnect, 8, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 10, 0, 1, 2);

        groupBoxTitleSession = new QGroupBox(page);
        groupBoxTitleSession->setObjectName(QString::fromUtf8("groupBoxTitleSession"));
        groupBoxTitleSession->setMaximumSize(QSize(16777215, 100));
        gridLayout_10 = new QGridLayout(groupBoxTitleSession);
        gridLayout_10->setSpacing(6);
        gridLayout_10->setContentsMargins(11, 11, 11, 11);
        gridLayout_10->setObjectName(QString::fromUtf8("gridLayout_10"));
        TitleEdit = new QLineEdit(groupBoxTitleSession);
        TitleEdit->setObjectName(QString::fromUtf8("TitleEdit"));
        TitleEdit->setMinimumSize(QSize(0, 40));
        TitleEdit->setMaximumSize(QSize(280, 16777215));

        gridLayout_10->addWidget(TitleEdit, 0, 0, 1, 1);


        gridLayout->addWidget(groupBoxTitleSession, 0, 0, 1, 2);

        Connect = new QPushButton(page);
        Connect->setObjectName(QString::fromUtf8("Connect"));
        Connect->setMinimumSize(QSize(0, 40));
        Connect->setMaximumSize(QSize(140, 16777215));

        gridLayout->addWidget(Connect, 8, 1, 1, 1);

        groupBoxPort = new QGroupBox(page);
        groupBoxPort->setObjectName(QString::fromUtf8("groupBoxPort"));
        groupBoxPort->setMinimumSize(QSize(70, 0));
        groupBoxPort->setMaximumSize(QSize(16777215, 100));
        gridLayout_3 = new QGridLayout(groupBoxPort);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        spinPort = new QSpinBox(groupBoxPort);
        spinPort->setObjectName(QString::fromUtf8("spinPort"));
        spinPort->setMinimumSize(QSize(0, 40));
        spinPort->setMaximumSize(QSize(16777215, 16777215));

        gridLayout_3->addWidget(spinPort, 0, 0, 1, 1);


        gridLayout->addWidget(groupBoxPort, 2, 0, 1, 2);

        groupBoxNumSession = new QGroupBox(page);
        groupBoxNumSession->setObjectName(QString::fromUtf8("groupBoxNumSession"));
        groupBoxNumSession->setMinimumSize(QSize(70, 100));
        groupBoxNumSession->setMaximumSize(QSize(16777215, 100));
        gridLayout_8 = new QGridLayout(groupBoxNumSession);
        gridLayout_8->setSpacing(6);
        gridLayout_8->setContentsMargins(11, 11, 11, 11);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        lable_session_num = new QLineEdit(groupBoxNumSession);
        lable_session_num->setObjectName(QString::fromUtf8("lable_session_num"));
        lable_session_num->setMinimumSize(QSize(130, 40));
        lable_session_num->setMaximumSize(QSize(16777215, 16777215));

        gridLayout_8->addWidget(lable_session_num, 0, 0, 1, 1);


        gridLayout->addWidget(groupBoxNumSession, 3, 0, 1, 2);

        sattingStackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        gridLayout_6 = new QGridLayout(page_2);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        closeUserListPanel = new QPushButton(page_2);
        closeUserListPanel->setObjectName(QString::fromUtf8("closeUserListPanel"));
        closeUserListPanel->setMinimumSize(QSize(0, 40));

        gridLayout_6->addWidget(closeUserListPanel, 0, 0, 1, 2);

        lineSearchUserList = new QLineEdit(page_2);
        lineSearchUserList->setObjectName(QString::fromUtf8("lineSearchUserList"));
        lineSearchUserList->setMinimumSize(QSize(0, 40));

        gridLayout_6->addWidget(lineSearchUserList, 1, 0, 1, 2);

        listViewUser = new QListWidget(page_2);
        listViewUser->setObjectName(QString::fromUtf8("listViewUser"));

        gridLayout_6->addWidget(listViewUser, 2, 0, 1, 2);

        Mute_Button = new QPushButton(page_2);
        Mute_Button->setObjectName(QString::fromUtf8("Mute_Button"));
        Mute_Button->setMinimumSize(QSize(130, 40));
        Mute_Button->setMaximumSize(QSize(16777215, 16777215));

        gridLayout_6->addWidget(Mute_Button, 3, 0, 1, 1);

        To_Ban_Button = new QPushButton(page_2);
        To_Ban_Button->setObjectName(QString::fromUtf8("To_Ban_Button"));
        To_Ban_Button->setMinimumSize(QSize(130, 40));
        To_Ban_Button->setMaximumSize(QSize(16777215, 16777215));

        gridLayout_6->addWidget(To_Ban_Button, 3, 1, 1, 1);

        sattingStackedWidget->addWidget(page_2);

        gridLayout_4->addWidget(sattingStackedWidget, 1, 2, 1, 1);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        send->setDefault(true);
        btn_maximize->setDefault(true);
        btn_close->setDefault(true);
        btn_minimize->setDefault(true);
        sattingStackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        actionNew_connect->setText(QApplication::translate("MainWindow", "New connect...", nullptr));
        actionExit->setText(QApplication::translate("MainWindow", "Exit", nullptr));
        send->setText(QApplication::translate("MainWindow", "Send", nullptr));
        StartSession->setText(QApplication::translate("MainWindow", "\320\227\320\260\320\277\321\203\321\201\321\202\320\270\321\202\321\214", nullptr));
        StopSession->setText(QApplication::translate("MainWindow", "\320\236\321\201\321\202\320\260\320\275\320\276\320\262\320\270\321\202\321\214", nullptr));
        label_2->setText(QString());
        ChatBtn->setText(QString());
        Settings->setText(QString());
        btn_maximize->setText(QString());
        btn_close->setText(QString());
        label->setText(QString());
        btn_minimize->setText(QString());
        BtnUserControl->setText(QApplication::translate("MainWindow", "User control", nullptr));
        groupBoxHost->setTitle(QApplication::translate("MainWindow", "\320\245\320\276\321\201\321\202:", nullptr));
        Disconnect->setText(QApplication::translate("MainWindow", "Disconnect", nullptr));
        groupBoxTitleSession->setTitle(QApplication::translate("MainWindow", "\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265 \321\201\320\265\321\201\321\201\320\270\320\270:", nullptr));
        Connect->setText(QApplication::translate("MainWindow", "Connect", nullptr));
        groupBoxPort->setTitle(QApplication::translate("MainWindow", "\320\237\320\276\321\200\321\202:", nullptr));
        groupBoxNumSession->setTitle(QApplication::translate("MainWindow", "\342\204\226 \321\201\320\265\321\201\321\201\320\270\320\270:", nullptr));
        closeUserListPanel->setText(QApplication::translate("MainWindow", "Exit ", nullptr));
        lineSearchUserList->setPlaceholderText(QApplication::translate("MainWindow", "Search...", nullptr));
        Mute_Button->setText(QApplication::translate("MainWindow", "Mute", nullptr));
        To_Ban_Button->setText(QApplication::translate("MainWindow", "Ban", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
