#include "mainwindow.h"
#include <QApplication>
#include "NotesManager.h"

using namespace NM;

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;

    NotesManager &nm = NotesManager::getInstance();
    

    /*NArticle *na = new NArticle(13456);
    nm<<na;*/

    nm.getNewNArticle();

    w.show();

    //delete na;
    nm.releaseInstance();

    return a.exec();
}

