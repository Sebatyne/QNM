#include "NotesManager.h"

namespace NM {

NotesManager *NotesManager::nmInstance = 0;

NotesManager::NotesManager () {
    QString s("ArticleFactory");
    NoteFactory *nf = new ArticleFactory(s);
    factories.insert(s, nf);
}

NotesManager & NotesManager::getInstance () {
    if (nmInstance == 0) {
        nmInstance = new NotesManager();
    }

    return *nmInstance;
}

void NotesManager::releaseInstance () {
    if (nmInstance != 0) {
        delete nmInstance;
    }
    nmInstance = 0;
}

Note & NotesManager::getNewNArticle () {
    Note *na = factories["ArticleFactory"]->buildNote("titre");
    Notes_list<<na;
    return *na;
}

void NotesManager::addArticle (NArticle *a) {
    Notes_list<<a;
}

void NotesManager::operator <<(NArticle *a) {
    this->addArticle(a);
}

}
