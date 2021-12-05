//
// Created by Andreea Ploscar on 05.05.2021.
//
#include "QApplication"
#include <QHBoxLayout>
#include <QMessageBox>
#include <QTableWidget>
#include <QInputDialog>
#include <QLabel>
#include <QDir>
#include <QRadioButton>
#include <QProcess>
#include <QCheckBox>
#include "Gui.h"
#include "iostream"
#include "string"
#include <QtCharts/QChart>
#include "QChartView"
#include "QBarCategoryAxis"
#include "QBarSeries"
#include "QBarSet"
#include "Delegate.h"


using namespace std;

Gui::Gui( Service & service, QWidget * parent): QWidget(parent), service(service){
    this->start();
}

void Gui::start(){
    QVBoxLayout* layout = new QVBoxLayout{ this };
    this->csv = new QRadioButton("CSV", this);
    this->html = new QRadioButton("HTML", this);
    QLabel * file = new QLabel;
    QLabel * name = new QLabel;
    file->setText("Choose file format:");
    name->setText("Input file name:");
    layout->addWidget(name);
    this->file_name_line = new QLineEdit("");
    layout->addWidget(this->file_name_line);
    layout->addWidget(file);
    layout->addWidget(csv);
    layout->addWidget(html);
    QPushButton * ok_file = new QPushButton("Save");
    layout->addWidget(ok_file);
    QObject::connect(ok_file, SIGNAL(clicked()), this, SLOT(change_repo()));
    QLabel * mode = new QLabel;
    mode->setText("Choose starting mode:");
    layout->addWidget(mode);
    this->admin = new QPushButton{"Administrator" };
    layout->addWidget(admin);
    admin->setDisabled(true);
    this->user = new QPushButton{"User" };
    layout->addWidget(user);
    user->setDisabled(true);
    this->exit = new QPushButton{"Exit" };
    layout->addWidget(exit);
    QObject::connect(this->admin, SIGNAL(clicked()), this, SLOT(administrator_mode()));
    QObject::connect(this->user, SIGNAL(clicked()), this, SLOT(user_mode()));
    QObject::connect(this->exit, SIGNAL(clicked()), this, SLOT(exit_app()));
}



void Gui::change_repo(){
    strcpy(file,this->file_name_line->text().toStdString().c_str());
    if(this->csv->isChecked()) {
        strcat(file, ".csv");
        CSVRepository *new_repo = new CSVRepository(file,
                                                    "/Users/andreeaploscar/CLionProjects/a10-915-Ploscar-Andreea-1/");
        this->service.setUserRepository(new_repo);


    }else {
        strcat(file, ".html");
        HTMLRepository *new_repo = new HTMLRepository(file,
                                                      "/Users/andreeaploscar/CLionProjects/a10-915-Ploscar-Andreea-1/");
        this->service.setUserRepository(new_repo);
    }
    admin->setEnabled(true);
    user->setEnabled(true);
}

void Gui::administrator_mode() {
    if(admin_wdg->isActiveWindow())
        admin_wdg->close();
    if(user_wdg->isActiveWindow())
        user_wdg->close();
    this->admin_wdg = new QWidget;
    this->admin_wdg->show();
    close();
    QVBoxLayout* layout = new QVBoxLayout{ this->admin_wdg };
    this->add = new QPushButton{"Add" };
    layout->addWidget(add);
    QObject::connect(this->add, SIGNAL(clicked()), this, SLOT(add_movie()));
    this->update = new QPushButton{"Update" };
    layout->addWidget(update);
    QObject::connect(this->update, SIGNAL(clicked()), this, SLOT(update_movie()));
    this->remove = new QPushButton{"Remove" };
    layout->addWidget(remove);
    QObject::connect(this->remove, SIGNAL(clicked()), this, SLOT(remove_movie()));

    this->admin_tableModel = new AdminTableModel{this->service};
    auto tableView = new QTableView();
    tableView->setModel(admin_tableModel);
    tableView->resizeColumnsToContents();
    layout->addWidget(tableView);

    this->admin_wdg->resize(700,500);
    this->exit_from_admin = new QPushButton{"Exit" };
    layout->addWidget(exit_from_admin);
    QObject::connect(this->exit_from_admin, SIGNAL(clicked()), this, SLOT(exit_app()));
    this->user_from_admin = new QPushButton{"User mode" };
    layout->addWidget(user_from_admin);
    QPushButton * chart = new QPushButton("See data in chart");
    layout->addWidget(chart);
    QObject::connect(chart, SIGNAL(clicked()), this, SLOT(see_chart()));
    QObject::connect(this->user_from_admin, SIGNAL(clicked()), this, SLOT(user_mode()));
    this->undo = new QPushButton{"Undo" };
    this->redo = new QPushButton{"Redo" };
    layout->addWidget(undo);
    layout->addWidget(redo);
    QObject::connect(undo, SIGNAL(clicked()), this, SLOT(undo_admin()));
    QObject::connect(redo, SIGNAL(clicked()), this, SLOT(redo_admin()));
    undo_key = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Z), this);
    redo_key = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Y),this);
    this->undo->setShortcut(Qt::CTRL + Qt::Key_Z);
    this->redo->setShortcut(Qt::CTRL + Qt::Key_Y);

    }

void Gui::undo_admin(){
    try {
        this->service.undo();

        administrator_mode();
    }catch (...){
        QMessageBox messageBox;
        messageBox.critical(0,"Error","Initial state!");
        messageBox.setFixedSize(300,200);
    }
}

void Gui::redo_admin(){
    try {
        this->service.redo();

        administrator_mode();
    }
    catch (...){
        QMessageBox messageBox;
        messageBox.critical(0,"Error","Last state!");
        messageBox.setFixedSize(300,200);
    }
}

void Gui::see_chart(){

    vector<std::string>years = {"2013", "2014", "2015", "2016","2017","2018", "2019",  "2020", "2021"};
    vector<QtCharts::QBarSet*> sets;
    vector<std::string>genres = this->service.get_all_genres();
    for(int i = 0; i < genres.size(); i ++){
        sets.push_back(new QtCharts::QBarSet(genres[i].c_str()));
    }
    for(auto & set: sets) {
        for (auto &year: years) {
            int data = this->service.get_movies_by_year(year, set->label().toStdString());
            *set << data;
        }
    }
    QtCharts::QBarSeries *barseries = new QtCharts::QBarSeries();
    for(auto & set: sets)
        barseries->append(set);
    auto *chart = new QtCharts::QChart();
    chart->addSeries(barseries);
    chart->setTitle("Movies data");
    QStringList categories;
    for (auto & year: years)
        categories << year.c_str();
    QtCharts::QBarCategoryAxis *axis = new QtCharts::QBarCategoryAxis();
    axis->append(categories);
    chart->createDefaultAxes();
    chart->setAxisX(axis, barseries);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
    QtCharts::QChartView *chartView = new QtCharts::QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setFixedSize(700,500);
    chart->setTheme(QtCharts::QChart::ChartThemeDark);
    //chartView->chart()->setTheme(theme);
    chartView->show();

}

void Gui::user_mode() {
    if(user_wdg->isActiveWindow())
        user_wdg->close();
    user_wdg = new QWidget;
    if(admin_wdg->isActiveWindow())
        admin_wdg->close();
    user_wdg->show();
    close();
    QVBoxLayout* layout = new QVBoxLayout{ user_wdg };
    this->remove_user = new QPushButton{"Remove" };
    layout->addWidget(remove_user);
    QObject::connect(this->remove_user, SIGNAL(clicked()), this, SLOT(remove_movie_user()));
    QPushButton * in_app = new QPushButton{"See Watchlist in app" };
    layout->addWidget(in_app);
    QObject::connect(in_app, SIGNAL(clicked()), this, SLOT(see_in_app()));
    QPushButton * by_gender = new QPushButton{"See movies by genre" };
    layout->addWidget(by_gender);
    QObject::connect(by_gender, SIGNAL(clicked()), this, SLOT(see_by_genre()));
    this->tableModel = new UserTableModel{this->service};
    tableModel->setHeaderData(1,Qt::Horizontal, QString("Column1"),Qt::DisplayRole);
    Delegate * delegate = new Delegate(tableModel);

    auto tableView = new QTableView();
    tableView->setModel(tableModel);
    tableView->setItemDelegateForColumn(5, delegate);

    tableView->resizeColumnsToContents();
    tableView->setColumnWidth(5,40);

    layout->addWidget(tableView);
    vector<Movie>movies = this->service.get_user_repository()->get_movies();

    user_wdg->resize(700,500);
    this->user_to_admin = new QPushButton{"Admin mode" };
    layout->addWidget(user_to_admin);
    QObject::connect(this->user_to_admin, SIGNAL(clicked()), this, SLOT(administrator_mode()));
    this->exit_from_user = new QPushButton{"Exit" };
    layout->addWidget(exit_from_user);
    QObject::connect(this->exit_from_user, SIGNAL(clicked()), this, SLOT(exit_app()));
    this->user_undo = new QPushButton{"Undo" };
    this->user_redo = new QPushButton{"Redo" };
    layout->addWidget(user_undo);
    layout->addWidget(user_redo);
    QObject::connect(user_undo, SIGNAL(clicked()), this, SLOT(undo_user()));
    QObject::connect(user_redo, SIGNAL(clicked()), this, SLOT(redo_user()));
}

void Gui::exit_app() {
    std::exit(0);
}

void Gui::add_movie() {

    this->add_wdg = new QWidget;
    add_wdg->setFixedSize(300,250);
    QVBoxLayout* layout = new QVBoxLayout{ add_wdg };
    QLabel * label = new QLabel;
    label->setText("Add a movie");
    layout->addWidget(label);
    this->title_line = new QLineEdit;
    layout->addWidget(title_line);
    this->title_line->setPlaceholderText("Title");
    this->genre_line = new QLineEdit;
    layout->addWidget(genre_line);
    this->genre_line->setPlaceholderText("Genre");
    this->year_line = new QLineEdit;
    layout->addWidget(year_line);
    this->year_line->setPlaceholderText("Year");
    this->likes_line = new QLineEdit;
    layout->addWidget(likes_line);
    this->likes_line->setPlaceholderText("Likes");
    this->trailer_line = new QLineEdit;
    layout->addWidget(trailer_line);
    this->trailer_line->setPlaceholderText("Trailer");
    this->save = new QPushButton{"Save" };
    layout->addWidget(save);
    QObject::connect(this->save, SIGNAL(clicked()), this, SLOT(save_movie()));
    add_wdg->show();
}

void Gui::save_movie(){
    string title = this->title_line->text().toStdString();
    string genre = this->genre_line->text().toStdString();
    string year = this->year_line->text().toStdString();
    string likes = this->likes_line->text().toStdString();
    string trailer = this->trailer_line->text().toStdString();
    try {
        int yearr = stoi(year, nullptr, 10);
        int likess = stoi(likes, nullptr, 10);
        this->service.add_movie_admin(title, genre, yearr, likess, trailer);
        this->add_wdg->close();
        administrator_mode();
    }
    catch (...){
        QMessageBox messageBox;
        messageBox.critical(0,"Error","Movie could not be added!");
        messageBox.setFixedSize(300,200);
        this->admin_wdg->show();
    }

}

void Gui::remove_movie_user(){
    this->remove_wdg = new QWidget;
    remove_wdg->setFixedSize(300,200);
    QVBoxLayout* layout = new QVBoxLayout{ remove_wdg };
    QLabel * title = new QLabel;
    title->setText("Input a title");
    layout->addWidget(title);
    this->input = new QLineEdit;
    layout->addWidget(this->input);

    this->checkbox = new QCheckBox;
    this->checkbox->setText("Rate movie with a like");
    layout->addWidget(checkbox);
    QPushButton * remove_movie_btn = new QPushButton("Remove");
    layout->addWidget(remove_movie_btn);
    QObject::connect(remove_movie_btn, SIGNAL(clicked()), this, SLOT(remove_movie_pressed()));
    remove_wdg->show();
}

void Gui::remove_movie_pressed(){
    this->title_to_remove = input->text();
    try {
        bool rate = false;
        if(this->checkbox->isChecked())
            rate = true;
        Movie movie = this->service.remove_movie_user(this->title_to_remove.toStdString(),rate);
        this->remove_wdg->close();
        user_mode();
    }
    catch (...){
        QMessageBox messageBox;
        messageBox.critical(0,"Error","Title does not exist!");
        messageBox.setFixedSize(300,200);
        this->remove_wdg->close();
        user_mode();
    }
}

void Gui::remove_movie() {
    bool ok;
    QString text = QInputDialog::getText(this, tr("Input a title"),
                                         tr("Title:"), QLineEdit::Normal,
                                         "", &ok);
    if (ok && !text.isEmpty()) {
        try {
            this->service.remove_movie_admin(text.toStdString());
            administrator_mode();
        }
        catch (...){
            QMessageBox messageBox;
            messageBox.critical(0,"Error","Title does not exist!");
            messageBox.setFixedSize(300,200);
            administrator_mode();
        }
    }

}

void Gui::undo_user(){
    try {
        this->service.undo_user();
        cout << "Undo";
        user_mode();
    }catch (...){
        QMessageBox messageBox;
        messageBox.critical(0,"Error","Initial state!");
        messageBox.setFixedSize(300,200);
    }
}
void Gui::redo_user(){
    try {
        this->service.redo_user();
        cout << "Redo";
        user_mode();
    }catch (...){
        QMessageBox messageBox;
        messageBox.critical(0,"Error","Most recent state!");
        messageBox.setFixedSize(300,200);
    }
}

void Gui::update_movie() {

    this->update_wdg = new QWidget;
    this->update_wdg->setFixedSize(300,250);
    QVBoxLayout* layout = new QVBoxLayout{ this->update_wdg };
    QLabel * label = new QLabel;
    label->setText("Update a movie");
    layout->addWidget(label);
    this->title_line_upd = new QLineEdit;
    layout->addWidget(title_line_upd);
    this->title_line_upd->setPlaceholderText("Title");
    this->genre_line_upd = new QLineEdit;
    layout->addWidget(genre_line_upd);
    this->genre_line_upd->setPlaceholderText("Genre");
    this->year_line_upd = new QLineEdit;
    layout->addWidget(year_line_upd);
    this->year_line_upd->setPlaceholderText("Year");
    this->likes_line_upd = new QLineEdit;
    layout->addWidget(likes_line_upd);
    this->likes_line_upd->setPlaceholderText("Likes");
    this->trailer_line_upd = new QLineEdit;
    layout->addWidget(trailer_line_upd);
    this->trailer_line_upd->setPlaceholderText("Trailer");
    this->update_btn = new QPushButton{"Update" };
    layout->addWidget(update_btn);
    QObject::connect(this->update_btn, SIGNAL(clicked()), this, SLOT(update_movie_slot()));
    this->update_wdg->show();
}

void Gui::update_movie_slot() {

    string title = this->title_line_upd->text().toStdString();
    //cout << title;
    string genre = this->genre_line_upd->text().toStdString();
    string year = this->year_line_upd->text().toStdString();
    //cout << year;
    string likes = this->likes_line_upd->text().toStdString();
    //cout << likes;
    string trailer = this->trailer_line_upd->text().toStdString();
    //cout << trailer;
    try {
        int yearr = stoi(year, nullptr, 10);
        int likess = stoi(likes, nullptr, 10);
        this->service.update_movie(title, genre, yearr, likess, trailer);
        this->update_wdg->close();
        administrator_mode();
    }
    catch (...){
        QMessageBox messageBox;
        messageBox.critical(0,"Error","Movie could not be updated!");
        messageBox.setFixedSize(300,200);
        this->admin_wdg->show();
    }
}

void Gui::see_in_app() {
    system(this->service.get_command().c_str());
}

void Gui::see_by_genre() {
    bool ok;
    string genre_s;
    QString text = QInputDialog::getText(this, tr("Input genre"),
                                         tr("Genre:"), QLineEdit::Normal,
                                         "", &ok);
    if (ok && !text.isEmpty())
        genre_s = text.toStdString();
    this->genre = genre_s;
    this->count = 0;
    this->genre_wdg = new QWidget;
    this->genre_wdg->setFixedSize(300,250);
    QVBoxLayout* layout = new QVBoxLayout{ this->genre_wdg };
    title_play = new QLabel;
    layout->addWidget(title_play);
    genre_play= new QLabel;
    layout->addWidget(genre_play);
    year_play = new QLabel;
    layout->addWidget(year_play);
    likes_play = new QLabel;
    layout->addWidget(likes_play);
    trailer_play = new QLabel;
    layout->addWidget(trailer_play);
    QPushButton * open = new QPushButton{"Open link in browser" };
    layout->addWidget(open);
    QObject::connect(open, SIGNAL(clicked()), this, SLOT(open_link()));
    QPushButton * add = new QPushButton{"Add" };
    layout->addWidget(add);
    QObject::connect(add, SIGNAL(clicked()), this, SLOT(add_movie_user()));
    QPushButton * next = new QPushButton{"Skip" };
    layout->addWidget(next);
    QObject::connect(next, SIGNAL(clicked()), this, SLOT(play()));
    QPushButton * exit_from_play = new QPushButton{"Exit" };
    layout->addWidget(exit_from_play);
    QObject::connect(exit_from_play, SIGNAL(clicked()), this, SLOT(exit_from_play_slot()));
    this->genre_wdg->show();
    filtered_movies = this->service.movies_by_genre(genre);
    play();
}

void Gui::exit_from_play_slot(){
    this->genre_wdg->close();
    this->user_wdg->close();
    user_mode();
}

void Gui::add_movie_user(){
    try {
        this->service.add_movie_user(current_movie.get_title(),current_movie.get_genre(),current_movie.get_year(),current_movie.get_number(),current_movie.get_trailer());
        play();
    }
    catch(...) {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","Movie could not be added!");
        messageBox.setFixedSize(300,200);
        play();
    }
}

void Gui::open_link(){
    QProcess process;
    process.start("open", QStringList()
            << current_movie.get_trailer().c_str());
    process.waitForFinished(-1);
}

void Gui::play(){
    current_movie.set_title(filtered_movies[count].get_title());
    current_movie.set_genre(filtered_movies[count].get_genre());
    current_movie.set_year(filtered_movies[count].get_year());
    current_movie.set_trailer(filtered_movies[count].get_trailer());
    current_movie.set_number(filtered_movies[count].get_number());
    title_play->setText(current_movie.get_title().c_str());
    genre_play->setText(current_movie.get_genre().c_str());
    year_play->setText(to_string(current_movie.get_year()).c_str());
    likes_play->setText(to_string(current_movie.get_number()).c_str());
    trailer_play->setText(current_movie.get_trailer().c_str());
    count ++;
    count = count % filtered_movies.size();
}

