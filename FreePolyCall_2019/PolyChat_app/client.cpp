#include "client.h"
#include <QMaskGenerator>

Client::Client(QObject *parent) : QObject(parent)
{
    clientSocket = new QWebSocket();

    connect(clientSocket, SIGNAL(textMessageReceived(QString)), this, SLOT(onReceiveMessage(QString)));
}

Client::~Client(){
    delete Namber;
}

template<class T1, class T2>
T1 Client::generateSessionNumber(T1 first, T2 end){
    std::mt19937 gen(time(nullptr));
    std::uniform_int_distribution<> uid(first, end);

    return uid(gen);
}

template<class T1, class T2>
bool Client::checkUserInList(const list<T1> &lst, T2 username)
{
    for (auto i = lst.cbegin(); i != lst.cend(); i++)
    {
        if (username == *i)
        {
            return true;
        }
        else
        {
            continue;
        }
    }
    return false;
}

void Client::connectSocket(const QString& host, unsigned int port) // Соединяется с сервером
{
    QMaskGenerator *gen;
    if (clientSocket != nullptr && clientSocket->isValid())
    {
        return; // Необходимо проверить и закрыть (или вернуть) соединение, если оно открыто
    }

    // Передаю значения порта и адреса
    _port = port;
    _host = host;

    QString NumSession = QVariant(generateSessionNumber(10000, 99999)).toString();
    emit newNumberSession(NumSession);

    QUrl qUrl;
    qUrl.setPort((int)_port); // выставление порта
    qUrl.setHost(_host); // выставление адреса
    qUrl.setScheme("ws"); // выставление адресации
    qUrl.setPath("/"+NumSession); // выставление номера трансляции + NumSession

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
