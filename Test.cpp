//
// Created by Andreea Ploscar on 05.05.2021.
//

#include "Test.h"

#include "Test.h"
#include "cassert"
#include "string"
#include "iostream"
#include "sstream"
#include "Exception.h"
using namespace std;

void Test::test_movie() {
    Movie *movie = new Movie();
    movie->set_title("Title");
    assert(movie->get_title() ==  "Title");
    movie->set_trailer("Trailer");
    assert(movie->get_trailer() == "Trailer");
    movie->set_genre("Genre");
    assert(movie->get_genre() == "Genre");
    movie->set_number(10);
    assert(movie->get_number() == 10);
    movie->set_year(2010);
    assert(movie->get_year() == 2010);
    string expected = "Title: Title\nGenre: Genre\nYear: 2010\nLikes: 10\nTrailer: Trailer\n\n";
    std::stringstream buffer;
    std::streambuf *prevcoutbuf = std::cout.rdbuf(buffer.rdbuf());
    std::cout << *movie << std::endl;
    std::string text = buffer.str();
    int result = text.compare(expected);
    std::cout.rdbuf(prevcoutbuf);
    assert(result == 0);
    delete movie;
}

void Test::test_add() {
    Movie movie =  Movie("Title", "Genre", 2010, 100, "Trailer");
    this->repo.add(movie);
    assert(this->repo.get_movies()[0].get_title() == "Title");
    try{
        this->repo.add(movie);
        assert(false);
    }
    catch (RepositoryException error){
        assert(true);
    }
    this->repo.remove("Title");
}

void Test::test_find() {
    Movie movie = Movie("Title", "Genre", 2010, 100, "Trailer");
    this->repo.add(movie);
    assert(this->repo.find("Title"));
    this->repo.remove("Title");
    assert(not this->repo.find("Title"));
}

void Test::test_remove() {
    Movie movie("Title", "Genre", 2010, 100, "Trailer");
    this->repo.add(movie);
    this->repo.remove("Title");
    assert(not this->repo.find("Title"));
    try{
        this->repo.remove("Title");
        assert(false);
    }
    catch (RepositoryException& e){
        assert(true);
    }
}

void Test::test_update() {
    Movie movie("Title", "Genre", 2010, 100, "Trailer");
    this->repo.add(movie);
    Movie movie2("Title2", "Genre", 2010, 100, "Trailer");
    this->repo.add(movie2);
    this->repo.update(movie2);
    this->repo.remove("Title2");
    try{
        this->repo.update(movie2);

        assert(false);
    }
    catch (RepositoryException& error){
        assert(true);
    }
    this->repo.remove("Title");
}

void Test::test_add_movie() {
    assert(this->service.get_repository().get_movies().empty());
    for (int i = 0; i < 100; i ++)
    {   char title[30];
        auto title_s = std::to_string(i);
        strcpy(title, title_s.c_str());
        this->service.add_movie_admin(title, "Genre", 2000, 100, "Trailer");
        try{
            this->service.add_movie_admin(title, "Genre", 2000, 100, "Trailer");
            assert(false);
        }
        catch (RepositoryException& e){
            assert(true);
        }
    }
    assert(this->service.get_user_repository()->get_movies().empty());
    this->service.add_movie_user("Title", "Genre", 2000, 100, "Trailer");
    try{
        this->service.add_movie_user("Title", "Genre", 2000, 100, "Trailer");
        assert(false);
    }
    catch (RepositoryException& e){
        assert(true);
    }
    assert(this->user_repo.get_movies().size()==1);
    this->service.remove_movie_user("Title",true);
}


void Test::test_remove_movie() {
    char title[30];
    string title_s;
    for (int i = 0; i < 100; i ++)
    {
        title_s = std::to_string(i);
        strcpy(title, title_s.c_str());
        this->service.remove_movie_admin(title);
        try{
            this->service.remove_movie_admin(title);
            assert(false);
        }
        catch (RepositoryException& error){
            assert(true);

        }
    }
    this->service.add_movie_user("Title", "Genre", 2000, 100, "Trailer");
    this->service.remove_movie_user("Title",true);
    try{
        this->service.remove_movie_user("Title",true);
        assert(false);
    }
    catch (RepositoryException& error){
        assert(true);
    }
}

void Test::test_update_movie() {
    this->service.add_movie_admin("Title", "Genre", 2000, 100, "Trailer");
    this->service.update_movie("Title", "New Genre", 2000, 100, "Trailer");
    try{
        this->service.update_movie("Title2", "New Genre", 2000, 100, "Trailer");
        assert(false);
    }
    catch (RepositoryException& error){
        assert(true);
    }
    this->service.remove_movie_admin("Title");
}

void Test::test_movies_by_genre(){
    this->service.add_movie_admin("Title", "New Genre", 2000, 100, "Trailer");
    this->service.add_movie_admin("Title2", "Genre", 2000, 100, "Trailer");
    std::vector<Movie> movies = this->service.movies_by_genre("");
    assert(movies.size()==2);
    std::vector<Movie> movies2 = this->service.movies_by_genre("New Genre");
    assert(movies2.size()==1);
}




void Test::test_all() {
    this->test_add();
    this->test_add_movie();
    this->test_find();
    this->test_movie();
    this->test_remove();
    this->test_remove_movie();
    this->test_update();
    this->test_update_movie();

    this->test_movies_by_genre();
    cout << "All tests passed\n\n";}

Test::Test(Repository &repo, Service &service, Repository &userRepo) : repo(repo), service(service),
                                                                       user_repo(userRepo) {}
