#pragma once

#include <QString>
#include <QMap>
#include <QDateTime>
#include "Note.h"

namespace NM {

    class Note;

    class NoteFactory
    {
        QString name;
    protected :
        NoteFactory(QString & n);
        unsigned int getNewId();
    public:
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
    protected:
        MediaFactory(QString &n);
    public :
        virtual Note * buildNote(const unsigned int id, const QString &title) = 0;
        virtual Note * buildNewNote(const QString &title) = 0;
    };

    class AudioFactory : public MediaFactory{
    public:
        AudioFactory(QString & n) : MediaFactory(n){}
        Note * buildNote(const unsigned int id, const QString &title);
        Note * buildNewNote(const QString &title);

    };

    class VideoFactory : public MediaFactory{
    public:
        VideoFactory(QString & n) : MediaFactory(n){}
        Note * buildNote(const unsigned int id, const QString &title);
        Note * buildNewNote(const QString &title);
    };

    class ImageFactory : public MediaFactory{
    public:
        ImageFactory(QString & n) : MediaFactory(n){}
        Note * buildNote(const unsigned int id, const QString &title);
        Note * buildNewNote(const QString &title);
    };

}
