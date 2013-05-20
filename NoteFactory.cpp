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

Note * ArticleFactory::buildNote(const QString &s) {
    return new NArticle(getNewId(), s);
}

Note * ArticleFactory::buildNote(NArticle *n) {
    NArticle *na = new NArticle(getNewId(), n->getTitle());
    na->setText((n->getText()));
    return na;
}

}
