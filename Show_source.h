#ifndef SHOW_SOURCE_H
#define SHOW_SOURCE_H

#include <QDialog>
#include <QClipboard>

namespace Ui {
class Show_source;
}

/**
 * \class Show_source
 * \brief Dialog affichant la source d'une note suite à un export
 */
class Show_source : public QDialog
{
    Q_OBJECT
    
public:
    explicit Show_source(const QString s, QWidget *parent = 0);
    ~Show_source();

private slots :
    void toClipboard();
    
private:
    Ui::Show_source *ui;
};

#endif // SHOW_SOURCE_H
