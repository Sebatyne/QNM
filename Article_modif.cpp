#include "Article_modif.h"
#include "ui_Article_modif.h"

Article_modif::Article_modif(NM::Note *n, QWidget *parent) :
    QWidget(parent),
    note(dynamic_cast<NM::NArticle*>(n)),
    ui(new Ui::Article_modif)
{
    ui->setupUi(this);

    note->load();
    ui->title_note->setText(note->getTitle());
    ui->text_note->setText(note->getText());

    connect(ui->save_button, SIGNAL(pressed()), this, SLOT(save_note()));
}

Article_modif::~Article_modif()
{
    delete ui;
}

void Article_modif::save_note() {
    note->setText(ui->text_note->toPlainText());
    NM::NotesManager::getInstance().save(note);
}
