#ifndef DOWNLOADER_H
#define DOWNLOADER_H
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QFile>
#include <QUrl>
#include <QDebug>
#include <string>
#include <vector>
using namespace std;

class Downloader : public QObject
{
    Q_OBJECT
public:
    explicit Downloader(QObject *parent = 0);

signals:
    void onReady(QString);
public slots:
    void resirvedText(QString str);
    void chatData();
    void getData();
    void onResult(QNetworkReply *reply);

private:
    QNetworkAccessManager *manager;
    QString message;
    QString temp = "";


};





#endif // DOWNLOADER_H
