#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidget>
#include <QList>
#include <QTreeWidgetItem>
#include <QStringList>
#include <QList>
#include <QString>
#include <QStandardItemModel>
#include <QStandardItem>
#include "NotesManager.h"


namespace Ui {
class MainWindow;
}

class QNMStandardItem;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;
    QStandardItemModel *arborescence;
    QStandardItem *parentItem;

    void createListNotes();
    QStandardItem* getQNMStandardDocument(NM::Document *doc);

};

class QNMStandardItem : public QStandardItem {
public :
    QNMStandardItem() : QStandardItem() {}
    QNMStandardItem(const QString & text) : QStandardItem (text) {}
    QNMStandardItem(const QIcon & icon, const QString & text) : QStandardItem (icon,text ) {}
    QNMStandardItem(int rows, int columns = 1) : QStandardItem (rows,columns) {}

    void setId(unsigned int i) {id = i;}
    unsigned int getId () const {return id;}
private :
    unsigned int id;
};

#endif // MAINWINDOW_H
