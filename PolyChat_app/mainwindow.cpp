#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mainApplicationDesigner(); // Дефолтный фид приложения
    settingDesigner(); // Вид и проверки для hostEdit, spinPort, connect;
    btn_max(); // Кнопка каоторая отвечает за свёртывание и развертывание программы в маленький и большой режимы

    client = new Client(this);

    // connect для получения сообщений
    connect(client, SIGNAL(receiveMessage(QString)),
            this, SLOT(onReceiveMessage(QString)));

    // connect для кнопки подключиться
    connect(ui->connect, &QToolButton::clicked,
            this, &MainWindow::onConnectBtnClick);

    // connect для кнопки отключится
    connect(ui->Disconnect, &QToolButton::clicked,
            this, &MainWindow::onDisconnectBtnClick);

    // connect для кнопки отправить сообщение
    connect(ui->send, SIGNAL(clicked()),
            this, SLOT(onSendMessageBtnClick()));

    // connect для кнопки скрытия окна
    connect(ui->btn_minimize, &QToolButton::clicked,
            this, &MainWindow::showMinimized);

    // connect для кнопки закрытия приложения
    connect(ui->btn_close, &QToolButton::clicked,
            this, &MainWindow::close);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::settingDesigner() // Вид и проверки для hostEdit, spinPort, connect;
{
    /* Создаем строку для регулярного выражения */
    QString ipRange = "(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])";

    /* Создаем регулярное выражение с применением строки, как
     * повторяющегося элемента
     */
    QRegExp ipRegex ("^" + ipRange
                     + "\\." + ipRange
                     + "\\." + ipRange
                     + "\\." + ipRange + "$");

    // Создаем Валидатор регулярного выражения с применением
    // созданного регулярного выражения
    QRegExpValidator *ipValidator = new QRegExpValidator(ipRegex, this);

    /* Устанавливаем Валидатор на QLineEdit */
    ui->hostEdit->setValidator(ipValidator);
    ui->hostEdit->setPlaceholderText("127.0.0.1");
    ui->hostEdit->setText("31.10.65.179");

    ui->spinPort->setMaximum(999999999);
    ui->spinPort->setValue(5000);
}

void MainWindow::mainApplicationDesigner() // Дефолтный фид приложения
{
    // Убираем дефолтную строку заголовка и делаем ненужное пространство прозрачным
    this->setWindowFlag(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setStyleSheet("font: 12pt Microsoft YaHei UI;");

    // Логическая блокировка кнопок DarkDesign (семены темы) и Disconnect
    ui->Disconnect->setDisabled(true);
    ui->DarkDesign->setDisabled(true);

    // Выставление стиля для дефолтной темы "Dark"
    ui->hostEdit->setStyleSheet("background:#3d3d3d;");
    ui->spinPort->setStyleSheet("background:#3d3d3d;");
    ui->connect->setStyleSheet("background:#3d3d3d;");
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

    // Только для чтения информации
    ui->messageBoard->setReadOnly(true);
}

// Кнопка каоторая отвечает за свёртывание и развертывание программы в маленький и большой режимы
void MainWindow::btn_max()
{
    connect(ui->btn_maximize, &QToolButton::clicked, [this]()
    {
        // Если окно находится в максимально развернутом состоянии, то кнопка находится в режиме свертывания
        if (this->isMaximized())
        {
            ui->btn_maximize->setStyleSheet("background:#3d3d3d; background-image: url(:/image/window-maximize-gray.png);"
                                            "background-repeat: no-repeat; margin: 0px;");
            this->showNormal();
        }
        else
        {
            ui->btn_maximize->setStyleSheet("background:#3d3d3d; background-image: url(:/image/window-restore-gray.png); "
                                            "background-repeat: no-repeat; margin: 0px;");
            this->showMaximized();
        }
    });
}

void MainWindow::onConnectBtnClick() // Слот для кнопки соединения с сервером
{
    // Логическая блокировка кнопок connect и разблокировка Disconnect
    ui->connect->setDisabled(true);
    ui->Disconnect->setDisabled(false);

    ui->messageBoard->append("Connection attempt...");
    unsigned int port = ui->spinPort->value();
    client->connectSocket(ui->hostEdit->text(), port);

    connect(client, SIGNAL(disconnected()), client, SLOT(deleteLater()));
}

void MainWindow::onDisconnectBtnClick() // Слот для кнопки отключения от сервера (можно удалить)
{
    // Логическая блокировка кнопок Disconnect и разблокировка connect
    ui->connect->setDisabled(false);
    ui->Disconnect->setDisabled(true);

    client->sendMessage("Disconnect");
}

void MainWindow::onSendMessageBtnClick() // Слот для кнопки отправки сообщения
{
    if(ui->messageEdt->text() != "") // Проверка на пустое сообщение
    {
        client->sendMessage(ui->messageEdt->text()); // отправка сообщения
        ui->messageEdt->clear(); // очищение отправленного сообщения
    }
}

void MainWindow::onReceiveMessage(QString message) // Слот для получения сообщения
{
    QString fullMessage = QString("[%1] %2")
            .arg(QDateTime::currentDateTime().toString("hh:mm:ss")) // отображает время прихода сообщения
            .arg(message); // само сообщение

    ui->messageBoard->append(fullMessage); // отображение пришедшего сообщения
}

void MainWindow::on_Settings_clicked() // Слот для отображения/скрытия меню настроек
{
    if(ui->pnlSettings->isVisible()) // Если открыт то закрываем, иначе отображаем
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
    // Логическая блокировка кнопок DarkDesign (семены темы) и разблокировки WhiteDesign
    ui->DarkDesign->setDisabled(true);
    ui->WhiteDesign->setDisabled(false);

    // Выставление стиля для темы "Dark"
    ui->send->setStyleSheet("background:#3d3d3d; color: #fff; border: 2px solid #000;");
    ui->connect->setStyleSheet("background:#3d3d3d;");
    ui->messageEdt->setStyleSheet("background:#3d3d3d; color: #fff; border: 2px solid #000;");
    ui->hostEdit->setStyleSheet("background:#3d3d3d;");
    ui->spinPort->setStyleSheet("background:#3d3d3d;");
    ui->Disconnect->setStyleSheet("background:#3d3d3d;");
    ui->DarkDesign->setStyleSheet("background:#3d3d3d;");
    ui->WhiteDesign->setStyleSheet("background:#3d3d3d;");
    ui->messageBoard->setStyleSheet("background:rgba(62, 62, 62, 0.5); color: #fff; border: 2px solid #000;");
    ui->titleBar->setStyleSheet("background:rgba(62, 62, 62, 0.5); color: #fff; border: 2px solid #000;");
    ui->pnlSettings->setStyleSheet("background:rgba(62, 62, 62, 0.5); color: #fff; border: 2px solid #000;");
}

void MainWindow::on_WhiteDesign_clicked() // Слот для переключения на светлую тему
{
    // Логическая блокировка кнопок WhiteDesign (семены темы) и разблокировки DarkDesign
    ui->DarkDesign->setDisabled(false);
    ui->WhiteDesign->setDisabled(true);

    // Выставление стиля для темы "White"
    ui->send->setStyleSheet("background:#fff; color:#000;");
    ui->Disconnect->setStyleSheet("background:#fff;");
    ui->DarkDesign->setStyleSheet("background:#fff;");
    ui->WhiteDesign->setStyleSheet("background:#fff;");
    ui->connect->setStyleSheet("background:#fff;");
    ui->messageEdt->setStyleSheet("background:#fff; color:#000;");
    ui->hostEdit->setStyleSheet("background:#fff; border: 2px solid #000;");
    ui->spinPort->setStyleSheet("background:#fff; border: 2px solid #000;");
    ui->messageBoard->setStyleSheet("background:#fff; color:#000; border: 2px solid #000;");
    ui->titleBar->setStyleSheet("background:rgba(255, 255, 255); color: #000; border: 2px solid #000;");
    ui->pnlSettings->setStyleSheet("background:rgba(255, 255, 255); color: #000; border: 2px solid #000;");
}
