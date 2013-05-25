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

Note * ArticleFactory::buildNote(const unsigned int id, const QString &title) {
    return new NArticle(id, title);
}

Note * ArticleFactory::buildNewNote(const QString &title) {
    NArticle *a = new NArticle(getNewId(), title);
    a->setModified();
    return a;
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

Note * DocumentFactory::buildNote(const unsigned int id, const QString &title) {
    return new Document(id, title);
}

Note * DocumentFactory::buildNewNote(const QString &title) {
    Document *d = new Document(getNewId(), title);
    d->setModified();
    return d;
}


//----------------MediaFactory----------------

MediaFactory::MediaFactory(QString &n)
    : NoteFactory(n) {}

}
