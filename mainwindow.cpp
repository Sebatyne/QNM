#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "NotesManager.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->actionNewArticle->setIcon(QIcon(QPixmap(QString(":/icons/note-new.png"))));
    ui->actionNewDocument->setIcon(QIcon(QPixmap(QString(":/icons/folder-new.png"))));
    ui->actionNewVideo->setIcon(QIcon(QPixmap(QString(":/icons/video.png"))));
    ui->actionNewImage->setIcon(QIcon(QPixmap(QString(":/icons/image.png"))));
    ui->actionNewAudio->setIcon(QIcon(QPixmap(QString(":/icons/audio.png"))));
    ui->actionHTML->setIcon(QIcon(QPixmap(QString(":/icons/html.png"))));
    ui->actionTeX->setIcon(QIcon(QPixmap(QString(":/icons/pdf.png"))));
    ui->actionText->setIcon(QIcon(QPixmap(QString(":/icons/text.png"))));

    createListNotes();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createListNotes() {
    arborescence = new QStandardItemModel;
    parentItem = arborescence->invisibleRootItem();

    for(NM::NotesManager::Iterator i = NM::NotesManager::getInstance().begin();
            i != NM::NotesManager::getInstance().end(); i++) {
        if ((*i)->getType() == NM::Note::Document) {
            (*i)->load();
            parentItem->appendRow( getQNMStandardDocument(dynamic_cast<NM::Document*>(*i)) );
        }
        else {
            QNMStandardItem *item = new QNMStandardItem((*i)->getTitle());
            item->setEditable(false);
            item->setIcon(QIcon(QPixmap(QString("./icons/note.png"))));

            item->setId((*i)->getId());
            parentItem->appendRow(item);
        }
    }

    ui->tree->setModel(arborescence);
}

QStandardItem* MainWindow::getQNMStandardDocument(NM::Document *doc) {
    QNMStandardItem *item = new QNMStandardItem(doc->getTitle());
    item->setEditable(false);
    item->setIcon(QIcon(QPixmap(QString("./icons/folder.png"))));
    item->setId(doc->getId());

    for(NM::Document::Iterator i = doc->begin(); i != doc->end(); i++) {
        if ((*i)->getType() == NM::Note::Document) {
            item->appendRow( getQNMStandardDocument(dynamic_cast<NM::Document*>(*i)) );
        }
        else {
            QNMStandardItem *item2 = new QNMStandardItem((*i)->getTitle());
            item2->setEditable(false);
            item2->setId((*i)->getId());
            item->appendRow(item2);
        }
    }

    return item;
}
