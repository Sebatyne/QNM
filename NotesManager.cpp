#include "NotesManager.h"

namespace NM {

    NotesManager *NotesManager::nmInstance = 0;

    NotesManager::NotesManager ()
        : path(QString("../Ressources/"))
    {
        QString s("NArticle");
        NoteFactory *nf = new ArticleFactory(s);
        factories.insert(s, nf);

        s = "Document";
        nf = new DocumentFactory(s);
        factories.insert(s, nf);

        s = "NVideo";
        nf = new VideoFactory(s);
        factories.insert(s, nf);

        s = "NAudio";
        nf = new AudioFactory(s);
        factories.insert(s, nf);

        s = "NImage";
        nf = new ImageFactory(s);
        factories.insert(s, nf);

        loadWorkspace(QString("workspace1"));
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
        QSet<Note*>::iterator i;
        for (i = notes.begin(); i != notes.end(); ++i) {
            if ((*i)->isModified())
                save(*i);
            delete *i;
        }
    }

    void NotesManager::loadWorkspace(QString fold) {
        if (fold == "")
            fold = "workspace1";

        workspace.mkdir(path + fold);   //crée le dossier si jamais il n'existe pas
        workspace.setPath(path + fold);

        //parcourt le dossier. Si note : ajout au set notes. Si document, crée un document,
        //l'ajoute au set notes, lui fait référencer ses notes (les crée au besoin, en not loaded)

        workspace.setFilter(QDir::Files | QDir::NoSymLinks | QDir::NoDotAndDotDot | QDir::Readable | QDir::Writable);
        QStringList dir = workspace.entryList();

        //lecture des fichiers
        for (int i = 0; i < dir.size(); i++) {
            //affiche le nom du fichier disque correspondant
            qDebug() <<  workspace.path() + "/" + dir.at(i);

            //on déclare un descripteur de fichier, ouvert en read-only
            QFile fd(workspace.path() + "/" + dir.at(i));
            fd.open(QIODevice::ReadOnly);

            //on récupère l'id de la note, son type et son titre (chop supprime le dernier caractère de ligne "\n"
            QString sid = fd.readLine();
            sid.chop(1);
            unsigned int id = sid.toUInt(); //vérification du nom ??
            qDebug() << id;
            QString type = fd.readLine();
            type.chop(1);
            QString title = fd.readLine();
            title.chop(1);

            //ajout à notes de la note qui vient d'être lue, puis fermeture de la note
            qDebug() << "type :" << type<< " title :" << title;
            notes << factories[type]->buildNote(id, title);

            fd.close();
        }


    }

    Note* NotesManager::getNote (unsigned int id) {
        QSet<Note*>::iterator i;
        for (i = notes.begin(); i != notes.end(); ++i) {
            if ((*i)->getId() == id)
                return *i;
        }
        return 0;
    }

    void NotesManager::addArticle (Note*n) {
        notes<<n;
    }

    void NotesManager::operator <<(Note *n) {
        notes<<n;
    }

    Note & NotesManager::getNewNote(const QString & fact) {
        if(factories.keys().indexOf(fact) != -1) {
            Note *na = factories[fact]->buildNewNote();
            notes<<na;
            return *na;
        } else {
            throw "this factory does not exist";
        }
    }

    Note & NotesManager::getNewNArticle () {
        Note *na = factories["NArticle"]->buildNewNote();
        notes<<na;
        return *na;
    }

    Note & NotesManager::getNewDocument() {
        Note *na = factories["Document"]->buildNewNote();
        notes<<na;
        return *na;
    }

    void NotesManager::save(const Note * note) const {
        QFile fd(workspace.path() + "/" + QString::number(note->getId()));
        fd.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text);

        QTextStream in(&fd);
        in << note->toText();

        fd.close();
    }
}
