#ifndef ARTICLE_MODIF_H
#define ARTICLE_MODIF_H

#include <QWidget>
#include "Note.h"
#include "mainwindow.h"

namespace Ui {
class Article_modif;
}

/**
 * \class Article_modif
 * \brief Widget de modification d'article
 *Widget évolué permettant de modifier les caractéristiques
 *d'une note de type article.
 *Il partage une classe mère, héritée par les classes filles,
 * qui permet s'affiche dans la zone centrale d'une fenêtre
 */

class Article_modif : public QWidget
{
    Q_OBJECT
    
public:
    /**
     * \brief Constructeur de la classe Article_modif
     * \param n : pointeur sur la note associée
     * \param parent : QWidget parent, laissé à 0.
     */
    explicit Article_modif(NM::Note* n, QWidget *parent = 0);
    ~Article_modif();

private slots :
    /**
     * \brief Enregistre la note actuellement éditée
     *Est appelé lors de l'appui sur le bouton d'enregistrement
    */
    void save_note();
    void delete_note();

private:
    NM::NArticle *note;
    Ui::Article_modif *ui;
};

#endif // ARTICLE_MODIF_H
