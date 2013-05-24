#ifndef NOTEFACTORY_H
#define NOTEFACTORY_H

#include <QString>
#include <QMap>
#include <QDateTime>
#include "Note.h"

namespace NM {

class NoteFactory
{
    QString name;

protected :
    unsigned int getNewId();

public:
    NoteFactory(QString & n);

    const QString & getName() const {return name;}

    virtual Note * buildNote(const unsigned int id, const QString & title = "") = 0;
    virtual Note * buildNewNote(const QString & title = "") = 0;
    //virtual Note * buildNote(Note * n);
};

class ArticleFactory : public NoteFactory {

public :
    ArticleFactory(QString & n);

    Note * buildNote(const unsigned int id, const QString & title = "");
    Note * buildNewNote(const QString & title = "");
    //Note * buildNote(NArticle *n);
};

class DocumentFactory : public NoteFactory {

public :
    DocumentFactory(QString & n);

    Note * buildNote(const unsigned int id, const QString & title = "");
    Note * buildNewNote(const QString & title = "");
};

class MediaFactory : public NoteFactory {

public :
    MediaFactory(QString &n);

    virtual Note * buildNewNote(const QString &title) = 0;
};

}

#endif // NOTEFACTORY_H
