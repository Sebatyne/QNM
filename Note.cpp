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

QString  NArticle::toText () const {
    QString str;

    str = QString::number(id) + "\n";
    str += "NArticle\n";
    str += title + "\n\n";
    str += text;

    return str;
}

void NArticle::load() {
    NotesManager& nm = NotesManager::getInstance();

    QFile fd(nm.getWorkspace().path() + "/" + QString::number(id));
    fd.open(QIODevice::ReadOnly);
    fd.readLine(); //on passe l'id
    fd.readLine(); //on passe le type
    fd.readLine(); //on passe le titre
    fd.readLine(); //on passe le saut de ligne

    while (!fd.atEnd()) {
        text += fd.readLine();
    }

    loaded = true;
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

void Document::load() {
    NotesManager& nm = NotesManager::getInstance();

    QFile fd(nm.getWorkspace().path() + "/" + QString::number(id));
    fd.open(QIODevice::ReadOnly);
    fd.readLine(); //on passe l'id
    fd.readLine(); //on passe le type
    fd.readLine(); //on passe le titre
    fd.readLine(); //on passe le saut de ligne

    unsigned int idNote;

    while (!fd.atEnd()) {
        //----------récupérer le pointeur sur la bonne note
        idNote = fd.readLine().toUInt();
        notes<<nm.getNote(idNote);
    }

    loaded = true;
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

