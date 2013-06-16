#ifndef TAG_MODIF_H
#define TAG_MODIF_H

#include <QDialog>
#include <QVBoxLayout>
#include <QCheckBox>
#include "Tag.h"
#include "TagManager.h"
#include "Note.h"

namespace Ui {
class Tag_modif;
}

class Tag_modif : public QDialog
{
    Q_OBJECT
    
public:
    explicit Tag_modif(NM::Note *n, QWidget *parent = 0);
    ~Tag_modif();
    
private slots :
    void create_tag();
    void saveAndQuit();

private:
    NM::Note *note;
    Ui::Tag_modif *ui;

    void create_listTags();
};

#endif // TAG_MODIF_H
