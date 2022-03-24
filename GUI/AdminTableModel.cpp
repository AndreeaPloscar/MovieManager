//
// Created by Andreea Ploscar on 24.05.2021.
//

#include "AdminTableModel.h"

AdminTableModel::AdminTableModel(Service &service):service(service) {

}

int AdminTableModel::rowCount(const QModelIndex &parent) const {
    return this->service.get_repository().get_movies().size();
}

int AdminTableModel::columnCount(const QModelIndex &parent) const {
    return 5;
}

QVariant AdminTableModel::data(const QModelIndex &index, int role) const {
    vector<Movie> data = this->service.get_repository().get_movies();
    int row = index.row(), column = index.column();
    if (role == Qt::DisplayRole){
        if (column == 0) {
            return QString::fromStdString(data[row].get_title());
        }
        if (column == 1){
            return QString::fromStdString(data[row].get_genre());
        }    if (column == 2){
            return QString::number(data[row].get_year());    }
        if (column == 3){
            return QString::number(data[row].get_number());
        }    if (column == 4){
            return QString::fromStdString(data[row].get_trailer());
        }
    }

    return QVariant();
}

QVariant AdminTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
            case 0:
                return QString("Title");
            case 1:
                return QString("Genre");
            case 2:
                return QString("Year");
            case 3:
                return QString("Likes");
            case 4:
                return QString("Link");
        }
    }
    return QVariant();
}
