#ifndef AUDIO_MODIF_H
#define AUDIO_MODIF_H

#include <QWidget>
#include <QFileDialog>
#include "Note.h"
#include "mainwindow.h"

namespace Ui {
class Audio_modif;
}

class Audio_modif : public QWidget
{
    Q_OBJECT
    
public:
    explicit Audio_modif(NM::Note *n, QWidget *parent = 0);
    ~Audio_modif();

private slots :
    void save_note();

private:
    NM::NAudio *note;
    Ui::Audio_modif *ui;
};

#endif // AUDIO_MODIF_H
