#ifndef IMAGE_MODIF_H
#define IMAGE_MODIF_H

#include <QWidget>
#include <QFileDialog>
#include <QVBoxLayout>
#include <QPixmap>
#include "Note.h"
#include "mainwindow.h"

namespace Ui {
class Image_modif;
}

class NMedia;

/**
 * \class Image_modif
 * \brief Widget de modification de note d'image
 *Widget évolué permettant de modifier les caractéristiques
 *d'une note de type image.
 *Il partage une classe mère, héritée par les classes filles,
 * qui permet s'affiche dans la zone centrale d'une fenêtre
 */


class Image_modif : public QWidget
{
    Q_OBJECT
    
public:
    explicit Image_modif(NM::Note* n, QWidget *parent = 0);
    ~Image_modif();
    
private slots :
    /**
     * \brief Enregistre la note actuellement éditée
     *Est appelé lors de l'appui sur le bouton d'enregistrement
    */
    void save_note();
    /**
     * \brief Afficheun dialog de navigation dans les fichiers pour choisir une image
    */
    void open_image();

private:
    NM::NImage *note;
    Ui::Image_modif *ui;
    QPixmap pix;

    void showImage();
};

#endif // IMAGE_MODIF_H
