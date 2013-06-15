#ifndef VIDEO_MODIF_H
#define VIDEO_MODIF_H

#include <QWidget>
#include <QFileDialog>
#include "Note.h"
#include "mainwindow.h"

namespace Ui {
class Video_modif;
}

class Video_modif : public QWidget
{
    Q_OBJECT
    
public:
    explicit Video_modif(NM::Note *n, QWidget *parent = 0);
    ~Video_modif();
    
private slots :
    void save_note();

private:
    NM::NVideo *note;
    Ui::Video_modif *ui;

    void open_video();
};

#endif // VIDEO_MODIF_H
