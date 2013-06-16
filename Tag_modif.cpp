#include "Tag_modif.h"
#include "ui_Tag_modif.h"

Tag_modif::Tag_modif(NM::Note *n, QWidget *parent) :
    note(n),
    QDialog(parent),
    ui(new Ui::Tag_modif)
{
    ui->setupUi(this);
    ui->label_name->setText(n->getTitle());
    create_listTags();

    connect(ui->button_addTag, SIGNAL(pressed()), this, SLOT(create_tag()));
    connect(ui->save_button, SIGNAL(pressed()), this, SLOT(saveAndQuit()));
}

Tag_modif::~Tag_modif()
{
    delete ui;
}

void Tag_modif::create_listTags() {
    if(ui->group_tags->layout()) {
        QLayoutItem *child;
        while( (child = ui->group_tags->layout()->takeAt(0)) )  {
            ui->group_tags->layout()->removeItem( child );
            delete child->widget();
            delete child;
         }
    } else {
        QVBoxLayout *lay = new QVBoxLayout();
        ui->group_tags->setLayout(lay);
    }

    NM::TagManager::Iterator it = NM::TagManager::getInstance()->getIterator();

    while (it.hasNext()) {
        it.next();
        QCheckBox *cb = new QCheckBox(it.getTagLabel());
        if (NM::TagManager::getInstance()->isLinked(it.getTagLabel(), note))
            cb->setChecked(true);
        ui->group_tags->layout()->addWidget(cb);
    }
}

void Tag_modif::create_tag() {
    if(!ui->line_newTag->text().isEmpty())
        NM::TagManager::getInstance()->addTag(ui->line_newTag->text());
    ui->line_newTag->clear();

    create_listTags();
}

void Tag_modif::saveAndQuit() {
    NM::TagManager *tm = NM::TagManager::getInstance();
    QLayoutItem *child;
    while( (child = ui->group_tags->layout()->takeAt(0)) )  {
        QCheckBox *ch = dynamic_cast<QCheckBox*>(child->widget());
        if (ch->isChecked()) {
            tm->addLink(ch->text(), note);
        } else {
            tm->removeLink(ch->text(), note);
        }
    }

    this->close();
}
