#include "listmessagemodel.h"

ListMessageModel::ListMessageModel(QObject *parent) :
    QAbstractListModel(parent)
{

}

int ListMessageModel::rowCount(const QModelIndex &parent) const
{
    return  list.count();
}

QVariant ListMessageModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return  QVariant();

    switch (role) {
    case Qt::DisplayRole:
    case DetailRole:
        return listName.at(index.row());
    case DescriptionRole:
        return listDescription.at(index.row());
    case Qt::TextAlignmentRole:
        return Qt::AlignTop;
    case Qt::DecorationRole:
        if (listName.at(index.row()) != "Streamer")
        {
            return RoleStudent;
        }
        else
        {
            return RoleStreamer;

        }
    default:
        return  QVariant();
    }

}



//if (!index.isValid())
//    return  QVariant();

//switch (role) {
//case Qt::DisplayRole:
//    return QString(" %2 \n %3")
//            .arg(listName.at(index.row()))
//            .arg(listDescription.at(index.row()));
//case Qt::TextAlignmentRole:
//    return Qt::AlignTop;
//case DetailRole:
//    return listName.at(index.row());
//case DescriptionRole:
//    return listDescription.at(index.row());
//case Qt::DecorationRole:
//    if (listName.at(index.row()) != "Streamer")
//    {
//        return QImage(":/image/std.png");
//    }
//    else
//    {
//        return QImage(":/image/cron.png");

//    }
//case Qt::BackgroundRole:
//    if (listName.at(index.row()) != "Streamer")
//    {
//        return QBrush(QColor(51,50,51));
//    }
//    else
//    {
//        return QBrush(QColor(51,50,51));

//    }
//default:
//    return  QVariant();
//}

bool ListMessageModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role == Qt::EditRole)
        list.replace(index.row(), value.toString());
        return true;
}

Qt::ItemFlags ListMessageModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return  Qt::NoItemFlags;

    return  Qt::ItemIsEnabled | Qt::ItemIsSelectable ;
}
