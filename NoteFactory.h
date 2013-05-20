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

    virtual Note * buildNote(const QString & s = "") = 0;
    virtual Note * buildNote(Note * n) = 0;
};

class ArticleFactory : public NoteFactory {

public :
    ArticleFactory(QString & n);

    Note * buildNote(const QString & s = "");
    Note * buildNote(NArticle * n);
};

}

#endif // NOTEFACTORY_H
