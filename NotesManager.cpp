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



void NotesManager::addArticle (Note*n) {
    notes<<n;
}

void NotesManager::operator <<(Note *n) {
    notes<<n;
}

Note & NotesManager::getNewNote(const QString & fact) {
    if(factories.keys().indexOf(fact) != -1) {
        Note *na = factories[fact]->buildNote();
        notes<<na;
        return *na;
    } else {
        throw "this factory does not exist";
    }
}

Note & NotesManager::getNewNArticle () {
    Note *na = factories["ArticleFactory"]->buildNote("titre");
    notes<<na;
    return *na;
}
}
