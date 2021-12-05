//
// Created by Andreea Ploscar on 24.05.2021.
//

#ifndef A10_915_PLOSCAR_ANDREEA_1_DELEGATE_H
#define A10_915_PLOSCAR_ANDREEA_1_DELEGATE_H

#include "QItemDelegate"
#include "QStyledItemDelegate"

class Delegate:  public QStyledItemDelegate{
    Q_OBJECT

    public:
    Delegate(QObject *parent = nullptr);

//    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
//                          const QModelIndex &index) const override;
//
//    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
//    void setModelData(QWidget *editor, QAbstractItemModel *model,
//                      const QModelIndex &index) const override;
//
//    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
//                              const QModelIndex &index) const override;
void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);
};


#endif //A10_915_PLOSCAR_ANDREEA_1_DELEGATE_H
