#ifndef QNMLISTWIDGETITEM_H
#define QNMLISTWIDGETITEM_H

#include <QListWidgetItem>

/**
 * \class QNMListWidgetItem
 * \
 * \brief Classe représentant une note dans l'affichage.
 *Hérite d'un QListWidgetItem, mais comporte l'id de la note représentée en plus
 */
class QNMListWidgetItem : public QListWidgetItem {
public :
    QNMListWidgetItem (const QString & text, QListWidget *parent = 0, int type = Type) : QListWidgetItem(text, parent, type) {}
    void setId(unsigned int i) {id = i;}
    unsigned int getId () const {return id;}
private :
    unsigned int id;
};

#endif // QNMLISTWIDGETITEM_H

