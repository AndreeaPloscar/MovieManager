//
// Created by Andreea Ploscar on 24.05.2021.
//

#ifndef A10_915_PLOSCAR_ANDREEA_1_ADMINTABLEMODEL_H
#define A10_915_PLOSCAR_ANDREEA_1_ADMINTABLEMODEL_H

#include "Service.h"
#include "QAbstractTableModel"


class AdminTableModel : public QAbstractTableModel{
    Q_OBJECT;
private:
    Service & service;
public:
    AdminTableModel(Service& service);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

};


#endif //A10_915_PLOSCAR_ANDREEA_1_ADMINTABLEMODEL_H
