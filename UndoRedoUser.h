//
// Created by Andreea Ploscar on 28.05.2021.
//

#ifndef A10_915_PLOSCAR_ANDREEA_1_UNDOREDOUSER_H
#define A10_915_PLOSCAR_ANDREEA_1_UNDOREDOUSER_H

#include "Repository.h"

class UndoRedoUser {
protected:
    Repository * repository;
    Movie movie;
    Repository & admin_repo;
public:
    UndoRedoUser(Repository * repository, Movie movie,Repository & admin_repository);
    virtual void undo() = 0;
    virtual void redo() = 0;
};

class UndoAddUser: public UndoRedoUser{
    void undo();

public:
    UndoAddUser(Repository *repository, const Movie movie,Repository & admin_repository);

private:
    void redo();
};

class UndoDeleteUser: public UndoRedoUser{
    void undo();
    void redo();
    bool rate;

public:
    UndoDeleteUser(Repository *repository, const Movie movie,Repository & admin_repository,bool);
};


#endif //A10_915_PLOSCAR_ANDREEA_1_UNDOREDOUSER_H
