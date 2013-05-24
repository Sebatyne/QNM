#include "NoteFactory.h"

namespace NM {

//----------------NoteFactory----------------

NoteFactory::NoteFactory(QString & n)
    : name(n)
{
}

unsigned int NoteFactory::getNewId() {
    return QDateTime::currentDateTime().toTime_t();
}


//----------------ArticleFactory----------------

ArticleFactory::ArticleFactory(QString &n)
    : NoteFactory(n)
{
}

Note * ArticleFactory::buildNote(const QString &title) {
    return new NArticle(getNewId(), title);
}

/*Note * ArticleFactory::buildNote(NArticle *n) {
    NArticle *na = new NArticle(getNewId(), n->getTitle());
    na->setText((n->getText()));
    return na;
}*/


//----------------DocumentFactory----------------

DocumentFactory::DocumentFactory(QString & n)
    : NoteFactory(n)
{
}

Note * DocumentFactory::buildNote(const QString &title) {
    return new Document(getNewId(), title);
}


//----------------MediaFactory----------------

MediaFactory::MediaFactory(QString &n)
    : NoteFactory(n) {}

}
