#include "Note.h"

namespace NM {

    //-----------------NOTE-------------------
    Note::Note(const unsigned int i, const QString &te)
        : id(i), title(te), loaded(false), modified(false)
    {
        //this->log();
    }

    void Note::log() const {}


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
        if (loaded == true)
            return;

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

        fd.close();

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
        modified = true;
        notes << n;
    }

    void Document::operator <<(Note *n) {
        addNote(n);
    }

    void Document::removeNote(Note *n) {
        modified = true;
        while(notes.removeOne(n))
            qDebug() << "note enlevee du document";
    }

    QString Document::toText () const {
        QString str;

        str = QString::number(id) + "\n"
                + "Document\n"
                + title + "\n\n";

        QListIterator<Note*> i(notes);
         while (i.hasNext()) {
             str += QString::number(i.next()->getId(), 10) + "\n";
         }

        return str;
    }

    void Document::load() {
        if (this->loaded) { return; }

        loaded = true;

        NotesManager& nm = NotesManager::getInstance();

        qDebug() <<nm.getWorkspace().path() + "/" + QString::number(id);

        QFile fd(nm.getWorkspace().path() + "/" + QString::number(id));
        if(!fd.open(QIODevice::ReadOnly))
            qDebug() << "échec lors de l'ouverture de fichier\n";
        fd.readLine(); //on passe l'id
        fd.readLine(); //on passe le type
        fd.readLine(); //on passe le titre
        fd.readLine(); //on passe le saut de ligne

        unsigned int idNote;
        qDebug() << "Attention chargememt des notes";

        while (!fd.atEnd()) {
            //----------récupérer le pointeur sur la bonne note
            QString idS = fd.readLine();
            idS.chop(1);
            idNote = idS.toUInt();
            qDebug() << "chargement de la note d'id : " << idNote << "\n";
            notes<<nm.getNote(idNote);
        }

        fd.close();
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

    void NMedia::load(){
        NotesManager & nm = NotesManager::getInstance();

        QFile fd(nm.getWorkspace().path() + "/" + QString::number(id));
        fd.open(QIODevice::ReadOnly);
        fd.readLine(); //on passe l'id
        fd.readLine(); //on passe le type
        fd.readLine(); //on passe le titre
        fd.readLine(); //on passe le saut de ligne

        url = fd.readLine();
        url.chop(1);

        while(!fd.atEnd()){
            description += fd.readLine();
        }

        loaded = true;
    }

    //-----------------NAudio----------------
    QString NAudio::toText() const{
        QString str = QString::number(id) + "\n";
        str += "NAudio\n";
        str += title + "\n\n";
        str += url + "\n";
        str += description;

        return str;
    }

    //-----------------NVideo----------------
    QString NVideo::toText() const{
        QString str = QString::number(id) + "\n";
        str += "NVideo\n";
        str += title + "\n\n";
        str += url + "\n";
        str += description + "\n";

        return str;
    }

    //-----------------NImage----------------
    QString NImage::toText() const{
        QString str = QString::number(id) + "\n";
        str += "NImage\n";
        str += title + "\n\n";
        str += url + "\n";
        str += description + "\n";

        return str;
    }
}

