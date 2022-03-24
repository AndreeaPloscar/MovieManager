//
// Created by Andreea Ploscar on 24.05.2021.
//

#include "UndoService.h"

UndoService::UndoService( Repository &repo) :repository(repo){
    index = -1;
}

void UndoService::record(UndoRedo * operation){
history.erase(history.begin() + index + 1, history.end());
history.push_back(operation);
index ++;
}

void UndoService::undo(){
    if(index == -1)
        throw exception();
history[index]->undo();
index--;
}

void UndoService::redo(){
    if(index == history.size()-1)
        throw exception();
history[index+1]->redo();
index++;
}
