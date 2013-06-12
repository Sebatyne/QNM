#include "Article_modif.h"
#include "ui_Article_modif.h"

Article_modif::Article_modif(unsigned int id, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Article_modif)
{
    ui->setupUi(this);

    note = dynamic_cast<NM::NArticle*>(NM::NotesManager::getInstance().getNote(id));
    note->load();
    ui->title_note->setText(note->getTitle());
    ui->text_note->setText(note->getText());

    connect(ui->save_button, SIGNAL(clicked()), this, SLOT(save_note()));
}

Article_modif::~Article_modif()
{
    delete ui;
}

void Article_modif::save_note() {
    note->setText(ui->text_note->toPlainText());
    NM::NotesManager::getInstance().save(note);
}
