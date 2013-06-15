#ifndef CORBEILLE_MODIF_H
#define CORBEILLE_MODIF_H

#include <QDialog>
#include "NotesManager.h"
#include "Note.h"
#include "QNMListWidgetItem.h"
#include "mainwindow.h"

namespace Ui {
class Corbeille_modif;
}

class Corbeille_modif : public QDialog
{
    Q_OBJECT
    
public:
    explicit Corbeille_modif(QWidget *parent = 0);
    ~Corbeille_modif();
    
private slots :
    void restaure_note();

private:
    Ui::Corbeille_modif *ui;

    void createListNotes();
};

#endif // CORBEILLE_MODIF_H
