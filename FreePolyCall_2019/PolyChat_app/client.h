#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QtWebSockets/QWebSocket>
#include <ctime>
#include <random>
#include <QVariant>
#include <QAbstractSocket>

using namespace std;


class Client : public QObject
{
    Q_OBJECT

public:
    explicit Client(QObject *parent = nullptr); // явный конструктор
    ~Client();

    void connectSocket(const QString& host, unsigned int port); // функция установки соединения
    void sendMessage(const QString& message); // функция отправки сообщения

private:
    QNetworkAccessManager *manager;
    unsigned int _port;
    QString _host;
    QWebSocket *clientSocket;
    int *Namber;

    template<class T1, class T2>
    T1 generateSessionNumber(T1 rng, T2 range);

    template<class T1, class T2>
    bool checkUserInList(const list<T1> &lst, T2 username); // проверка есть юзер или нет

signals:
    void receiveMessage(QString message); // сигнал для получения сообщения
    void newNumberSession(QString num_session);
    void checkConnection();
    void onReady(QString);

private slots:
    void onReceiveMessage(QString message); // слот для приема сообщений
    void chatData();
    void onResult(QNetworkReply *reply);
    void reciveBuf(QString);
};

#endif // CLIENT_H
