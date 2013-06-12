#pragma once

#include <QList>
#include <QDateTime>
#include <QMap>

#include "Note.h"
#include "NUtils.h"

namespace NM{
    class NotesExporter
    {
    protected:
        Note * ExportedNote;
        NotesExporter(Note * ExportedNote) : ExportedNote(ExportedNote){}
        bool delimitParts;
        bool displayDate;

        void setDisplayDate(bool DisplayDate){displayDate = DisplayDate;}
        void setDelimitParts(bool DelimitParts){delimitParts = DelimitParts;}

    public:
        virtual QString getRawExport() = 0;

        void setExportedNote(Note * ExportedNote);
    };

    class textNotesExporter : NotesExporter{
        QString NoteToText(Note * convertedNote, unsigned int TitleLevel);
        QString ArticleToText(NArticle * ConvertedArticle, unsigned int titleLevel);
        QString ImageToText(NImage * ConvertedImage, unsigned int titleLevel);
        QString AudioToText(NAudio * ConvertedAudio, unsigned int titleLevel);
        QString VideoToText(NVideo * ConvertedVideo, unsigned int titleLevel);
        QString MediaToText(NMedia * NoteMedia, unsigned int titleLevel);
    public:
        textNotesExporter(Note * ExportedNote) : NotesExporter(ExportedNote){
            delimitParts = true;
            displayDate = false;
        }
        QString getRawExport();
    };

    class HTMLNotesExporter : NotesExporter{
        QString spreadSheet;
    public:
        HTMLNotesExporter(Note * ExportedNote) : NotesExporter(ExportedNote){

        }

        void setSpreadSheet(QString & css);
        QString getSpreadSheet(){return spreadSheet;}

        QString getRawExport();

    };

    class LaTexNotesExporter : NotesExporter{
    public:
        enum latexDocType{book, article, report};

        LaTexNotesExporter(Note * ExportedNote) : NotesExporter(ExportedNote){
            ignoreAudio = false;
            ignoreVideo = false;
            ignoreNumbering = true;
            delimitParts = true;
            displayDate = false;
            docType = article;

            titleSize.insert(1, "part");
            titleSize.insert(2, "section");
            titleSize.insert(3, "subsection");
            titleSize.insert(4, "subsubsection");
        }

        void setDocType(latexDocType docType);
        latexDocType getDocType() const {return docType;}

        void setIgnoreAudio(bool IgnoreAudio){ignoreAudio = IgnoreAudio;}
        void setIgnoreVideo(bool IgnoreVideo){ignoreVideo = IgnoreVideo;}
        void setIgnoreNumerotation(bool IgnoreNumbering){ignoreNumbering = IgnoreNumbering;}

        QString getRawExport();
    private:
        latexDocType docType;
        bool ignoreAudio;
        bool ignoreVideo;
        bool ignoreNumbering;

        QMap <int, QString> titleSize;

        QString NoteToLatex(Note * ConvertedNote, unsigned int titleLevel);
        QString ArticleToLatex(NArticle * ConvertedArticle, unsigned int titleLevel);
        QString ImageToLatex(NImage * ConvertedImage, unsigned int titleLevel);
        QString AudioToLatex(NAudio * ConvertedAudio, unsigned int titleLevel);
        QString VideoToLatex(NVideo * ConvertedVideo, unsigned int titleLevel);
        QString MediaToLatex(NMedia * NoteMedia, unsigned int titleLevel);
    };
}
