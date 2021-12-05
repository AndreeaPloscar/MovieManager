//
// Created by Andreea Ploscar on 05.05.2021.
//

#ifndef A89_915_PLOSCAR_ANDREEA_GUI_H
#define A89_915_PLOSCAR_ANDREEA_GUI_H
#include "QMainWindow"
#include "Service.h"
#include <QPushButton>
#include "QTableWidget"
#include "QLabel"
#include "QRadioButton"
#include "QCheckBox"
#include "UserTableModel.h"
#include "AdminTableModel.h"
#include "QShortcut"
#include "QAction"

class Gui: public QWidget{
    Q_OBJECT
public:
    Gui( Service &service, QWidget * parent = 0);
    void start();

private:
    QWidget * remove_wdg;
    QLineEdit * input;
    QWidget * user_wdg = new QWidget;
    QLineEdit * file_name_line;
    QRadioButton *csv;
    QRadioButton *html;
    Service & service;
    QWidget * add_wdg;
    QWidget * update_wdg;
    QWidget * admin_wdg = new QWidget;
    QPushButton * admin;
    QPushButton * user;
    QPushButton * exit;
    QPushButton * add;
    QPushButton * update;
    QPushButton * remove;
    UserTableModel * tableModel;
    AdminTableModel * admin_tableModel;
    QPushButton * exit_from_admin;
    QPushButton * user_from_admin;
    QLineEdit * title_line;
    QLineEdit * genre_line;
    QLineEdit * year_line;
    QLineEdit * likes_line;
    QLineEdit * trailer_line;
    QPushButton * save;
    QLineEdit * title_line_upd;
    QLineEdit * genre_line_upd;
    QLineEdit * year_line_upd;
    QLineEdit * likes_line_upd;
    QLineEdit * trailer_line_upd;
    QPushButton * update_btn;
    QPushButton * user_to_admin;
    QPushButton * exit_from_user;
    QPushButton * remove_user;
    QPushButton * undo;
    QPushButton * redo;
    QPushButton * user_undo;
    QPushButton * user_redo;
    int count = 0;
    string genre;
    vector<Movie> filtered_movies;
    char file[25];
    QLabel *title_play;
    QLabel *genre_play;
    QLabel *year_play;
    QLabel *likes_play;
    QLabel *trailer_play;
    Movie current_movie;
    QWidget * genre_wdg;
    QCheckBox * checkbox;
    QString title_to_remove;
    QShortcut * undo_key;
    QShortcut * redo_key;

private slots:
    void see_chart();
    void remove_movie_pressed();
    void exit_from_play_slot();
    void add_movie_user();
    void open_link();
    void change_repo();
    void administrator_mode();
    void user_mode();
    void exit_app();
    void save_movie();
    void add_movie();
    void remove_movie();
    void update_movie();
    void update_movie_slot();
    void remove_movie_user();
    void see_in_app();
    void see_by_genre();
    void play();
    void undo_admin();
    void redo_admin();
    void undo_user();
    void redo_user();
};


#endif //A89_915_PLOSCAR_ANDREEA_GUI_H
