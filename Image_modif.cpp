#include "Image_modif.h"
#include "ui_Image_modif.h"

Image_modif::Image_modif(NM::Note *n, QWidget *parent) :
    QWidget(parent),
    note(dynamic_cast<NM::NImage*>(n)),
    ui(new Ui::Image_modif)
{
    ui->setupUi(this);

    note->load();
    ui->title_note->setText(note->getTitle());
    ui->url_line->setText(note->getUrl());

    ui->preview->show();

    connect(ui->save_button, SIGNAL(pressed()), this, SLOT(save_note()));
    connect(ui->find_button, SIGNAL(pressed()), this, SLOT(open_image()));

    ui->preview->setMinimumWidth(this->width()/2);

    if (!note->getUrl().isEmpty()) {
        pix = QPixmap(note->getUrl());
        showImage();
    }
    if (!note->getDescription().isEmpty()) {
        ui->description_line->clear();
        ui->description_line->insert(note->getDescription());
    }

}

Image_modif::~Image_modif()
{
    delete ui;
}

void Image_modif::save_note() {
    note->setUrl(ui->url_line->text());
    note->setTitle(ui->title_note->text());
    note->setDescription(ui->description_line->text());
    NM::NotesManager::getInstance().save(note);
}

void Image_modif::open_image() {
     ui->url_line->setText(QFileDialog::getOpenFileName(this,
         tr("Open Image"), "/home/~", tr("Image Files (*.png *.jpg *.bmp)")));
     showImage();
}

void Image_modif::showImage() {
    QPixmap pix2 = pix.scaled(ui->preview->height(), ui->preview->width(), Qt::KeepAspectRatioByExpanding, Qt::FastTransformation);
    ui->preview->setPixmap(pix2);
}
