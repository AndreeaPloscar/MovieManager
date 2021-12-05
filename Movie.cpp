//
// Created by Andreea Ploscar on 05.05.2021.
//


#include <utility>
#include <vector>
#include "Movie.h"
#include "string"
#include "sstream"
using namespace std;
Movie::Movie(std::string title, std::string genre, int year, int likes, std::string trailer){
    this->likes = likes;
    this->title = std::move(title);
    this->genre = std::move(genre);
    this->trailer = std::move(trailer);
    this->year = year;
}

std::string Movie::get_title(){
    return this->title;
}
std::string Movie::get_genre(){
    return this->genre;
}

int Movie::get_year() const{
    return this->year;
}
int Movie::get_number() const{
    return this->likes;
}

std::string Movie::get_trailer(){
    return this->trailer;
}

void Movie::set_title(std::string new_title){
    this->title = new_title;
}

void Movie::set_genre(std::string new_genre){
    this->genre = new_genre;
}
void Movie::set_year(int new_year){
    this->year = new_year;
}

void Movie::set_number(int new_number){
    this->likes = new_number;
}

void Movie::set_trailer(std::string new_trailer){
    this->trailer = new_trailer;
}

std::ostream &operator<<(std::ostream &os, const Movie &movie) {
    os << "Title: " << movie.title << "\n" <<"Genre: " << movie.genre << "\n" << "Year: " << movie.year << "\n" << "Likes: " << movie.likes
       << "\n" << "Trailer: " << movie.trailer << "\n";
    return os;
}

std::istream& operator >> (std::istream &input, Movie *movie)
{
    std::string line;
    getline(input,line);
    std::vector<std::string> tokens;
    std::string delimiter=",";
    size_t pos;
    std::string token;
    while ((pos = line.find(delimiter))!= std::string::npos) {
        token = line.substr(0,pos);
        tokens.push_back(token);
        line.erase(0,pos+delimiter.length());
    }
    tokens.push_back(line);
    if (tokens.size() != 5)
        return input;
    movie->set_title(tokens[0]);
    movie->set_genre(tokens[1]);
    movie->set_year(stoi(tokens[2]));
    movie->set_number(stoi(tokens[3]));
    movie->set_trailer(tokens[4]);
    return input;
}


Movie &Movie::operator=(const Movie &movie) {
    this->title = movie.title;
    this->trailer = movie.trailer;
    this->likes = movie.likes;
    this->year=movie.year;
    return *this;
}
