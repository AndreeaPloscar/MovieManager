//
// Created by Andreea Ploscar on 24.05.2021.
//

#include "UserTableModel.h"

UserTableModel::UserTableModel(Service &service): service(service) {
    //this->setHorizontalHeaderLabels(QStringList() << "Title" << "Genre" << "Year" << "Likes" << "Trailer link");

}

int UserTableModel::rowCount(const QModelIndex &parent) const {
    return this->service.get_user_repository()->get_movies().size();
}

int UserTableModel::columnCount(const QModelIndex &parent) const {
    return 6;
}

QVariant UserTableModel::data(const QModelIndex &index, int role) const {
    vector<Movie> data = this->service.get_user_repository()->get_movies();
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
        if(column == 5){
            return QString::fromStdString(data[row].get_trailer());
        }
    }

    return QVariant();
}

QVariant UserTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
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
            case 5:
                return QString("Play");
        }
    }
    return QVariant();
}

Service &UserTableModel::getService() const {
    return service;
}

//QVariant UserTableModel::headerData(int column, Qt::Orientation orientation, int role) const
//{
//    if (role == Qt::DisplayRole)
//    {
//        if (orientation == Qt::Horizontal) {
//            switch (column)
//            {
//                case 0:
//                    return tr("ColumnName");
//                case 1:
//                    return tr("Filename");
//                default:
//                    return QString("");
//            }
//        }
//    }
//    return QVariant();
//}