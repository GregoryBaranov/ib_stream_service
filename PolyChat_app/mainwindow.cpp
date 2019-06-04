#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QInputDialog>
#include "client.h"

#include <QFileDialog>
#include <QDir>
#include <QGraphicsDropShadowEffect>
#include <QToolButton>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowFlag(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setMouseTracking(true);   // Включаем отслеживание курсора без нажатых кнопокы

    ui->btn_close->setStyleSheet("background:#3d3d3d; background-image: url(C:/GitHub/PolyChat/PolyChat_app/image/close-gray.png); margin: 0px; border: 0px; ");

    connect(ui->btn_close, &QToolButton::clicked, this, &MainWindow::close);

    ui->messageEdt->setStyleSheet("font: 12pt Microsoft YaHei UI; background:#3d3d3d; color: #fff;");
    ui->messageEdt->setPlaceholderText("Message...");


    ui->send->setStyleSheet("font: 12pt Microsoft YaHei UI; background:#3d3d3d; color: #fff;");

    connect(ui->send, SIGNAL(clicked()), this, SLOT(onSendMessageBtnClick()));

     connect(ui->btn_minimize, &QToolButton::clicked, this, &MainWindow::showMinimized);
     ui->btn_minimize->setStyleSheet("background:#3d3d3d; background-image: url(C:/GitHub/PolyChat/PolyChat_app/image/window-minimize-gray.png); icon-size: 12px; margin: 0px;");

     connect(ui->connect, &QToolButton::clicked, this, &MainWindow::onConnectBtnClick);
     connect(ui->Disconnect, &QToolButton::clicked, this, &MainWindow::onDisconnectBtnClick);



     ui->btn_maximize->setStyleSheet("background:#3d3d3d; background-image: url(C:/GitHub/PolyChat/PolyChat_app/image/window-maximize-gray.png); background-repeat: no-repeat; margin: 0px;");

     btn_max();




    ui->Settings->setStyleSheet("background:#3d3d3d; color:#fff;");
    ui->hostEdit->setStyleSheet("background:#3d3d3d;");
    ui->spinPort->setStyleSheet("background:#3d3d3d;");
    ui->connect->setStyleSheet("background:#3d3d3d;");
    ui->HideSettings->setStyleSheet("background:#3d3d3d; color: #fff;");
     ui->groupBox->setStyleSheet("background:rgba(62, 62, 62, 0.5); color: #fff; border: 1px solid #000;");


    ui->messageBoard->setStyleSheet("background:rgba(62, 62, 62, 0.5); color: #fff; border: 1px solid #000;");
    this->setStyleSheet("font: 12pt Microsoft YaHei UI;");

    ui->nameEdit->setStyleSheet("background:#3d3d3d; color:#fff;");
     ui->nameEdit->setPlaceholderText("Name");

    client = new Client(this);
    connect(client, SIGNAL(receiveMessage(QString)), this, SLOT(onReceiveMessage(QString)));
    connect(client, SIGNAL(receiveServiceMessage(QString)), this, SLOT(onReceiveServiceMessage(QString)));

    ui->hostEdit->setText("31.10.65.179");
    ui->spinPort->setMaximum(999999999);
    ui->spinPort->setValue(5000);

//    unsigned int port = ui->spinPort->value();

//    client->connectSocket(ui->hostEdit->text(), port);


     ui->groupBox->hide();
     ui->send->setDisabled(true);
     ui->Disconnect->hide();
     ui->HideSettings->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::btn_max(){

        connect(ui->btn_maximize, &QToolButton::clicked, [this](){
            if (this->isMaximized())
            {
                ui->btn_maximize->setStyleSheet(" background:#3d3d3d; background-image: url(C:/GitHub/PolyChat/PolyChat_app/image/window-maximize-gray.png); background-repeat: no-repeat; margin: 0px;");
                this->showNormal();
            }
            else
            {
                ui->btn_maximize->setStyleSheet("background:#3d3d3d; background-image: url(C:/GitHub/PolyChat/PolyChat_app/image/window-restore-gray.png); background-repeat: no-repeat; margin: 0px;");
                this->showMaximized();
            }
        });


}

// Слот для кнопки соединения с сервером

void MainWindow::onConnectBtnClick()
{
    ui->connect->setDisabled(true);
    ui->send->setDisabled(false);
    ui->messageBoard->append("Connection attempt...");
    unsigned int port = ui->spinPort->value();
    client->connectSocket(ui->hostEdit->text(), port);
}

void MainWindow::onDisconnectBtnClick(){
    client->sendMessage("Disconnect");
    ui->messageBoard->append("Disconnect attempt...");
    ui->send->setDisabled(true);
    client->disconnectSocket();
    client->deleteLater();
}

// Слот для кнопки отправки сообщения

void MainWindow::onSendMessageBtnClick()
{

        client->sendMessage(ui->nameEdit->text() + ": " + ui->messageEdt->text());
        ui->messageEdt->clear();

}

// Слот для получения сообщения

void MainWindow::onReceiveMessage(QString message)
{
   QString fullMessage = QString("[%1] %2")
           .arg(QDateTime::currentDateTime().toString("hh:mm:ss"))
           .arg(message);

   ui->messageBoard->append(fullMessage);
}



// Слот для получения сервисного сообщения

void  MainWindow::onReceiveServiceMessage(QString message)
{
    ui->messageBoard->append(message);
}

void MainWindow::on_Settings_clicked()
{
    ui->groupBox->show();
    ui->Settings->hide();
     ui->HideSettings->show();
}



void MainWindow::on_HideSettings_clicked()
{
    ui->groupBox->hide();
    ui->HideSettings->hide();
    ui->Settings->show();
}


void MainWindow::on_btn_close_clicked()
{
        client->sendMessage("Disconnect");
}



void MainWindow::on_DarkDesign_clicked()
{
    ui->messageEdt->setStyleSheet("font: 12pt Microsoft YaHei UI; background:#3d3d3d; color: #fff;");
    ui->send->setStyleSheet("font: 12pt Microsoft YaHei UI; background:#3d3d3d; color: #fff;");
    ui->hostEdit->setStyleSheet("background:#3d3d3d;");
    ui->spinPort->setStyleSheet("background:#3d3d3d;");
    ui->connect->setStyleSheet("background:#3d3d3d;");
    ui->groupBox->setStyleSheet("background:rgba(62, 62, 62, 0.5); color: #fff; border: 1px solid #000;");
    ui->messageBoard->setStyleSheet("background:rgba(62, 62, 62, 0.5); color: #fff; border: 1px solid #000;");
    ui->nameEdit->setStyleSheet("background:#3d3d3d; color:#fff;");

}

void MainWindow::on_WhiteDesign_clicked()
{
    ui->messageEdt->setStyleSheet("font: 12pt Microsoft YaHei UI; background:#fff; color:#000;");
    ui->send->setStyleSheet("font: 12pt Microsoft YaHei UI; background:#fff; color:#000;");
    ui->hostEdit->setStyleSheet("background:#fff; border: 1px solid #000;");
    ui->spinPort->setStyleSheet("background:#fff; border: 1px solid #000;");
    ui->connect->setStyleSheet("background:#fff;");
    ui->groupBox->setStyleSheet("background:#fff; color:#000; border: 1px solid #000;");
    ui->messageBoard->setStyleSheet("background:#fff; color:#000; border: 1px solid #000;");
    ui->nameEdit->setStyleSheet("background:#fff; color:#000; border: 1px solid #000;");

}
