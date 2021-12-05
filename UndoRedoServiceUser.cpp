//
// Created by Andreea Ploscar on 28.05.2021.
//

#include "UndoRedoServiceUser.h"
UndoRedoServiceUser::UndoRedoServiceUser( Repository *repo, Repository&admin_repo) :user_repository(repo), admin_repository(admin_repo){
    index = -1;
}

void UndoRedoServiceUser::record(UndoRedoUser * operation){
    history.erase(history.begin() + index + 1, history.end());
    history.push_back(operation);
    index ++;
}

void UndoRedoServiceUser::undo(){
    if(index == -1)
        throw exception();
    history[index]->undo();
    index--;
}

void UndoRedoServiceUser::redo(){
    if(index == history.size()-1)
        throw exception();
    history[index+1]->redo();
    index++;
}

void UndoRedoServiceUser::setUserRepository(Repository *userRepository) {
    user_repository = userRepository;
}
