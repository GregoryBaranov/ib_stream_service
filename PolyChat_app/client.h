#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QtWebSockets/QWebSocket>

class Client : public QObject
{
    Q_OBJECT

public:
    explicit Client(QObject *parent = 0);

    void connectSocket(const QString& host, unsigned int port); //facassanxt.ru:
    void sendMessage(const QString& message);

private:
    unsigned int _port;
    QString _host;
    QWebSocket *clientSocket;

signals:
    void receiveMessage(QString message);

private slots:
    void onReceiveMessage(QString message);
};

#endif // CLIENT_H
