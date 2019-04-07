#include "downloader.h"
#include <windows.h>
#include <QUrl>
#include <string>
using namespace  std;
Downloader::Downloader(QObject *parent) : QObject(parent)
{    
    manager = new QNetworkAccessManager();    
     connect(manager, &QNetworkAccessManager::finished, this, &Downloader::onResult);
}


void Downloader::getData()
{
    QString qurl = message;
    QUrl urlN;
    QString site = "http://pyserverchat.std-864.ist.mospolytech.ru/sendMessage?text=";
    QString site1 = site + message;
   urlN.setQuery(site1);
    QNetworkRequest request;
     request.setUrl(site1);
     manager->get(request);
}

void Downloader::resirvedText(QString str)
{
    message = str;
}


void Downloader::chatData()
{
    QUrl url("http://pyserverchat.std-864.ist.mospolytech.ru/ismessage");
    QNetworkRequest request;
    request.setUrl(url);
    manager->get(request);

}

void Downloader::onResult(QNetworkReply *reply)
{

   if(reply->error())
    {
        qDebug() << "ERROR";
        qDebug() << reply->errorString();
    }
    else
    {
        QString buf = reply->readAll();

          if ((buf != "") && (buf != temp))
          {


               temp = buf;

                 emit onReady(buf);
          }

    }
}




