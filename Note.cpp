#include "Note.h"

namespace NM {


//-----------------NOTE-------------------
Note::Note(const unsigned int i, const QString &te)
    : id(i), title(te), loaded(true), modified(false)
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

void NArticle::log() const {
    qDebug() << "Article : " << getId() << "\n";
    //std::cout<< "Article :" << getId() << std::endl;
}


//-----------------Document----------------
Document::Document(unsigned int i, const QString &te)
    : Note(i, te) {}

void Document::addNote(Note *n) {
    notes << n;
}

void Document::operator <<(Note *n) {
    notes << n;
}

void Document::removeNote(Note *n) {
    notes.removeOne(n);
}

void Document::log() const {
    qDebug() << "Document" << getId() << "\n";
}


}
