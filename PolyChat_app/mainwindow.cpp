#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowFlag(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setMouseTracking(true);   // Включаем отслеживание курсора без нажатых кнопокы

    ui->pushButton->setStyleSheet("background:#3d3d3d; background-image: url(C:/GitHub/QWebSocket/Qt-WebSocket-JSON-Chat/ChatClient/image/exit.png); background-repeat: no-repeat");


    hostEdt = new QLineEdit(this);
    hostEdt->setGeometry(10,360,480,30);
    hostEdt->setText("facassanxt.ru");// facassanxt.ru
    hostEdt->setText("10.66.16.255");
    hostEdt->hide();

    messageEdt = new QLineEdit(this);
    messageEdt->setGeometry(0,360,520,40);
    messageEdt->setStyleSheet("font: 12pt Microsoft YaHei UI; background:#3d3d3d; color: #fff;");

    sendMessageBtn = new QPushButton(this);
    sendMessageBtn->setGeometry(529,360,100,40);
    sendMessageBtn->setText("Send");
    sendMessageBtn->setStyleSheet("font: 12pt Microsoft YaHei UI; background:#3d3d3d; color: #fff;");
    connect(sendMessageBtn, SIGNAL(clicked()), this, SLOT(onSendMessageBtnClick()));

    messageBoard = new QTextEdit(this);
    messageBoard->setGeometry(0,50,620,300);
    messageBoard->setDisabled(true);
    messageBoard->setStyleSheet("background:rgba(62, 62, 62, 0.5); color: #fff; border: 1px solid #000;");
    this->setStyleSheet("font: 12pt Microsoft YaHei UI;");


//    QWidget::grabMouse () - когда начинаете перемещение
//    QWidget::releaseMouse () - когда завершаете перемещение


    client = new Client(this);
    connect(client, SIGNAL(receiveMessage(QString)), this, SLOT(onReceiveMessage(QString)));
    connect(client, SIGNAL(receiveServiceMessage(QString)), this, SLOT(onReceiveServiceMessage(QString)));

    client->connectSocket(hostEdt->text());

}

MainWindow::~MainWindow()
{
    delete ui;
}

// Слот для кнопки соединения с сервером

void MainWindow::onConnectBtnClick()
{
//    messageBoard->append("Connection attempt...");
//    client->connectSocket(hostEdt->text());
}

// Слот для кнопки отправки сообщения

void MainWindow::onSendMessageBtnClick()
{
    if (client != NULL && messageEdt->text() != "")
    {
        client->sendMessage( messageEdt->text());
        messageEdt->clear();
    }
}

// Слот для получения сообщения

void MainWindow::onReceiveMessage(QString message)
{
   QString fullMessage = QString("[%1]: %2")
           .arg(QDateTime::currentDateTime().toString("hh:mm:ss"))
           .arg(message);

   messageBoard->append(fullMessage);
}



// Слот для получения сервисного сообщения

void  MainWindow::onReceiveServiceMessage(QString message)
{
    messageBoard->append(message);
}



//void MainWindow::on_actionNew_connect_triggered()
//{
//    messageBoard->append("Connection attempt...");
//    client->connectSocket(hostEdt->text());
//}



void MainWindow::on_pushButton_clicked()
{
    close();
}




