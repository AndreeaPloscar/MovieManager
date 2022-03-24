//
// Created by Andreea Ploscar on 05.05.2021.
//

#include "Validator.h"
#include "Exception.h"

bool Validator::validate_option(char * command){
    if (command[0] > '0' && command[0] <= '4' && command[1] == 0)
        return true;
    return false;
}

bool Validator::validate_integer(std::string string) {
    try {
        std::stoi(string);
        return true;
    }
    catch (...) {
        return false;
    }
}

void Validator::validate_movie(std::string title, std::string genre, int year, int likes, std::string trailer) {
    if (title == "")
        throw ValidatorException("Title should not be empty!");
    if (genre == "")
        throw ValidatorException("Genre should not be empty!");
    if(year < 0)
        throw ValidatorException("Year should be a positive number!");
    if(likes < 0)
        throw ValidatorException("The number of likes should be a positive integer!");
    if(trailer == "")
        throw ValidatorException("Trailer should not be empty!");
}


