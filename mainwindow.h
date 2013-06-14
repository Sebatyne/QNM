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
#include <QVBoxLayout>
#include <QWidget>
#include "NotesManager.h"
#include "QNMListWidgetItem.h"
#include "Article_modif.h"
#include "Document_modif.h"
#include "Image_modif.h"

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
    void createListNotes();
    
private:
    Ui::MainWindow *ui;
    QStandardItemModel *arborescence;
    QStandardItem *parentItem;

    //QStandardItem* getQNMStandardDocument(NM::Document *doc);

};



#endif // MAINWINDOW_H
