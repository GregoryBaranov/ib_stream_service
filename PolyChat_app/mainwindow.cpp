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

    btn_max();

    ui->btn_maximize->setStyleSheet("background:#3d3d3d; background-image: url(C:/GitHub/PolyChat/PolyChat_app/image/window-maximize-gray.png); background-repeat: no-repeat; margin: 0px;");
    ui->Settings->setStyleSheet("background:#3d3d3d; color:#fff;");
    ui->hostEdit->setStyleSheet("background:#3d3d3d;");
    ui->spinPort->setStyleSheet("background:#3d3d3d;");
    ui->connect->setStyleSheet("background:#3d3d3d;");

    ui->messageBoard->setStyleSheet("background:rgba(62, 62, 62, 0.5); color: #fff; border: 1px solid #000;");
    this->setStyleSheet("font: 12pt Microsoft YaHei UI;");

    ui->nameEdit->setStyleSheet("background:#3d3d3d; color:#fff;");
    ui->nameEdit->setPlaceholderText("Name");

    client = new Client(this);

    ui->hostEdit->setText("31.10.65.179");
    ui->spinPort->setMaximum(999999999);
    ui->spinPort->setValue(5000);

    ui->send->setDisabled(true);
    ui->Disconnect->hide();

    connect(client, SIGNAL(receiveMessage(QString)),
            this, SLOT(onReceiveMessage(QString)));
    connect(client, SIGNAL(receiveServiceMessage(QString)),
            this, SLOT(onReceiveServiceMessage(QString)));

}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::btn_max() //?
{
    connect(ui->btn_maximize, &QToolButton::clicked, [this]()
    {
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


void MainWindow::onConnectBtnClick() // Слот для кнопки соединения с сервером
{
    ui->connect->setDisabled(true);
    ui->send->setDisabled(false);
    ui->messageBoard->append("Connection attempt...");
    unsigned int port = ui->spinPort->value();
    client->connectSocket(ui->hostEdit->text(), port);
}


void MainWindow::onDisconnectBtnClick() // Слот для кнопки отключения от сервера (можно удалить)
{
    client->sendMessage("Disconnect");
    ui->messageBoard->append("Disconnect attempt...");
    ui->send->setDisabled(true);
    client->disconnectSocket();
    client->deleteLater();
}


void MainWindow::onSendMessageBtnClick() // Слот для кнопки отправки сообщения
{

    client->sendMessage(ui->nameEdit->text() + ": " + ui->messageEdt->text());
    ui->messageEdt->clear();

}


void MainWindow::onReceiveMessage(QString message) // Слот для получения сообщения
{
    QString fullMessage = QString("[%1] %2")
            .arg(QDateTime::currentDateTime().toString("hh:mm:ss"))
            .arg(message);

    ui->messageBoard->append(fullMessage);
}


void MainWindow::onReceiveServiceMessage(QString message) // Слот для получения сервисного сообщения
{
    ui->messageBoard->append(message);
}


void MainWindow::on_Settings_clicked() // Слот для отображения/скрытия меню настроек
{
    if(ui->pnlSettings->isVisible())
    {
        ui->pnlSettings->hide();
    }
    else {
        ui->pnlSettings->show();
    }
}


void MainWindow::on_HideSettings_clicked()  // Слот для скрытия меню настроек
{
    ui->Settings->show();
}


void MainWindow::on_btn_close_clicked() // Слот для отключения от сервера
{
    client->sendMessage("Disconnect");
}


void MainWindow::on_DarkDesign_clicked() // Слот для переключения на темную тему
{
    ui->messageEdt->setStyleSheet("font: 12pt Microsoft YaHei UI; background:#3d3d3d; color: #fff;");
    ui->send->setStyleSheet("font: 12pt Microsoft YaHei UI; background:#3d3d3d; color: #fff;");
    ui->hostEdit->setStyleSheet("background:#3d3d3d;");
    ui->spinPort->setStyleSheet("background:#3d3d3d;");
    ui->connect->setStyleSheet("background:#3d3d3d;");
    //ui->groupBox->setStyleSheet("background:rgba(62, 62, 62, 0.5); color: #fff; border: 1px solid #000;");
    ui->messageBoard->setStyleSheet("background:rgba(62, 62, 62, 0.5); color: #fff; border: 1px solid #000;");
    ui->nameEdit->setStyleSheet("background:#3d3d3d; color:#fff;");

}


void MainWindow::on_WhiteDesign_clicked() // Слот для переключения на светлую тему
{
    ui->messageEdt->setStyleSheet("font: 12pt Microsoft YaHei UI; background:#fff; color:#000;");
    ui->send->setStyleSheet("font: 12pt Microsoft YaHei UI; background:#fff; color:#000;");
    ui->hostEdit->setStyleSheet("background:#fff; border: 1px solid #000;");
    ui->spinPort->setStyleSheet("background:#fff; border: 1px solid #000;");
    ui->connect->setStyleSheet("background:#fff;");
    ui->messageBoard->setStyleSheet("background:#fff; color:#000; border: 1px solid #000;");
    ui->nameEdit->setStyleSheet("background:#fff; color:#000; border: 1px solid #000;");
}
