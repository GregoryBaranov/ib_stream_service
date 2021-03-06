#include "client.h"
#include "mainwindow.h"
#include <QMaskGenerator>
#include <smart_pointer.h>

Client::Client(QObject *parent) : QObject(parent)
{
    popUp = new PopUp();
    checkConnect = FAILURE_CONNECT;

    clientSocket = new QWebSocket();
    connect(clientSocket, SIGNAL(textMessageReceived(QString)), this, SLOT(onReceiveMessage(QString)));

    manager = new QNetworkAccessManager();
    connect(manager, &QNetworkAccessManager::finished, this, &Client::onResult);

    connect(this, SIGNAL(onReady(QString)),this,SLOT(reciveBuf(QString)));
}

Client::~Client(){}

void Client::chatData()
{
    QUrl url("http://" + _host + ":" + QString::fromStdString(to_string(_port)) + "/id_ses");
    QNetworkRequest request;
    request.setUrl(url);
    manager->get(request);
}

void Client::onResult(QNetworkReply *reply)
{
    smart_pointer<MainWindow> wind(new MainWindow());
//    MainWindow *wind = new MainWindow;
    if(reply->error())
    {
        if (checkConnect == FAILURE_CONNECT)
        {
            wind->FailedConnect();
            qDebug() << reply->errorString();

            popUp->setPopupText("ERROR: "+reply->errorString());
            popUp->show();

            checkConnect = FAILURE_CONNECT;
        }
    }
    else
    {
        QString buf = reply->readAll();
        qDebug() << buf;
        emit onReady(buf);
    }
}


void Client::reciveBuf(QString buf)
{
    QString NumSession = buf;

    if (clientSocket != nullptr && clientSocket->isValid())
    {
        return; // Необходимо проверить и закрыть (или вернуть) соединение, если оно открыто
    }

    QUrl qUrl;
    qUrl.setPort((int)_port); // выставление порта
    qUrl.setHost(_host); // выставление адреса
    qUrl.setScheme("ws"); // выставление адресации
    qUrl.setPath("/" + NumSession); // выставление номера трансляции + NumSession

    emit newNumberSession(NumSession);

    clientSocket->open(qUrl); // открытие соединения с сервером

    checkConnect = SUCCESS_CONNECT;
}

void Client::clientDisconnect()
{
    checkConnect = FAILURE_CONNECT;
}

void Client::connectSocket(const QString& host, unsigned int port) // Соединяется с сервером
{
    checkConnect = FAILURE_CONNECT;

    _port = port;
    _host = host;
    Client::chatData();
}

void Client::sendMessage(const QString& message) // Отправляет текстовое сообщение
{
    clientSocket->sendTextMessage(message); // отправка текста
}

void Client::onReceiveMessage(QString message) // Слот для приема сообщений
{
    emit receiveMessage(message); // перенвправление сообщения в cлот для получения сообщения
}
