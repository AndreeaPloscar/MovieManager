//
// Created by Andreea Ploscar on 05.05.2021.
//

#ifndef A89_915_PLOSCAR_ANDREEA_EXCEPTION_H
#define A89_915_PLOSCAR_ANDREEA_EXCEPTION_H


#include "exception"
#include "string"
using namespace std;

class RepositoryException: public std::exception {
    string msg;
public:
    RepositoryException(string _msg): msg(_msg){};
    string getMsg(){return this->msg;}
};

class InputException: public std::exception{
    string msg;
public:
    InputException(string _msg): msg(_msg){};
    string getMsg(){return this->msg;}
};

class ValidatorException: public std::exception{
    string msg;
public:
    ValidatorException(string _msg): msg(_msg){};
    string getMsg(){return this->msg;}
};


#endif //A89_915_PLOSCAR_ANDREEA_EXCEPTION_H
