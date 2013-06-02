#pragma once

#include <QString>
#include <QDebug>
#include <QList>
#include <QFile>
#include "NotesManager.h"

namespace NM {

    class Note {
    private :
        Note(const Note & n);

    protected :
        Note(const unsigned int i = 0, const QString & te = "");

        unsigned int id;
        QString title;
        bool loaded;
        bool modified;

    public :
        enum noteType{NArticle, Document, NVideo, NAudio, NImage};

        virtual ~Note() {}

        const QString & getTitle () const {return title;}
        unsigned int getId () const {return id;}
        bool isModified () const {return modified;}

        void setTitle (const QString & te) {title = te;}
        void setLoaded() {loaded = true;}
        void setModified () {modified = true;}


        virtual QString toText() const = 0;
        virtual void load() = 0;

        virtual noteType getType() const = 0;

        bool operator<(const Note & n ) {return this->id < n.getId();}
        bool operator>(const Note & n ) {return this->id > n.getId();}
        bool operator==(const Note & n) {return this->id == n.getId();}
        bool operator!=(const Note & n) {return this->id != n.getId();}

        virtual void log() const = 0;

    };

    class NArticle : public Note {
        QString text;

    public :
        NArticle(unsigned int i,const QString & te = "", const QString & txt = "");
        ~NArticle() {}

        const QString & getText () const {return text;}
        void setText (const QString & txt) {text = txt;}

        QString toText () const;
        void load();

        Note::noteType getType() const {return Note::NArticle;}

        void log() const;

    };

    class Document : public Note {
        QList<Note*> notes;
    public :

        class Iterator {
            friend class Document;
            QList<Note*>::iterator i;

        public :
            Iterator(QList<Note*> &s) {i=s.begin();}
            Iterator(QList<Note*>::iterator j) {i = j;}
            Note * operator*() {return *(i);}
            Iterator operator++() {i++; return *this;}
            Iterator operator++(int) {Iterator j(i); i++; return j;}
            Iterator operator--() {i--; return i;}
            Iterator operator--(int) {Iterator j(i); i--; return j;}
            bool operator==(QList<Note*>::iterator j) {return i==j;}
            bool operator!=(QList<Note*>::iterator j) {return i!=j;}
            bool operator!=(Iterator j) {return (*i)!=(*j);}
        };

        Document(unsigned int i,const QString & te = "");

        void addNote (Note *n);
        void operator<< (Note *n);

        void removeNote (Note *n);

        QString toText () const;
        void load();

        Note::noteType getType() const {return Note::Document;}

        Iterator begin() {return Iterator(notes);}
        Iterator end() {Iterator i(notes.end()); return i;}

        void log() const;
    };


    class NMedia : public Note{
    protected :
        QString url;    //qui peut aussi contenir un path
        QString description;
        NMedia(unsigned int i, const QString & te = "" , const QString & u = "", const QString & desc = "");

    public :
        const QString & getUrl() const{return url;}
        void setUrl(const QString & url);

        const QString & getDescription() const {return description;}
        void setDescription(QString const & description);

        virtual QString toText() const = 0;
        virtual Note::noteType getType() const = 0;


        void log() const;

        void load();
    };


    class NAudio : public NMedia{
    public:
        NAudio(unsigned int i, const QString & te = "", const QString & url = "", const QString & desc = ""): NMedia(i, te, url, desc) {}
        QString toText() const;
        Note::noteType getType() const {return Note::NAudio;}
    };

    class NVideo : public NMedia{
    public:
        NVideo(unsigned int i, const QString & te = "", const QString & url = "", const QString & desc = ""): NMedia(i, te, url, desc) {}
        QString toText() const;
        Note::noteType getType() const {return Note::NVideo;}
    };

    class NImage : public NMedia{
    public:
        NImage(unsigned int i, const QString & te = "", const QString & url = "", const QString & desc = ""): NMedia(i, te, url, desc) {}
        QString toText() const;
        Note::noteType getType() const {return Note::NImage;}
    };

}
