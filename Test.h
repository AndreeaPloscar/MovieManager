//
// Created by Andreea Ploscar on 05.05.2021.
//

#ifndef A89_915_PLOSCAR_ANDREEA_TEST_H
#define A89_915_PLOSCAR_ANDREEA_TEST_H

#include "Repository.h"
#include "Service.h"
#include "Movie.h"

class Test {
private:
    Repository & repo;
    Service & service;
    Repository & user_repo;
public:
    Test(Repository &repo, Service &service, Repository &userRepo);

public:
    static void test_movie();
    void test_add();
    void test_find();
    void test_remove();
    void test_update();
    void test_add_movie();
    void test_remove_movie();
    void test_update_movie();
    void test_all();
    void test_get_repository();
    void test_movies_by_genre();

};


#endif //A89_915_PLOSCAR_ANDREEA_TEST_H
