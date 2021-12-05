
#include <QApplication>
#include <QPushButton>
#include "Gui.h"
#include "Test.h"
#include "UndoService.h"
#include "UndoRedoServiceUser.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    Repository test_repo;
    Repository* test_user_repo = new Repository();
    Validator validator;

    //Service test_service{test_repo, test_user_repo, validator, undo_service};
    //Test test(test_repo, test_service, *test_user_repo);
    //test.test_all();
    FileRepository repo = FileRepository("input.txt", "/Users/andreeaploscar/CLionProjects/a10-915-Ploscar-Andreea-1/");
    Repository * user_repo = new Repository();
    UndoService undo_service{repo};
    UndoRedoServiceUser undo_service_user{user_repo,repo};
    Service service{repo, user_repo, validator, undo_service, undo_service_user};
    Gui* gui = new Gui(service);
    gui->show();
    return app.exec();
}