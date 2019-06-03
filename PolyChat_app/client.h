#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QtWebSockets/QWebSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QNetworkAccessManager>

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = 0);
    void connectSocket(const QString& host, unsigned int port = 5007);//facassanxt.ru:

    void sendMessage(const QString& message);
    void requestExternalAddress();

private:
    unsigned int _port;
    QString _host;
    QWebSocket *clientSocket;
    QNetworkAccessManager *manager;
    QString temp = "";
    QString ip;
    Client *downloader;

signals:
    void receiveMessage(QString message);
    void requestUsername();
    void receiveUserlist(QJsonArray array);
    void receiveServiceMessage(QString message);
    void onReady(QString);

private slots:
    void onReceiveMessage(QString message);
    void onDisconnected();
    void getResponse(QNetworkReply *reply);


};

#endif // CLIENT_H
