//
// Created by Andreea Ploscar on 05.05.2021.
//

#ifndef A89_915_PLOSCAR_ANDREEA_SERVICE_H
#define A89_915_PLOSCAR_ANDREEA_SERVICE_H


#include "Repository.h"
#include "Validator.h"
#include "UndoRedo.h"
#include "UndoService.h"
#include "UndoRedoServiceUser.h"

class Service {
private:
    Repository & repository;
    Repository * user_repository;
    Validator& validator;
    UndoService & undo_service;
    UndoRedoServiceUser & undo_service_user;

public:
    vector<std::string> get_all_genres();
    Validator &getValidator();
    int get_movies_by_year(std::string year, std::string genre);
    void setUserRepository(Repository * userRepository);
    Service(Repository &repository, Repository * user_repository, Validator &validator, UndoService & service,UndoRedoServiceUser& undo_serv_user);
    Repository& get_repository();
    std::string get_command();
    Repository* get_user_repository();
    Movie remove_movie_user(std::string title,bool rate);
    void rate_movie(std::string title);
    void add_movie_admin(std::string title, std::string genre, int year, int likes, std::string trailer  );
    void remove_movie_admin(std::string  title);
    void update_movie(std::string title, std::string genre, int year, int likes, std::string  trailer );
    std::vector<Movie> movies_by_genre(std::string);
    void add_movie_user( std::string title,std::string genre, int year, int likes, std::string trailer);
    void undo();
    void redo();
    void undo_user();
    void redo_user();

};


#endif //A89_915_PLOSCAR_ANDREEA_SERVICE_H
