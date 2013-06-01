#include "notesExporter.h"

namespace NM{
    void NotesExporter::insert(const Note * N){
        if(N && !ExportedNotes.contains(N)){
            ExportedNotes.insert(N);
        }
    }

    void NotesExporter::operator <<(const Note * N){
        this->insert(N);
    }
}
