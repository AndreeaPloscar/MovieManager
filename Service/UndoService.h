//
// Created by Andreea Ploscar on 24.05.2021.
//

#ifndef A10_915_PLOSCAR_ANDREEA_1_UNDOSERVICE_H
#define A10_915_PLOSCAR_ANDREEA_1_UNDOSERVICE_H
#include "vector"
#include "UndoRedo.h"

class UndoService {
private:
    vector<UndoRedo *> history;
    Repository & repository;
    int index;

public:
    explicit UndoService(Repository &repository);
    void record(UndoRedo * operation);
    void undo();
    void redo();

};


#endif //A10_915_PLOSCAR_ANDREEA_1_UNDOSERVICE_H
