#ifndef NOTESMANAGER_H
#define NOTESMANAGER_H

#include <QString>
#include <QSet>
#include <QMap>
#include "Note.h"
#include "NoteFactory.h"

namespace NM {

class NotesManager {
    QSet<Note*> Notes_list;
    static NotesManager* nmInstance;
    QMap<QString, NoteFactory*> factories;

protected :
    NotesManager();

public :
    static NotesManager & getInstance ();
    static void releaseInstance ();

    unsigned int getNbNotes () const {return Notes_list.size();}

    void addArticle (NArticle *a);
    void operator <<(NArticle *a);

    Note & getNewNArticle();
};

}

#endif // NOTESMANAGER_H
