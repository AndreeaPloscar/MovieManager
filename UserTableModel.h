//
// Created by Andreea Ploscar on 24.05.2021.
//

#ifndef A10_915_PLOSCAR_ANDREEA_TABLEMODEL_H
#define A10_915_PLOSCAR_ANDREEA_TABLEMODEL_H

#include "QWidget"
#include "QAbstractTableModel"
#include "Service.h"

class UserTableModel : public QAbstractTableModel{
Q_OBJECT;
private:
    Service & service;
public:
    Service &getService() const;

public:
    UserTableModel(Service& service);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

};


#endif //A10_915_PLOSCAR_ANDREEA_TABLEMODEL_H
