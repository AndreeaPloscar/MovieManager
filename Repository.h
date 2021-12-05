//
// Created by Andreea Ploscar on 05.05.2021.
//

#ifndef A89_915_PLOSCAR_ANDREEA_REPOSITORY_H
#define A89_915_PLOSCAR_ANDREEA_REPOSITORY_H



//#include <sqlite3.h>
#include "Movie.h"
#include "vector"
#include "sstream"
#include "fstream"


class Repository {
protected:
    std::vector<Movie> movies;
public:
    Repository();
    virtual std::string get_command();
    virtual void add(Movie& movie);
    virtual Movie remove(std::string title);
    virtual Movie update(Movie& movie);
    virtual bool find(std::string title);
    std::vector<Movie> get_movies() const;
    virtual void rate_movie(std::string title);
    virtual void unrate_movie(std::string title);
};

class FileRepository: public Repository{
private:
    string path;
    char * file_name;
public:
    explicit FileRepository( char * fileName, string path);
    void save_to_file();
    void add(Movie& movie);
    Movie remove(std::string title);
    Movie update(Movie& movie);
    bool find(std::string title);
    void load_from_file();
    void rate_movie(std::string title);
    void unrate_movie(std::string title);
};

class CSVRepository: public Repository{
private:
    string path;
    char * file_name;
public:
    explicit CSVRepository( char * fileName, string path);
    void save_to_file();
    void add(Movie& movie);
    Movie remove(std::string title);
    Movie update(Movie& movie);
    std::string get_command();
    bool find(std::string title);
};


class HTMLRepository: public Repository{
private:
    string path;
    char * file_name;
public:
    explicit HTMLRepository( char * fileName, string path);
    void save_to_file();
    void add(Movie& movie);
    std::string get_command();
    Movie remove(std::string title);
    Movie update(Movie& movie);
    bool find(std::string title);
};

//
//class DBRepository: public Repository{
//private:
//    char *db_name;
//public:
//    explicit DBRepository(char *db);
//    void add(Movie& movie);
//    std::string get_command();
//    Movie remove(std::string title);
//    void update(Movie& movie);
//    bool find(std::string title);
//    void load_from_db();
//};


#endif //A89_915_PLOSCAR_ANDREEA_REPOSITORY_H
