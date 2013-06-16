#ifndef VIDEO_MODIF_H
#define VIDEO_MODIF_H

#include <QWidget>
#include <QFileDialog>
#include "Note.h"
#include "mainwindow.h"

namespace Ui {
class Video_modif;
}

/**
 * \class Video_modif
 * \brief Widget de modification de note video.
 *Widget évolué permettant de modifier les caractéristiques
 *d'une note de type video.
 *Il partage une classe mère, héritée par les classes filles,
 * qui permet s'affiche dans la zone centrale d'une fenêtre
 */
class Video_modif : public QWidget
{
    Q_OBJECT
    
public:
    explicit Video_modif(NM::Note *n, QWidget *parent = 0);
    ~Video_modif();
    
private slots :
    /**
     * \brief Enregistre la note actuellement éditée
     *Est appelé lors de l'appui sur le bouton d'enregistrement
    */
    void save_note();
    void delete_note();
    void open_note();

private:
    NM::NVideo *note;
    Ui::Video_modif *ui;
};

#endif // VIDEO_MODIF_H
