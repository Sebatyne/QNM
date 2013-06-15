#include "Video_modif.h"
#include "ui_Video_modif.h"

Video_modif::Video_modif(NM::Note *n, QWidget *parent) :
    QWidget(parent),
    note(dynamic_cast<NM::NVideo*>(n)),
    ui(new Ui::Video_modif)
{
    ui->setupUi(this);
    note->load();
    ui->title_note->setText(note->getTitle());
    ui->url_line->setText(note->getUrl());
    ui->description_line->clear();
    ui->description_line->setText(note->getDescription().trimmed());

    connect(ui->save_button, SIGNAL(pressed()), this, SLOT(save_note()));
    connect(ui->save_button, SIGNAL(pressed()), MainWindow::getInstance(), SLOT(createListNotes()));
    connect(ui->save_button, SIGNAL(pressed()), MainWindow::getInstance(), SLOT(saveWork()));
    connect(ui->delete_button, SIGNAL(pressed()), this, SLOT(delete_note()));
    connect(ui->delete_button, SIGNAL(pressed()), MainWindow::getInstance(), SLOT(createListNotes()));
}

Video_modif::~Video_modif()
{
    delete ui;
}

void Video_modif::save_note() {
    note->setUrl(ui->url_line->text());
    note->setTitle(ui->title_note->text());
    note->setDescription(ui->description_line->text());
    NM::NotesManager::getInstance().save(note);
}

void Video_modif::delete_note() {
    NM::NotesManager::getInstance().deleteNote(note);
    NM::NotesManager::getInstance().saveWorkspace();
    this->hide();
}
