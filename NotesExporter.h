#pragma once

#include <QList>
#include "Note.h"

namespace NM{
    class NotesExporter
    {
        NotesExporter();
        virtual ~NotesExporter() = 0;
        QSet<const Note*> ExportedNotes;
    public:
        virtual void Export() = 0;
        virtual QString & getRawExport() = 0;

        void insert(const Note *);
        void operator<<(const Note*);

        void remove(const Note *);
    };

    class textNotesExporter : NotesExporter{
    public:
        textNotesExporter();
        void Export();
        QString & getRawExport();
    };

    class HTMLNotesExporter : NotesExporter{
        QString spreadSheet;
    public:
        HTMLNotesExporter();

        void setCustomSpreadSheet(QString & css);

        void Export();
        QString & getRawExport();

    };

    class LaTexNotesExporter : NotesExporter{
    public:
        LaTexNotesExporter();

        void Export();
        QString & getRawExport();
    };
}
