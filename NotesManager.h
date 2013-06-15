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
#include <QtXml>
#include <QPalette>
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

    protected :
        NotesManager();
        ~NotesManager();

    public :
        static NotesManager & getInstance ();
        static void releaseInstance ();

        unsigned int getNbNotes () const {return notes.size();}
        const QDir getWorkspace () const {return workspace;}
        Note * getNote(unsigned int id);

        const QSet<Note*> returnSetNotes() const {return notes;}

        //load un workspace par défaut situé dans ../Ressources/workspace1
        void loadWorkspace (QString fold);

        void addArticle (Note *n);
        void operator <<(Note *n);

        Note & getNewNote(const QString & fact);
        Note & getNewNArticle();
        Note & getNewDocument();
        Note & getNewNImage();
        Note & getNewNAudio();
        Note & getNewNVideo();


        void save(Note *note) const;
        void saveWorkspace();

        void deleteNote(Note *n);
        Note* restoreNote(unsigned int id);

        void createNoteFromNode(const QDomNode n);
        //void createDocFromNode(const QDomNode n);

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

        //fonctions de l'itérateur
            Iterator begin() {return Iterator(notes);}
            Iterator end() {Iterator i(notes.end()); return i;}

            Iterator corbeille_begin() {return Iterator(corbeille);}
            Iterator corbeille_end() {Iterator i(corbeille.end()); return i;}
    };
}

#endif // NOTESMANAGER_H
