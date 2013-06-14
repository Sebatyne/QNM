#ifndef IMAGE_MODIF_H
#define IMAGE_MODIF_H

#include <QWidget>
#include <QFileDialog>
#include <QVBoxLayout>
#include <QPixmap>
#include "Note.h"

namespace Ui {
class Image_modif;
}

class NMedia;

class Image_modif : public QWidget
{
    Q_OBJECT
    
public:
    explicit Image_modif(NM::Note* n, QWidget *parent = 0);
    ~Image_modif();
    
private slots :
    void save_note();
    void open_image();

private:
    NM::NImage *note;
    Ui::Image_modif *ui;
    QPixmap pix;

    void showImage();
};

#endif // IMAGE_MODIF_H
