#include "NoteFactory.h"

namespace NM {

    //----------------NoteFactory----------------

    NoteFactory::NoteFactory(QString & n)
        : name(n)
    {
    }

    unsigned int NoteFactory::getNewId() {
        unsigned int i = QDateTime::currentDateTime().toTime_t();

        while (NotesManager::getInstance().getNote(i)) {
            i = QDateTime::currentDateTime().toTime_t();
        }

        return i;
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

    //----------------AudioFactory----------------

    Note * AudioFactory::buildNote(const unsigned int id, const QString &title){
        return new NAudio(id, title);
    }

    Note * AudioFactory::buildNewNote(const QString &title){
        NAudio * a = new NAudio(getNewId(), title);
        a->setModified();
        return a;
    }

    //----------------ImageFactory----------------

    Note * ImageFactory::buildNote(const unsigned int id, const QString &title){
        return new NImage(id, title);
    }

    Note * ImageFactory::buildNewNote(const QString &title){
        NImage * im = new NImage(getNewId(), title);
        im->setModified();
        return im;
    }

    //----------------VideoFactory----------------

    Note * VideoFactory::buildNote(const unsigned int id, const QString &title){
        return new NImage(id, title);
    }

    Note * VideoFactory::buildNewNote(const QString &title){
        NVideo * vi = new NVideo(getNewId(), title);
        vi->setModified();
        return vi;
    }
}
