//
// Created by Andreea Ploscar on 24.05.2021.
//

#include "Delegate.h"
#include "QPushButton"
#include "QApplication"
#include "QSpinBox"
#include "QTableView"
#include "iostream"
#include "QProcess"
#include "UserTableModel.h"
#include "Service.h"

Delegate::Delegate(QObject *parent)
        : QStyledItemDelegate(parent){}

void Delegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionButton * button = new QStyleOptionButton();
    QRect r = option.rect;//getting the rect of the cell
    int x,y,w,h;
    x = r.left() + r.width() - 45;//the X coordinate
    y = r.top();//the Y coordinate
    w = 50;//button width
    h = 30;//button height
    button->rect = QRect(x,y,w,h);
    button->icon = QPixmap("/Users/andreeaploscar/CLionProjects/a10-915-Ploscar-Andreea-1/play.jpg");
    button->iconSize = QSize(30,30);
    button->state = QStyle::State_Enabled;

    QApplication::style()->drawControl( QStyle::CE_PushButtonLabel,button,painter);

}

bool Delegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
        QProcess process;
        process.start("open", QStringList()
                <<  index.model()->data(index, Qt::DisplayRole).toString().toStdString().c_str());
        process.waitForFinished(-1);

    return true;
}