#pragma once

#include <QList>
#include <QDateTime>
#include <QMap>

#include "Note.h"

namespace NM{
    class NotesExporter
    {
    protected:
        Note * ExportedNote;
        NotesExporter(Note * ExportedNote) : ExportedNote(ExportedNote){}
    public:
        virtual QString getRawExport() = 0;

        void setExportedNote(Note * ExportedNote);
    };

    class textNotesExporter : NotesExporter{
    public:
        textNotesExporter(Note * ExportedNote) : NotesExporter(ExportedNote){}
        QString getRawExport();
    };

    class HTMLNotesExporter : NotesExporter{
        QString spreadSheet;
    public:
        HTMLNotesExporter(Note * ExportedNote) : NotesExporter(ExportedNote){}

        void setSpreadSheet(QString & css);
        QString getSpreadSheet(){return spreadSheet;}

        QString getRawExport();

    };

    class LaTexNotesExporter : NotesExporter{
    public:
        enum latexDocType{book, article, report};

        LaTexNotesExporter(Note * ExportedNote) : NotesExporter(ExportedNote){
            ignoreAudio = true;
            ignoreVideo = true;
            ignoreNumbering = false;
            delimitParts = false;
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
        void setDisplayDate(bool DisplayDate){displayDate = DisplayDate;}
        void setIgnoreNumerotation(bool IgnoreNumbering){ignoreNumbering = IgnoreNumbering;}
        void setDelimitParts(bool DelimitParts){delimitParts = DelimitParts;}

        QString getRawExport();
    private:
        latexDocType docType;
        bool ignoreAudio;
        bool ignoreVideo;
        bool displayDate;
        bool ignoreNumbering;
        bool delimitParts;

        QMap <int, QString> titleSize;

        QString NoteToLatex(Note * ConvertedNote, unsigned int titleLevel);
        QString ArticleToLatex(NArticle * ConvertedArticle, unsigned int titleLevel);
        QString ImageToLatex(NImage * ConvertedImage, unsigned int titleLevel);
    };
}
