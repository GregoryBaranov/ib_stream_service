#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QtWebSockets/QWebSocket>

class Client : public QObject
{
    Q_OBJECT

public:
    explicit Client(QObject *parent = 0); // явный конструктор

    void connectSocket(const QString& host, unsigned int port); // функция установки соединения
    void sendMessage(const QString& message); // функция отправки сообщения

private:
    unsigned int _port;
    QString _host;
    QWebSocket *clientSocket;

signals:
    void receiveMessage(QString message); // сигнал для получения сообщения

private slots:
    void onReceiveMessage(QString message); // слот для приема сообщений
};

#endif // CLIENT_H
