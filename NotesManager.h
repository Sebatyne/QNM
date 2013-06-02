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

class Note;
class NoteFactory;

class NotesManager {
    QSet<Note*> notes;
    QSet<Note*> corbeille;
    static NotesManager* nmInstance;
    QMap<QString, NoteFactory*> factories;
    QString path;   //chemin par défaut des workspace
    QDir workspace; //

    class Iterator {
        friend class NotesManager;
        QSet<Note*>::iterator i;

    public :
        Iterator(QSet<Note*> &s) {i=s.begin();}
        Iterator(QSet<Note*>::iterator j) {i = j;}
        Note * operator*() {return *(i);}
        Iterator operator++() {i++; return *this;}
        Iterator operator++(int) {Iterator j(i); i++; return j;}
        Iterator operator--() {i--; return i;}
        Iterator operator--(int) {Iterator j(i); i--; return j;}
        bool operator==(QSet<Note*>::iterator j) {return i==j;}
        bool operator!=(QSet<Note*>::iterator j) {return i!=j;}
        bool operator!=(Iterator j) {return (*i)!=(*j);}
    };

protected :
    NotesManager();
    ~NotesManager();

public :
    static NotesManager & getInstance ();
    static void releaseInstance ();

    unsigned int getNbNotes () const {return notes.size();}
    const QDir getWorkspace () const {return workspace;}
    Note *getNote(unsigned int id);

    //load un workspace par défaut situé dans ../Ressources/workspace1
    void loadWorkspace (QString fold);

    void addArticle (Note *n);
    void operator <<(Note *n);

    Note & getNewNote(const QString & fact);
    Note & getNewNArticle();
    Note & getNewDocument();

    void save(const Note * note) const;

    //fonctions de l'itérateur
    Iterator begin() {return Iterator(notes);}
    Iterator end() {Iterator i(notes.end()); return i;}
};

}

#endif // NOTESMANAGER_H
