//
// Created by Andreea Ploscar on 28.05.2021.
//

#include "UndoRedoUser.h"
UndoRedoUser::UndoRedoUser(Repository *repository, Movie movie,Repository & admin_repository) : repository(repository), movie(movie), admin_repo(admin_repository){}


void UndoDeleteUser::undo() {
    this->repository->add(this->movie);
   if(this->rate)
       this->admin_repo.unrate_movie(this->movie.get_title());

}

void UndoDeleteUser::redo() {
    this->repository->remove(this->movie.get_title());
    if(this->rate)
        this->admin_repo.rate_movie(this->movie.get_title());
}

UndoDeleteUser::UndoDeleteUser(Repository *repository, const Movie movie,Repository & admin_repository,bool rate) : UndoRedoUser(repository, movie, admin_repository),rate(rate) {}


void UndoAddUser::undo() {
    this->repository->remove(movie.get_title());
}

void UndoAddUser::redo() {
    this->repository->add(movie);
}

UndoAddUser::UndoAddUser(Repository *repository, const Movie movie,Repository & admin_repository) : UndoRedoUser(repository, movie,admin_repository) {}
