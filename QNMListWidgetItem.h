#ifndef QNMLISTWIDGETITEM_H
#define QNMLISTWIDGETITEM_H

#include <QListWidgetItem>

class QNMListWidgetItem : public QListWidgetItem {
public :
    QNMListWidgetItem (const QString & text, QListWidget *parent = 0, int type = Type) : QListWidgetItem(text, parent, type) {}
    void setId(unsigned int i) {id = i;}
    unsigned int getId () const {return id;}
private :
    unsigned int id;
};

#endif // QNMLISTWIDGETITEM_H

