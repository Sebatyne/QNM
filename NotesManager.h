#ifndef NOTESMANAGER_H
#define NOTESMANAGER_H

#include <QString>
#include <QSet>
#include <QMap>
#include "Note.h"
#include "NoteFactory.h"

namespace NM {

class NotesManager {
    QSet<Note*> notes;
    QSet<Note*> corbeille;
    static NotesManager* nmInstance;
    QMap<QString, NoteFactory*> factories;

protected :
    NotesManager();
    ~NotesManager();

public :
    static NotesManager & getInstance ();
    static void releaseInstance ();

    unsigned int getNbNotes () const {return notes.size();}

    void addArticle (Note *n);
    void operator <<(Note *n);

    Note & getNewNote(const QString & fact);
    Note & getNewNArticle();
    Note & getNewDocument();
};

}

#endif // NOTESMANAGER_H
