#include "Document_modif.h"
#include "ui_Document_modif.h"

Document_modif::Document_modif(NM::Note *n, QWidget *parent) :
    note(dynamic_cast<NM::Document*>(n)),
    QWidget(parent),
    ui(new Ui::Document_modif)
{
    ui->setupUi(this);
    note->load();

    temp_note = new NM::Document(0);

    //chargement des notes temporairement dans notes_temp
    for(NM::Document::Iterator it = note->begin(); it != note->end(); it++) {
        temp_note->addNote(*it);
    }

    ui->title_note->setText(note->getTitle());

    init_contained_notes();
    init_other_notes();

    connect(ui->add_button, SIGNAL(pressed()), this, SLOT(addNoteToDoc()));
    connect(ui->remove_button, SIGNAL(pressed()), this, SLOT(removeNoteFromDoc()));
    connect(ui->save_button, SIGNAL(pressed()), this, SLOT(save_note()));
    connect(ui->contained_notes, SIGNAL(itemDoubleClicked(QListWidgetItem*)), SLOT(removeNoteFromDoc()));
    connect(ui->other_notes, SIGNAL(itemDoubleClicked(QListWidgetItem*)), SLOT(addNoteToDoc()));
    connect(ui->save_button, SIGNAL(pressed()), MainWindow::getInstance(), SLOT(createListNotes()));
    connect(ui->save_button, SIGNAL(pressed()), MainWindow::getInstance(), SLOT(saveWork()));
}

Document_modif::~Document_modif()
{
    delete ui;
}

void Document_modif::save_note() {
    note->clear();
    for (NM::Document::Iterator i = temp_note->begin(); i != temp_note->end(); i++) {
        note->addNote(*i);
    }
    note->setTitle(ui->title_note->text());
    NM::NotesManager::getInstance().save(note);
}

void Document_modif::init_contained_notes() {
    ui->contained_notes->clear();

    for(NM::Document::Iterator i = temp_note->begin(); i != temp_note->end(); i++) {
        QNMListWidgetItem *n = new QNMListWidgetItem((*i)->getTitle(), ui->contained_notes);
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

void Document_modif::init_other_notes() {
    ui->other_notes->clear();
    QSet<NM::Note*> all_notes;
    QSet<NM::Note*> this_notes;

    all_notes = NM::NotesManager::getInstance().returnSetNotes();

    for(NM::Document::Iterator it = temp_note->begin(); it != temp_note->end(); it++) {
        this_notes << (*it);
    }

    this_notes = all_notes - this_notes;
    this_notes -= note;

    for(QSet<NM::Note*>::Iterator i = this_notes.begin(); i != this_notes.end(); i++) {
        QNMListWidgetItem *n = new QNMListWidgetItem((*i)->getTitle(), ui->other_notes);
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

void Document_modif::addNoteToDoc() {
    if (!ui->other_notes->currentItem()) {
        return;
    }
    QNMListWidgetItem *wi = dynamic_cast<QNMListWidgetItem*>(ui->other_notes->currentItem());
    temp_note->addNote(NM::NotesManager::getInstance().getNote(wi->getId()));
    qDebug() << "ajout au document de la note d'id : " << wi->getId();
    init_contained_notes();
    init_other_notes();
    //note->setModified();
}

void Document_modif::removeNoteFromDoc() {
    if (!ui->contained_notes->currentItem()) {
        return;
    }
    QNMListWidgetItem *wi = dynamic_cast<QNMListWidgetItem*>(ui->contained_notes->currentItem());
    temp_note->removeNote(NM::NotesManager::getInstance().getNote(wi->getId()));
    init_contained_notes();
    init_other_notes();
    //note->setModified();
}
