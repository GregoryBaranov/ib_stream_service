#ifndef LISTMESSAGEMODEL_H
#define LISTMESSAGEMODEL_H

#include <QAbstractListModel>
#include "mainwindow.h"
#include <QSize>
#include <QBrush>
#include <QFont>
#include <QStringList>
#include <QDebug>
#include "styleapp.h"
#include <QMessageBox>

class ListMessageModel : public QAbstractListModel
{
    Q_OBJECT

public:

    enum ObjectDataRole
    {
        DescriptionRole = Qt::UserRole + 1,
        DetailRole,
        RoleStreamer,
        RoleStudent,
        VersionRole,
        InstalledRole,
        EnabledRole,
        BuildInRole,
        SourceRole,
        IconRole,
        DateRole,
        GuidRole,
        ProgressRole,
        NeedUpdateRole
    };

    explicit ListMessageModel(QObject *parent = nullptr);

    // количество элементов списка
    int rowCount(const QModelIndex & parent = QModelIndex()) const;

    // возвращает значение элемента
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    // сохраняет новое значение
    bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);

    // возвращает параметры редактируемости
    Qt::ItemFlags flags(const QModelIndex & index) const;

    QString name_, description_, detail_, source_, guid_;

    QList<QString> list;
    QList<QString> listName;
    QList<QString> listDescription;
    QList<QString> listDate;
private:
//    QList<QString> list;



};

#endif // LISTMESSAGEMODEL_H
