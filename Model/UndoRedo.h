//
// Created by Andreea Ploscar on 25.05.2021.
//

#ifndef A10_915_PLOSCAR_ANDREEA_1_UNDOREDO_H
#define A10_915_PLOSCAR_ANDREEA_1_UNDOREDO_H
#include "Repository.h"

class UndoRedo {
protected:
    Repository & repository;
    Movie movie;
public:
    UndoRedo(Repository & repository, Movie movie);
    virtual void undo() = 0;
    virtual void redo() = 0;
};

class UndoAdd: public UndoRedo{
    void undo();

public:
    UndoAdd(Repository &repository, const Movie movie);

private:
    void redo();
};

class UndoDelete: public UndoRedo{
    void undo();
    void redo();

public:
    UndoDelete(Repository &repository, const Movie movie);
};

class UndoUpdate: public UndoRedo{
private:
    Movie old_movie;
public:
    void undo();

    UndoUpdate(Repository &repository, const Movie movie, const Movie oldMovie);

    void redo();
};



#endif //A10_915_PLOSCAR_ANDREEA_1_UNDOREDO_H
