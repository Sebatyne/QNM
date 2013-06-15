#ifndef AUDIO_MODIF_H
#define AUDIO_MODIF_H

#include <QWidget>
#include <QFileDialog>
#include "Note.h"
#include "mainwindow.h"

namespace Ui {
class Audio_modif;
}

/**
 * \class Audio_modif
 * \brief Widget de modification de note audio.
 *Widget évolué permettant de modifier les caractéristiques
 *d'une note de type audio.
 *Il partage une classe mère, héritée par les classes filles,
 * qui permet s'affiche dans la zone centrale d'une fenêtre
 */


class Audio_modif : public QWidget
{
    Q_OBJECT
    
public:
    explicit Audio_modif(NM::Note *n, QWidget *parent = 0);
    ~Audio_modif();

private slots :
    /**
     * \brief Enregistre la note actuellement éditée
     *Est appelé lors de l'appui sur le bouton d'enregistrement
    */
    void save_note();
    void delete_note();

private:
    NM::NAudio *note;
    Ui::Audio_modif *ui;
};

#endif // AUDIO_MODIF_H
