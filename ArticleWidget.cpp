#include "ArticleWidget.h"
#include "ui_ArticleWidget.h"

ArticleWidget::ArticleWidget(QWidget *parent) :
    QGroupBox(parent),
    ui(new Ui::ArticleWidget)
{
    ui->setupUi(this);
}

ArticleWidget::~ArticleWidget()
{
    delete ui;
}
