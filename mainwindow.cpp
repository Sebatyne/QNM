#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "NotesManager.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    //items.append(new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString("item: %1").arg(i))));

}

MainWindow::~MainWindow()
{
    delete ui;
}
