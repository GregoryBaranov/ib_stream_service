#include "client.h"

Client::Client(QObject *parent) : QObject(parent)
{
    clientSocket = new QWebSocket();

    connect(clientSocket, SIGNAL(textMessageReceived(QString)), this, SLOT(onReceiveMessage(QString)));
}

void Client::connectSocket(const QString& host, unsigned int port) // Соединяется с сервером
{
    if (clientSocket != NULL && clientSocket->isValid())
    {
        return; // Необходимо проверить и закрыть (или вернуть) соединение, если оно открыто
    }

    // Передаю значения порта и адреса
    _port = port;
    _host = host;

    QUrl qUrl;
    qUrl.setPort(_port); // выставление порта
    qUrl.setHost(_host); // выставление адреса
    qUrl.setScheme("ws"); // выставление адресации

    clientSocket->open(qUrl); // открытие соединения с сервером
}

void Client::sendMessage(const QString& message) // Отправляет текстовое сообщение
{
    clientSocket->sendTextMessage(message); // отправка текста
}

void Client::onReceiveMessage(QString message) // Слот для приема сообщений
{
    emit receiveMessage(message); // перенвправление сообщения в cлот для получения сообщения
}
