#ifndef NOTE_H
#define NOTE_H

#include <QString>
#include <QDebug>
#include <QList>

namespace NM {

class Note {
private :
    Note(const Note & n);

protected :
    unsigned int id;
    QString title;
    bool loaded;
    bool modified;

public :
    Note(const unsigned int i, const QString & te = "");
    virtual ~Note() {};

    const QString & getTitle () const {return title;}
    unsigned int getId () const {return id;}

    void setTitle (const QString & te) {title = te;}

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

    void log() const;

};

class Document : public Note {
    QList<Note*> notes;
public :
    Document(unsigned int i,const QString & te = "");

    void addNote (Note *n);
    void operator<< (Note *n);

    void removeNote (Note *n);

    void log() const;
};

class NMedia : public Note {
    QString description;
    QString path;

public :
    NMedia(unsigned int i, const QString & te = "", const QString & desc = "", const QString & pa = "");

    void log() const;
};

}

#endif // NOTE_H
