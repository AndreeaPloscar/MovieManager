//
// Created by Andreea Ploscar on 05.05.2021.
//

#ifndef A89_915_PLOSCAR_ANDREEA_MOVIE_H
#define A89_915_PLOSCAR_ANDREEA_MOVIE_H

#include <ostream>
using namespace std;
class Movie {

private:
    std::string title;
    std::string genre;
    int year;
    int likes;
    std::string trailer;

public:

    explicit Movie(std::string title = "", std::string genre = "", int year = 0, int likes = 0, std::string trailer = "" );
    //explicit Movie(Movie & movie);
    std::string get_title();
    std::string get_genre();
    int get_year() const;
    int get_number() const;
    std::string get_trailer();

    void set_title(std::string title);
    void set_genre(std::string genre);
    void set_year(int year);
    void set_number(int number);
    void set_trailer(std::string trailer);
    Movie& operator=(const Movie &movie);
    friend std::ostream &operator<<(std::ostream &os, const Movie &movie);
    friend std::istream &operator>>(std::istream &is, Movie* movie);

};




#endif //A89_915_PLOSCAR_ANDREEA_MOVIE_H
