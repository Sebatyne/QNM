#include "Note.h"

namespace NM {


//-----------------NOTE-------------------
Note::Note(const unsigned int i, const QString &te)
    : id(i), title(te), loaded(false), modified(false)
{
    this->log();
}

void Note::log() const {};


//-----------------NARTICLE---------------
NArticle::NArticle(unsigned int i, const QString &te, const QString &txt)
    : Note(i, te), text(txt)
{
    log();
}

QString NArticle::toText () const {
    QString str;

    str = QString::number(id) + "\n";
    str += "NArticle\n";
    str += title + "\n\n";
    str += text;

    return str;
}

void NArticle::log() const {
    qDebug() << "Article : " << getId() << "\n";
    //std::cout<< "Article :" << getId() << std::endl;
}


//-----------------Document----------------
Document::Document(unsigned int i, const QString &te)
    : Note(i, te)
{
    log();
}

void Document::addNote(Note *n) {
    notes << n;
}

void Document::operator <<(Note *n) {
    notes << n;
}

void Document::removeNote(Note *n) {
    notes.removeOne(n);
}

QString Document::toText () const {
    QString str;

    str = QString::number(id)
            + "Document\n"
            + title + "\n\n";

    //  --------- il faut encore ajouter les notes ----------

    QListIterator<Note*> i(notes);
     while (i.hasNext()) {
         str += QString::number(i.next()->getId());
     }

    return str;
}

void Document::log() const {
    qDebug() << "Document" << getId() << "\n";
}

//-----------------NMedia----------------

NMedia::NMedia(unsigned int i, const QString & te, const QString & u, const QString & desc)
    : Note (i, te), url(u), description(desc)
{
}

void NMedia::log() const {
    qDebug() << "NMedia" << getId() << "\n";
}

}

