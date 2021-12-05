//
// Created by Andreea Ploscar on 05.05.2021.
//


#include <iostream>
#include "Repository.h"
#include "string"
#include "Exception.h"

using namespace std;
void Repository::add(Movie& movie) {
    /***
     * Adds a new movie into the array of movies
     */
    if(this->find(movie.get_title()))
        throw RepositoryException("Movie already exists!");
    this->movies.push_back(movie);
}

Movie Repository::remove(std::string title) {
    /***
     * Removes a movie from the array of movies, given by its title
     */
    if(not this->find(title))
        throw RepositoryException( "Movie does not exist!");
    int i = 0;
    bool found = false;
    while (i < this->movies.size() && not found){
        if(this->movies[i].get_title() != title ){
            i++;
        }
        else
        {found = true;
        }
    }
    Movie movie = Movie(this->movies[i].get_title(),
                        this->movies[i].get_genre(),
                        this->movies[i].get_year(),
                        this->movies[i].get_number(),
                        this->movies[i].get_trailer());
    this->movies.erase(this->movies.begin() + i);
    return movie;
}

Movie Repository::update(Movie& movie) {
    if(not this->find(movie.get_title()))
        throw RepositoryException( "Movie does not exist!");
    bool found = false;
    int i=0;
    while (i < this->movies.size() && not found){
        if(this->movies[i].get_title() != movie.get_title()){
            i++;
        }
        else
        {found = true;
        }
    }
    Movie old_movie = this->movies[i];
    this->movies[i].set_title(movie.get_title());
    this->movies[i].set_genre(movie.get_genre());
    this->movies[i].set_year(movie.get_year());
    this->movies[i].set_number(movie.get_number());
    this->movies[i].set_trailer(movie.get_trailer());
    return old_movie;
}

Repository::Repository() {
    this->movies = std::vector<Movie>();
}

std::vector<Movie> Repository::get_movies() const {
    return this->movies;
}

bool Repository::find(std::string title) {
    for(auto & movie : this->movies)
        if(movie.get_title() == title )
            return true;

    return false;

}

std::string Repository::get_command() {
    return "";
}

void Repository::rate_movie(std::string title) {
    bool found = false;
    int i=0;
    while (i < this->movies.size() && not found){
        if(this->movies[i].get_title() != title){
            i++;
        }
        else
        {found = true;
        }
    }
    this->movies[i].set_number(this->movies[i].get_number() + 1);
}

void Repository::unrate_movie(std::string title) {
    bool found = false;
    int i=0;
    while (i < this->movies.size() && not found){
        if(this->movies[i].get_title() != title){
            i++;
        }
        else
        {found = true;
        }
    }
    this->movies[i].set_number(this->movies[i].get_number() - 1);
}

FileRepository::FileRepository(char * fileName, string path) : Repository(), file_name(fileName), path(path){
    this->load_from_file();}

void FileRepository::save_to_file() {
    char file_name[100];
    strcpy(file_name, path.c_str());
    std::strcat(file_name, this->file_name);
    std::ofstream out_file;
    out_file.open (file_name);
    std::string line;
    for (auto &movie: this->get_movies()){
        out_file << movie.get_title() << "," << movie.get_genre() << "," << movie.get_year() << "," << movie.get_number() << "," << movie.get_trailer() << "\n";
    }
    out_file.close();
}

void FileRepository::add(Movie &movie) {
    Repository::add(movie);
    this->save_to_file();
}

Movie FileRepository::remove(std::string title) {
    Movie movie = Repository::remove(title);
    this->save_to_file();
    return movie;
}

Movie FileRepository::update(Movie &movie) {
    Movie old_movie = Repository::update(movie);
    this->save_to_file();
    return old_movie;
}

bool FileRepository::find(std::string title) {
    return Repository::find(title);
}

void FileRepository::load_from_file() {
    std::ifstream infile;
    char file_name_aux[100];
    strcpy(file_name_aux, path.c_str());
    std::strcat(file_name_aux, this->file_name);
    infile.open(file_name_aux);
    std::string line;
    Movie movie("","",0,0,"");
    while(infile >> &movie){
        this->add(movie);
    }
}

void FileRepository::rate_movie(std::string title) {
    Repository::rate_movie(title);
    this->save_to_file();
}
void FileRepository::unrate_movie(std::string title) {
    Repository::unrate_movie(title);
    this->save_to_file();
}


CSVRepository::CSVRepository(char * fileName, string path) : Repository(), file_name(fileName), path(std::move(path)){

}

void CSVRepository::save_to_file() {
    char file_name_aux[100];
    strcpy(file_name_aux, path.c_str());
    std::strcat(file_name_aux, this->file_name);
    std::ofstream out_file;
    out_file.open (file_name_aux);
    std::string line;
    for (auto &movie: this->get_movies()){
        out_file << movie.get_title() << "," << movie.get_genre() << "," << movie.get_year() << "," << movie.get_number() << "," << movie.get_trailer() << "\n";
    }
    out_file.close();
}
std::string CSVRepository::get_command() {

    std::string command ="open -a TextEdit " +  path;

    command  += this->file_name;
    return command;
}

void CSVRepository::add(Movie &movie) {
    Repository::add(movie);
    this->save_to_file();
}

Movie CSVRepository::remove(std::string title) {
    Movie movie = Repository::remove(title);
    this->save_to_file();
    return movie;
}

Movie CSVRepository::update(Movie &movie) {
    Repository::update(movie);
    this->save_to_file();
    return Movie();
}

bool CSVRepository::find(std::string title) {
    return Repository::find(title);

}


HTMLRepository::HTMLRepository(char * fileName, string path) : Repository(), file_name(fileName), path(path){}

void HTMLRepository::save_to_file() {
    char file_name[100];
    strcpy(file_name, path.c_str());
    std::strcat(file_name, this->file_name);
    std::ofstream out_file;
    out_file.open (file_name);
    out_file << "<!DOCTYPE html>    <!-- write this exactly as it is here -->\n"
                "<html> <!-- write this exactly as it is here -->\n"
                "<head> <!--  write this exactly as it is here -->\n"
                "    <title>Watchlist</title> <!-- replace “Playlist” with the title for your HTML -->\n"
                "</head> <!-- write this exactly as it is here (close head tag) -->\n"
                "<body> <!-- write this exactly as it is here -->\n"
                "<table border=\"1\"> <!-- write this exactly as it is here -->\n"
                "    <tr> <!-- tr = table row; 1 row for each entity -->\n"
                "        <td>Title</td> <!-- td = table data; 1 td for each attribute of the entity -->\n"
                "        <td>Genre</td>\n"
                "        <td>Year</td>\n"
                "        <td>Likes</td>\n"
                "        <td>Trailer link</td>\n"
                "    </tr>\n";
    for (auto &movie:  this->get_movies()){
        out_file<< "    <tr>\n"<<
                "        <td>"<< movie.get_title()<<"</td>\n"<<
                "        <td>"<< movie.get_genre() <<"</td>\n"<<
                "        <td>"<< movie.get_year() <<"</td>\n"<<
                "        <td>"<<movie.get_number()<<"</td>\n"<<
                "        <td><a href=\""<< movie.get_trailer()<<"\">Link</a></td>\n"<<
                "    </tr>\n";
    }

    out_file<<"</table>\n"
              "</body>\n"
              "</html>";
    out_file.close();
}

std::string HTMLRepository::get_command() {
    std::string command;
    command = "open " + path;
    command += this->file_name;
    return command;
}

void HTMLRepository::add(Movie &movie) {
    Repository::add(movie);
    this->save_to_file();
}

Movie HTMLRepository::remove(std::string title) {
    Movie movie = Repository::remove(title);
    this->save_to_file();
    return movie;
}

Movie HTMLRepository::update(Movie &movie) {
    Repository::update(movie);
    this->save_to_file();
    return Movie();
}

bool HTMLRepository::find(std::string title) {
    return Repository::find(title);

}

//DBRepository::DBRepository(char *db): Repository(), db_name(db) {
//    this->load_from_db();
//}
//
//void DBRepository::add(Movie &movie) {
//    Repository::add(movie);
//    sqlite3 *db;
//    int exit = sqlite3_open(this->db_name,&db);
//    if (exit) {
//
//    } else {
//        string movie_s = "'" + movie.get_title() + "', '" + movie.get_genre() + "', '" + to_string(movie.get_year()) + "', '" +
//                         to_string(movie.get_number()) + "', '" + movie.get_trailer() + "'" + ");";
//        string sql1 = "INSERT INTO movies (title, genre, year, likes, link) VALUES(" + movie_s;
//        int rc1 = sqlite3_exec(db, sql1.c_str(), NULL, NULL, NULL);
//        if (rc1 != SQLITE_OK)
//            throw RepositoryException("Database error");
//    }
//    sqlite3_close(db);
//}
//
//std::string DBRepository::get_command() {
//    return Repository::get_command();
//}
//
//Movie DBRepository::remove(std::string title) {
//    Movie movie =  Repository::remove(title);
//
//    sqlite3 *db;
//    int exit = sqlite3_open(this->db_name,&db);
//    if (exit) {} else {
//        string sql = "DELETE FROM MOVIES WHERE TITLE = '";
//        sql += movie.get_title();
//        sql += "';";
//        int exit_code = sqlite3_exec(db, sql.c_str(), NULL, NULL, NULL);
//        if (exit_code != SQLITE_OK)
//            throw RepositoryException("Database error");
//    }
//    sqlite3_close(db);
//    return movie;
//}
//
//void DBRepository::update(Movie &movie) {
//    Repository::update(movie);
//    sqlite3 *db;
//    int exit = sqlite3_open(this->db_name,&db);
//    if (exit) {
//    } else {
//        string sql = "UPDATE MOVIES SET ";
//        string title = "TITLE='" + movie.get_title() + "', ";
//        string genre = "GENRE='" + movie.get_genre() + "', ";
//        string year = "YEAR='" + to_string(movie.get_year()) + "', ";
//        string likes = "LIKES='" + to_string(movie.get_number()) + "', ";
//        string trailer = "LINK='" + movie.get_trailer() + "'";
//        string sql2 = " WHERE TITLE = '";
//        string command = sql + title + genre + year + likes + trailer + sql2 + movie.get_title() + "';";
//        int exit_code = sqlite3_exec(db, command.c_str(), NULL, NULL, NULL);
//        if (exit_code != SQLITE_OK)
//            throw RepositoryException("Database error");
//    }
//    sqlite3_close(db);
//}
//
//bool DBRepository::find(std::string title) {
//    return Repository::find(title);
//}
//
//void DBRepository::load_from_db() {
//    sqlite3 *db;
//    int exit = sqlite3_open(this->db_name,&db);
//    if (exit) {} else {
//        sqlite3_stmt* stmt;
//        int exit_code = sqlite3_prepare_v2(db, "select * from movies", -1, &stmt,NULL);
//        if (exit_code != SQLITE_OK){
//            throw RepositoryException("Database might not exist!");
//        }
//        while (sqlite3_step(stmt) == SQLITE_ROW) {
//            string title = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));
//            Movie movie(title,
//                        std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1))),
//                        sqlite3_column_int(stmt, 2),
//                        sqlite3_column_int(stmt, 3) ,
//                        std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4))));
//            Repository::add(movie);
//        }
//        sqlite3_finalize(stmt);
//    }
//    sqlite3_close(db);
//}
