//
// Created by Andreea Ploscar on 25.05.2021.
//

#include "UndoRedo.h"

UndoRedo::UndoRedo(Repository &repository, Movie movie) : repository(repository), movie(movie) {}


void UndoDelete::undo() {
    this->repository.add(this->movie);
}

void UndoDelete::redo() {
    this->repository.remove(this->movie.get_title());
}

UndoDelete::UndoDelete(Repository &repository, const Movie movie) : UndoRedo(repository, movie) {}

void UndoUpdate::undo() {
    this->repository.update(old_movie);
}

void UndoUpdate::redo() {
    this->repository.update(movie);
}

UndoUpdate::UndoUpdate(Repository &repository, const Movie movie, const Movie oldMovie) : UndoRedo(repository, movie),
                                                                                            old_movie(oldMovie) {}

void UndoAdd::undo() {
    this->repository.remove(movie.get_title());
}

void UndoAdd::redo() {
    this->repository.add(movie);
}

UndoAdd::UndoAdd(Repository &repository, const Movie movie) : UndoRedo(repository, movie) {}
