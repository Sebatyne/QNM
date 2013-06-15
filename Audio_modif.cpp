#include "Audio_modif.h"
#include "ui_Audio_modif.h"

Audio_modif::Audio_modif(NM::Note *n, QWidget *parent) :
    QWidget(parent),
    note(dynamic_cast<NM::NAudio*>(n)),
    ui(new Ui::Audio_modif)
{
    ui->setupUi(this);
    note->load();
    ui->title_note->setText(note->getTitle());
    ui->url_line->setText(note->getUrl());
    ui->description_line->clear();
    ui->description_line->setText(note->getDescription().trimmed());

    connect(ui->save_button, SIGNAL(pressed()), this, SLOT(save_note()));
    connect(ui->save_button, SIGNAL(pressed()), MainWindow::getInstance(), SLOT(createListNotes()));
}

Audio_modif::~Audio_modif()
{
    delete ui;
}

void Audio_modif::save_note() {
    note->setUrl(ui->url_line->text());
    note->setTitle(ui->title_note->text());
    note->setDescription(ui->description_line->text());
    NM::NotesManager::getInstance().save(note);
}
