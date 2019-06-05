#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mainApplicationDesigner();
    settingDesigner();
    btn_max();

    client = new Client(this);

    connect(client, SIGNAL(receiveMessage(QString)),
            this, SLOT(onReceiveMessage(QString)));

    connect(client, SIGNAL(receiveServiceMessage(QString)),
            this, SLOT(onReceiveServiceMessage(QString)));

    connect(ui->connect, &QToolButton::clicked,
            this, &MainWindow::onConnectBtnClick);

    connect(ui->Disconnect, &QToolButton::clicked,
            this, &MainWindow::onDisconnectBtnClick);

    connect(ui->send, SIGNAL(clicked()),
            this, SLOT(onSendMessageBtnClick()));

    connect(ui->btn_minimize, &QToolButton::clicked,
            this, &MainWindow::showMinimized);

    connect(ui->btn_close, &QToolButton::clicked,
            this, &MainWindow::close);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::settingDesigner()
{
    ui->nameEdit->setStyleSheet("background:#3d3d3d; color:#fff;");
    ui->hostEdit->setStyleSheet("background:#3d3d3d;");

    ui->hostEdit->setStyleSheet("background:#3d3d3d;");
    ui->spinPort->setStyleSheet("background:#3d3d3d;");
    ui->connect->setStyleSheet("background:#3d3d3d;");

    ui->nameEdit->setPlaceholderText("Name");
    ui->hostEdit->setPlaceholderText("127.0.0.1");

    ui->hostEdit->setText("127.0.0.1");
    ui->spinPort->setMaximum(999999999);
    ui->spinPort->setValue(5000);
}

void MainWindow::mainApplicationDesigner()
{
    this->setWindowFlag(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setStyleSheet("font: 12pt Microsoft YaHei UI;");

    ui->Disconnect->setDisabled(true);
    ui->DarkDesign->setDisabled(true);

    ui->Settings->setStyleSheet("background:#3d3d3d; color:#fff;");
    ui->btn_close->setStyleSheet("background:#3d3d3d; background-image: url(:/image/close-gray.png);");
    ui->send->setStyleSheet("font: 12pt Microsoft YaHei UI; background:#3d3d3d; color: #fff; border: 2px solid #000;");
    ui->btn_maximize->setStyleSheet("background:#3d3d3d; background-image: url(:/image/window-maximize-gray.png);");
    ui->btn_minimize->setStyleSheet("background:#3d3d3d; background-image: url(:/image/window-minimize-gray.png);");
    ui->Disconnect->setStyleSheet("background:#3d3d3d;");
    ui->DarkDesign->setStyleSheet("background:#3d3d3d;");
    ui->WhiteDesign->setStyleSheet("background:#3d3d3d;");

    ui->messageEdt->setStyleSheet("background:#3d3d3d; color: #fff; border: 2px solid #000;");
    ui->messageBoard->setStyleSheet("background:rgba(62, 62, 62, 0.5); color: #fff; border: 2px solid #000;");
    ui->titleBar->setStyleSheet("background:rgba(62, 62, 62, 0.5); color: #fff; border: 2px solid #000;");
    ui->pnlSettings->setStyleSheet("background:rgba(62, 62, 62, 0.5); color: #fff; border: 2px solid #000;");
    ui->messageEdt->setPlaceholderText("Message...");
    ui->messageBoard->setReadOnly(true);
}

void MainWindow::btn_max()
{
    connect(ui->btn_maximize, &QToolButton::clicked, [this]()
    {
        if (this->isMaximized())
        {
            ui->btn_maximize->setStyleSheet("background:#3d3d3d; background-image: url(C:/GitHub/PolyChat/PolyChat_app/image/window-maximize-gray.png); background-repeat: no-repeat; margin: 0px;");
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
    ui->Disconnect->setDisabled(false);

    ui->messageBoard->append("Connection attempt...");
    unsigned int port = ui->spinPort->value();
    client->connectSocket(ui->hostEdit->text(), port);

    connect(client, SIGNAL(disconnected()), client, SLOT(deleteLater()));
}

void MainWindow::onDisconnectBtnClick() // Слот для кнопки отключения от сервера (можно удалить)
{
    ui->connect->setDisabled(false);
    ui->Disconnect->setDisabled(true);

    client->sendMessage("Disconnect");
}

void MainWindow::onSendMessageBtnClick() // Слот для кнопки отправки сообщения
{
    if(ui->messageEdt->text() != "")
    {
        client->sendMessage(ui->nameEdit->text() + ": " + ui->messageEdt->text());
        ui->messageEdt->clear();
    }
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
    else
    {
        ui->pnlSettings->show();
    }
}

void MainWindow::on_btn_close_clicked() // Слот для отключения от сервера
{
    client->sendMessage("Disconnect");
}

void MainWindow::on_DarkDesign_clicked() // Слот для переключения на темную тему
{
    ui->DarkDesign->setDisabled(true);
    ui->WhiteDesign->setDisabled(false);

    ui->send->setStyleSheet("background:#3d3d3d; color: #fff; border: 2px solid #000;");
    ui->connect->setStyleSheet("background:#3d3d3d;");

    ui->messageEdt->setStyleSheet("background:#3d3d3d; color: #fff; border: 2px solid #000;");
    ui->hostEdit->setStyleSheet("background:#3d3d3d;");
    ui->spinPort->setStyleSheet("background:#3d3d3d;");
    ui->Disconnect->setStyleSheet("background:#3d3d3d;");
    ui->DarkDesign->setStyleSheet("background:#3d3d3d;");
    ui->WhiteDesign->setStyleSheet("background:#3d3d3d;");

    ui->messageBoard->setStyleSheet("background:rgba(62, 62, 62, 0.5); color: #fff; border: 2px solid #000;");
    ui->nameEdit->setStyleSheet("background:#3d3d3d; color:#fff;");
    ui->titleBar->setStyleSheet("background:rgba(62, 62, 62, 0.5); color: #fff; border: 2px solid #000;");
    ui->pnlSettings->setStyleSheet("background:rgba(62, 62, 62, 0.5); color: #fff; border: 2px solid #000;");
}

void MainWindow::on_WhiteDesign_clicked() // Слот для переключения на светлую тему
{
    ui->DarkDesign->setDisabled(false);
    ui->WhiteDesign->setDisabled(true);

    ui->send->setStyleSheet("background:#fff; color:#000;");
    ui->Disconnect->setStyleSheet("background:#fff;");
    ui->DarkDesign->setStyleSheet("background:#fff;");
    ui->WhiteDesign->setStyleSheet("background:#fff;");
    ui->connect->setStyleSheet("background:#fff;");

    ui->messageEdt->setStyleSheet("background:#fff; color:#000;");
    ui->hostEdit->setStyleSheet("background:#fff; border: 2px solid #000;");
    ui->spinPort->setStyleSheet("background:#fff; border: 2px solid #000;");
    ui->messageBoard->setStyleSheet("background:#fff; color:#000; border: 2px solid #000;");
    ui->nameEdit->setStyleSheet("background:#fff; color:#000; border: 2px solid #000;");
    ui->titleBar->setStyleSheet("background:rgba(255, 255, 255); color: #000; border: 2px solid #000;");
    ui->pnlSettings->setStyleSheet("background:rgba(255, 255, 255); color: #000; border: 2px solid #000;");
}
