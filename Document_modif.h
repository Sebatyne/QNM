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

/**
 * \class Document_modif
 * \brief Widget de modification d'un document
 *Widget évolué permettant de modifier les caractéristiques
 *d'une note de type document.
 *Il partage une classe mère, héritée par les classes filles,
 * qui permet s'affiche dans la zone centrale d'une fenêtre
 */


class Document_modif : public QWidget
{
    Q_OBJECT
    
public:
    explicit Document_modif(NM::Note* n, QWidget *parent = 0);
    ~Document_modif();
    
private slots :
    /**
     * \brief Enregistre la note actuellement éditée
     *Est appelé lors de l'appui sur le bouton d'enregistrement
    */
    void save_note();
    void delete_note();
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
