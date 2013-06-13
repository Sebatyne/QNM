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
    explicit Article_modif(NM::Note* n, QWidget *parent = 0);
    ~Article_modif();

private slots :
    void save_note();

private:
    NM::NArticle *note;
    Ui::Article_modif *ui;
};

#endif // ARTICLE_MODIF_H
