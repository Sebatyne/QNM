#include "NotesManager.h"

namespace NM {

NotesManager *NotesManager::nmInstance = 0;

NotesManager::NotesManager ()
    : path(QString("../Ressources/"))
{
    QString s("ArticleFactory");
    NoteFactory *nf = new ArticleFactory(s);
    factories.insert(s, nf);

    s = "DocumentFactory";
    nf = new DocumentFactory(s);
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

NotesManager::~NotesManager(){
    //delete sur les factories, les notes si elles ne sont pas enregistrées...
}

void NotesManager::loadWorkspace(QString fold) {
    if (fold == "")
        fold = "workspace1";

    workspace.mkdir(path + fold);   //crée le dossier si jamais il n'existe pas
    workspace.setPath(path + fold);

    //parcourt le dossier. Si note : ajout au set notes. Si document, crée un document,
    //l'ajoute au set notes, lui fait référencer ses notes (les crée au besoin, en not loaded)

    workspace.setFilter(QDir::Files | QDir::NoSymLinks | QDir::NoDotAndDotDot	| QDir::Readable | QDir::Writable);
    QFileInfoList dir = workspace.entryInfoList();

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

Note & NotesManager::getNewDocument() {
    Note *na = factories["DocumentFactory"]->buildNote();
    notes<<na;
    return *na;
}

}
