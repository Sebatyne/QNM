#ifndef DOCUMENT_MODIF_H
#define DOCUMENT_MODIF_H

#include <QWidget>
#include <QIcon>
#include <QPixmap>
#include <QSet>
#include <QList>
#include "Note.h"
#include "QNMListWidgetItem.h"
#include "mainwindow.h"

class Note;

namespace Ui {
class Document_modif;
}

class Document_modif : public QWidget
{
    Q_OBJECT
    
public:
    explicit Document_modif(NM::Note* n, QWidget *parent = 0);
    ~Document_modif();
    
private slots :
    void save_note();
    void addNoteToDoc();
    void removeNoteFromDoc();

private:
    NM::Document *note;
    NM::Document *temp_note;
    Ui::Document_modif *ui;  

    void init_contained_notes();
    void init_other_notes();
};

#endif // DOCUMENT_MODIF_H
