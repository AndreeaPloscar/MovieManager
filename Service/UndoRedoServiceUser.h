//
// Created by Andreea Ploscar on 28.05.2021.
//

#ifndef A10_915_PLOSCAR_ANDREEA_1_UNDOREDOSERVICEUSER_H
#define A10_915_PLOSCAR_ANDREEA_1_UNDOREDOSERVICEUSER_H
#include "UndoRedoUser.h"


class UndoRedoServiceUser {

    private:
        vector<UndoRedoUser *> history;
        Repository * user_repository;
        Repository & admin_repository;
public:
    void setUserRepository(Repository *userRepository);

private:
    int index;

    public:
        explicit UndoRedoServiceUser(Repository *repository, Repository &admin_repo);
        void record(UndoRedoUser * operation);
        void undo();
        void redo();


};


#endif //A10_915_PLOSCAR_ANDREEA_1_UNDOREDOSERVICEUSER_H
