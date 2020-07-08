#include "emojis.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>
#include <QVariant>
#include <QDebug>

Emojis::Emojis(){}

// синглтон
Emojis* Emojis::instance()
{
    static Emojis provider;
    return &provider;
}

// возвращает список emoji
QStringList Emojis::getEmoji(TYPE_EMOJI TYPE = ALL)
{
    QFile file(":/Emoji/emoji.json");
    QString allEmoji;

    if ((file.exists())&&(file.open(QIODevice::ReadOnly)))
    {
       allEmoji = file.readAll();
    }

    QJsonParseError jsonError;
    QJsonDocument jsonResponse = QJsonDocument::fromJson(allEmoji.toUtf8());

    if (jsonError.error != QJsonParseError::NoError)
    {
        qDebug() << jsonError.errorString();
    }

    QList<QVariant> list = jsonResponse.toVariant().toList();
    QMap<QString, QVariant> map = list[0].toMap();

    QStringList listEmoji;
    switch(TYPE)
    {
        case ALL:
            listEmoji = map["ALL"].toString().split(";");
            break;
        case SMILEY:
            listEmoji = map["SMILEY"].toString().split(";");
            break;
        case GESTURES:
            listEmoji = map["GESTURES"].toString().split(";");
            break;
        case PEOPLE:
            listEmoji = map["PEOPLE"].toString().split(";");
            break;
        case CLOTHING:
            listEmoji = map["CLOTHING"].toString().split(";");
            break;
    }

    listEmoji.removeLast();

    return listEmoji;
}
