//
// Created by Andreea Ploscar on 05.05.2021.
//

#include "Service.h"
#include "iostream"
#include "Service.h"
#include "Exception.h"
#include <utility>
#include "exception"
#include "sstream"
#include "fstream"
#include "string"

using namespace std;
int Service::get_movies_by_year(std::string year, std::string genre){
    std::vector<Movie> movies=this->repository.get_movies();
    std::vector<Movie> result;
    for(auto &movie: movies)
        if(movie.get_genre() == genre and movie.get_year() == stoi(year, nullptr, 10))
            result.push_back(movie);
    return result.size();
}

vector<std::string> Service::get_all_genres(){
    vector<std::string> genres;
    for(auto &movie: this->repository.get_movies()){
        genres.push_back(movie.get_genre());
    }
    sort( genres.begin(), genres.end() );
    genres.erase( unique(genres.begin(), genres.end() ), genres.end() );
    return genres;
}

void Service::add_movie_admin(std::string title, std::string genre, int year, int likes, std::string trailer) {
    /***
     * Creates a movie with given parameters and adds it into the list of movies, raises exception if movie already exists
     */
    this->validator.validate_movie(title, genre, year, likes, trailer);
    Movie movie(title, genre, year, likes,trailer);
    UndoAdd * operation = new UndoAdd(repository, movie);
    undo_service.record(operation);
    this->repository.add(movie);
}

std::string Service::get_command(){
    return this->user_repository->get_command();
}

void Service::add_movie_user(std::string title, std::string genre, int year, int likes, std::string trailer) {
    /***
     * Creates a movie with given parameters and adds it into the watchlist, raises exception if movie already exists
     */
    Movie movie(title, genre, year, likes, trailer);
    this->user_repository->add(movie);
    UndoAddUser* operation = new UndoAddUser(user_repository,movie,repository);
    undo_service_user.record(operation);

}

void Service::remove_movie_admin(std::string title) {
    /***
     * Removes the movie having given title from the list of movies
     */

    Movie old_movie = this->repository.remove(title);
    auto * operation = new UndoDelete(repository, old_movie);
    undo_service.record(operation);

}

Movie Service::remove_movie_user(std::string title, bool rate) {
    /***
     * Removes the movie having given title from the watchlist
     */
    Movie movie = this->user_repository->remove(title);
    if(rate)
        this->repository.rate_movie(title);
    UndoDeleteUser* operation = new UndoDeleteUser(user_repository,movie,repository, rate);
    undo_service_user.record(operation);
    return movie;
}

void Service::update_movie( std::string title, std::string genre, int year, int likes,std::string trailer) {
    /***
     * Creates a movie with given parameters and updates it into the list of movies, raises exception if movie doesn't exist
     */
    Movie movie(title, genre, year, likes, trailer);
    Movie old_movie = this->repository.update(movie);
    auto * operation = new UndoUpdate(repository, movie, old_movie);
    undo_service.record(operation);
}

Service::Service(Repository& repository, Repository* user_repository, Validator& validator, UndoService & undo_serv, UndoRedoServiceUser & undo_user):repository{repository}, user_repository{user_repository}, validator{validator}, undo_service{undo_serv}, undo_service_user{undo_user} {
}

Repository& Service::get_repository() {
    return this->repository;
}

Repository* Service:: get_user_repository(){
    return this->user_repository;
}

std::vector<Movie> Service::movies_by_genre(std::string genre){

    std::vector<Movie> movies=this->repository.get_movies();
    std::vector<Movie> result;
    if (genre == "")
        return movies;
    for(auto &movie: movies)
        if(movie.get_genre() == genre)
            result.push_back(movie);
    return result;

}


Validator &Service::getValidator() {
    return validator;
}

void Service::setUserRepository(Repository *userRepository) {
    user_repository = userRepository;
    undo_service_user.setUserRepository(userRepository);
}

void Service::rate_movie(std::string title) {
    this->repository.rate_movie(title);
}

void Service::undo() {
    this->undo_service.undo();
}

void Service::redo() {
    this->undo_service.redo();
}

void Service::undo_user() {
undo_service_user.undo();
}

void Service::redo_user() {
undo_service_user.redo();
}
