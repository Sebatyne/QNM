#ifndef ARTICLEWIDGET_H
#define ARTICLEWIDGET_H

#include <QGroupBox>

namespace Ui {
class ArticleWidget;
}

class ArticleWidget : public QGroupBox
{
    Q_OBJECT
    
public:
    explicit ArticleWidget(QWidget *parent = 0);
    ~ArticleWidget();
    
private:
    Ui::ArticleWidget *ui;
};

#endif // ARTICLEWIDGET_H
