#ifndef NOTESMANAGER_H
#define NOTESMANAGER_H

#include <QString>
#include <QSet>
#include <QMap>
#include <QDir>
#include <QFile>
#include <QStringList>
#include <QDebug>
#include <QTextStream>
#include "Note.h"
#include "NoteFactory.h"

namespace NM {

class NotesManager {
    QSet<Note*> notes;
    QSet<Note*> corbeille;
    static NotesManager* nmInstance;
    QMap<QString, NoteFactory*> factories;
    QString path;   //chemin par défaut des workspace
    QDir workspace; //

protected :
    NotesManager();
    ~NotesManager();

public :
    static NotesManager & getInstance ();
    static void releaseInstance ();

    unsigned int getNbNotes () const {return notes.size();}

    //load un workspace par défaut situé dans ../Ressources/workspace1
    void loadWorkspace (QString fold);

    void addArticle (Note *n);
    void operator <<(Note *n);

    Note & getNewNote(const QString & fact);
    Note & getNewNArticle();
    Note & getNewDocument();

    void save(const Note * note) const;
};

}

#endif // NOTESMANAGER_H
