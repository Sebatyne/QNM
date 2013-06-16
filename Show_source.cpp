#include "Show_source.h"
#include "ui_Show_source.h"

Show_source::Show_source(const QString s, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Show_source)
{
    ui->setupUi(this);
    ui->text_source->setPlainText(s);
    ui->text_source->setReadOnly(true);

    connect(ui->ok_button, SIGNAL(pressed()), this, SLOT(close()));
    connect(ui->toClipboard_button, SIGNAL(pressed()), this, SLOT(toClipboard()));
}

Show_source::~Show_source()
{
    delete ui;
}

void Show_source::toClipboard() {
    QClipboard *cl = QApplication::clipboard();
    cl->setText(ui->text_source->toPlainText());
    this->close();
}
