#ifndef ARTICLE_MODIF_H
#define ARTICLE_MODIF_H

#include <QWidget>
#include "Note.h"

namespace Ui {
class Article_modif;
}

class Article_modif : public QWidget
{
    Q_OBJECT
    
public:
    explicit Article_modif(unsigned int id, QWidget *parent = 0);
    ~Article_modif();

private slots :
    void save_note();

private:
    Ui::Article_modif *ui;
    unsigned int note_id;
    NM::NArticle *note;
};

#endif // ARTICLE_MODIF_H
