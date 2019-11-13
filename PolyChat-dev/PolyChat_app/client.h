#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QtWebSockets/QWebSocket>
#include <ctime>
#include <random>
#include <QVariant>
#include <QAbstractSocket>

class Client : public QObject
{
    Q_OBJECT

public:
    explicit Client(QObject *parent = 0); // явный конструктор
    ~Client();

    void connectSocket(const QString& host, unsigned int port); // функция установки соединения
    void sendMessage(const QString& message); // функция отправки сообщения
    template<class T1, class T2>
    T1 generateSessionNumber(T1 rng, T2 range);

private:
    unsigned int _port;
    QString _host;
    QWebSocket *clientSocket;
    int *Namber;

signals:
    void receiveMessage(QString message); // сигнал для получения сообщения
    void newNumberSession(QString num_session);
    void failedConnect();

private slots:
    void onReceiveMessage(QString message); // слот для приема сообщений
};

#endif // CLIENT_H
