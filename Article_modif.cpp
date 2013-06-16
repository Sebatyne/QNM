#include "Article_modif.h"
#include "ui_Article_modif.h"

Article_modif::Article_modif(NM::Note *n, QWidget *parent) :
    QWidget(parent),
    note(dynamic_cast<NM::NArticle*>(n)),
    ui(new Ui::Article_modif)
{
    ui->setupUi(this);

    ui->text_note->setAcceptRichText(false);

    note->load();
    ui->title_note->setText(note->getTitle());
    ui->text_note->setText(note->getText());

    connect(ui->save_button, SIGNAL(pressed()), this, SLOT(save_note()));
    connect(ui->save_button, SIGNAL(pressed()), MainWindow::getInstance(), SLOT(saveWork()));
    connect(ui->save_button, SIGNAL(pressed()), MainWindow::getInstance(), SLOT(createListNotes()));
    connect(ui->delete_button, SIGNAL(pressed()), this, SLOT(delete_note()));
    connect(ui->delete_button, SIGNAL(pressed()), MainWindow::getInstance(), SLOT(createListNotes()));
}

Article_modif::~Article_modif()
{
    delete ui;
}

void Article_modif::save_note() {
    note->setTitle(ui->title_note->text());
    note->setText(ui->text_note->toPlainText());
    NM::NotesManager::getInstance().save(note);
}

void Article_modif::delete_note() {
    NM::NotesManager::getInstance().deleteNote(note);
    NM::NotesManager::getInstance().saveWorkspace();
    this->hide();
}
