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
    virtual ~Note() {};

    const QString & getTitle () const {return title;}
    unsigned int getId () const {return id;}
    bool isModified () {return modified;}

    void setTitle (const QString & te) {title = te;}
    void setLoaded() {loaded = true;}
    void setModified () {modified = true;}


    virtual QString toText() const = 0;
    virtual void load() = 0;

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

    const QString & getText () const {return text;};
    void setText (const QString & txt) {text = txt;};

    QString toText () const;
    void load();

    void log() const;

};

class Document : public Note {
    QList<Note*> notes;
public :
    Document(unsigned int i,const QString & te = "");

    void addNote (Note *n);
    void operator<< (Note *n);

    void removeNote (Note *n);

    QString toText () const;
    void load();

    void log() const;
};


class NMedia : public Note{
    QString url;    //qui peut aussi contenir un path
    QString description;

protected :
    NMedia(unsigned int i, const QString & te = "" , const QString & u = "", const QString & desc = "");

public :
    const QString & getUrl() const{return url;}
    void setUrl(const QString & url);

    const QString & getDescription() const{return description;}
    void setDescription(QString const & description);

    void log() const;
};


class NAudio : public NMedia{
public:
    NAudio(unsigned int i, const QString & te = "", const QString & url = "", const QString & desc = "");
};

class NVideo : public NMedia{
public:
    NVideo(unsigned int i, const QString & te = "", const QString & url = "", const QString & desc = "");
};

class NImage : public NMedia{
    NImage(unsigned int i, const QString & te = "", const QString & url = "", const QString & desc = "");
};

}
