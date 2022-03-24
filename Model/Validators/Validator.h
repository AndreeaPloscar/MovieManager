//
// Created by Andreea Ploscar on 05.05.2021.
//

#ifndef A89_915_PLOSCAR_ANDREEA_VALIDATOR_H
#define A89_915_PLOSCAR_ANDREEA_VALIDATOR_H


#include "string"

class Validator {
public:
    void validate_movie(std::string title, std::string genre, int year, int likes, std::string trailer );
    bool validate_option(char * command);
    bool validate_integer(std::string);
};



#endif //A89_915_PLOSCAR_ANDREEA_VALIDATOR_H
