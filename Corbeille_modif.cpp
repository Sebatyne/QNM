#include "Corbeille_modif.h"
#include "ui_Corbeille_modif.h"

Corbeille_modif::Corbeille_modif(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Corbeille_modif)
{
    ui->setupUi(this);
    createListNotes();

    connect(ui->restaurer_button,SIGNAL(pressed()), this, SLOT(restaure_note()));
}

Corbeille_modif::~Corbeille_modif()
{
    delete ui;
}

void Corbeille_modif::createListNotes() {
    ui->tree->clear();

    for(NM::NotesManager::Iterator i = NM::NotesManager::getInstance().corbeille_begin();
            i != NM::NotesManager::getInstance().corbeille_end(); i++) {
        QNMListWidgetItem *n = new QNMListWidgetItem((*i)->getTitle(), ui->tree);
        n->setId((*i)->getId());

        if ((*i)->getType() == NM::Note::Document)
            n->setIcon(QIcon(QPixmap(QString(":/icons/folder.png"))));
        else if ((*i)->getType() == NM::Note::NVideo)
            n->setIcon(QIcon(QPixmap(QString(":/icons/video.png"))));
        else if ((*i)->getType() == NM::Note::NAudio)
            n->setIcon(QIcon(QPixmap(QString(":/icons/audio.png"))));
        else if ((*i)->getType() == NM::Note::NImage)
            n->setIcon(QIcon(QPixmap(QString(":/icons/image.png"))));
        else
            n->setIcon(QIcon(QPixmap(QString(":/icons/note.png"))));
    }
}

void Corbeille_modif::restaure_note() {
    NM::Note *n = NM::NotesManager::getInstance().restoreNote(dynamic_cast<QNMListWidgetItem*>(ui->tree->currentItem())->getId());
    qDebug() << "Restaure la note d'id : " << n->getId();
    MainWindow::getInstance()->createListNotes();
    this->close();
}
