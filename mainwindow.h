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
#include <QInputDialog>
#include <QListWidgetItem>
#include <QVBoxLayout>
#include "NotesManager.h"
#include "Article_modif.h"


namespace Ui {
class MainWindow;
}

class QNMListWidgetItem;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots :
    void saveWork();
    void dialogNewArticle();
    void dialogNewImage();
    void dialogNewVideo();
    void dialogNewAudio();
    void dialogNewDocument();
    QString dialogNewNote();
    void viewItem(QListWidgetItem *wi);
    
private:
    Ui::MainWindow *ui;
    QStandardItemModel *arborescence;
    QStandardItem *parentItem;

    void createListNotes();
    //QStandardItem* getQNMStandardDocument(NM::Document *doc);

};

class QNMListWidgetItem : public QListWidgetItem {
public :
    QNMListWidgetItem (const QString & text, QListWidget *parent = 0, int type = Type) : QListWidgetItem(text, parent, type) {}
    void setId(unsigned int i) {id = i;}
    unsigned int getId () const {return id;}
private :
    unsigned int id;
};

#endif // MAINWINDOW_H
