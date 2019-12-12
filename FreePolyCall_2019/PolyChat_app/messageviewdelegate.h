#ifndef MESSAGEVIEWDELEGATE_H
#define MESSAGEVIEWDELEGATE_H

#include <QStyledItemDelegate>
#include <QWidget>
#include "listmessagemodel.h"
#include "mainwindow.h"
#include <QVector>

class MessageViewDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit MessageViewDelegate(QObject *parent = nullptr);

    // создает виджет редактора значений
    QWidget * createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    // передает значение от модели в редактор
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;

    // передает значение от редактора в модель
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;

    // задает геометрию редактора
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    // отрисовывает ячейку элемента
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const override;
    // отрисовывает объекты элемента
    void paintObject( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const;
    void paintSetIcon( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const;
    void drawButton( QStyleOptionButton &o, const QPoint &p, QPainter * painter ) const;


private:
    std::vector<std::string> Items;
    QImage defaultIcon_;
};

#endif // MESSAGEVIEWDELEGATE_H
