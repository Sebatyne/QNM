#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->actionNewArticle->setIcon(QIcon(QPixmap(QString(":/icons/note-new.png"))));
    ui->actionNewDocument->setIcon(QIcon(QPixmap(QString(":/icons/folder-new.png"))));
    ui->actionNewVideo->setIcon(QIcon(QPixmap(QString(":/icons/video.png"))));
    ui->actionNewImage->setIcon(QIcon(QPixmap(QString(":/icons/image.png"))));
    ui->actionNewAudio->setIcon(QIcon(QPixmap(QString(":/icons/audio.png"))));
    ui->actionHTML->setIcon(QIcon(QPixmap(QString(":/icons/html.png"))));
    ui->actionTeX->setIcon(QIcon(QPixmap(QString(":/icons/pdf.png"))));
    ui->actionText->setIcon(QIcon(QPixmap(QString(":/icons/text.png"))));

    createListNotes();

    connect(ui->actionNewArticle,SIGNAL(triggered()), this, SLOT(dialogNewArticle()));
    connect(ui->actionNewDocument,SIGNAL(triggered()), this, SLOT(dialogNewDocument()));
    connect(ui->actionNewVideo,SIGNAL(triggered()), this, SLOT(dialogNewVideo()));
    connect(ui->actionNewImage,SIGNAL(triggered()), this, SLOT(dialogNewImage()));
    connect(ui->actionNewAudio,SIGNAL(triggered()), this, SLOT(dialogNewAudio()));

    connect(ui->tree, SIGNAL(itemActivated(QListWidgetItem*)), this, SLOT(viewItem(QListWidgetItem*)));
    connect(ui->tree, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(viewItem(QListWidgetItem*)));
}

MainWindow::~MainWindow()
{
    delete ui;
    NM::NotesManager::releaseInstance();
}

void MainWindow::saveWork() {
    NM::NotesManager::getInstance().saveWorkspace();
    //NM::NotesManager::releaseInstance();
}

void MainWindow::createListNotes() {
    ui->tree->clear();

    for(NM::NotesManager::Iterator i = NM::NotesManager::getInstance().begin();
            i != NM::NotesManager::getInstance().end(); i++) {
        QNMListWidgetItem *n = new QNMListWidgetItem((*i)->getTitle(), ui->tree);
        n->setId((*i)->getId());

        if ((*i)->getType() == NM::Note::Document)
            n->setIcon(QIcon(QPixmap(QString(":/icons/folder.png"))));
        else if ((*i)->getType() == NM::Note::NVideo)
            n->setIcon(QIcon(QPixmap(QString(":/icons/video.png"))));
        else if ((*i)->getType() == NM::Note::NAudio)
            n->setIcon(QIcon(QPixmap(QString(":/icons/audio.png"))));
        else if ((*i)->getType() == NM::Note::NImage)
            n->setIcon(QIcon(QPixmap(QString(":/icons/image.png"))));
        else
            n->setIcon(QIcon(QPixmap(QString(":/icons/note.png"))));
    }
}

QString MainWindow::dialogNewNote() {
    bool ok = false;
    QString name = QInputDialog::getText(this, "Nouvelle Note", "Titre de la note :", QLineEdit::Normal, QString(), &ok);
    if (ok && !name.isEmpty())
        return name;
    else
        return QString();
}

void MainWindow::dialogNewArticle() {
    QString name = dialogNewNote();
    if (!name.isEmpty()) {
        NM::Note &n = NM::NotesManager::getInstance().getNewNArticle();
        n.setTitle(name);
        n.setModified();
        saveWork();
        createListNotes();
    }
}
void MainWindow::dialogNewImage() {
    QString name = dialogNewNote();
    if (!name.isEmpty()) {
        NM::Note &n = NM::NotesManager::getInstance().getNewNImage();
        n.setTitle(name);
        n.setModified();
        saveWork();
        createListNotes();
    }
}

void MainWindow::dialogNewVideo() {
    QString name = dialogNewNote();
    if (!name.isEmpty()) {
        NM::Note &n = NM::NotesManager::getInstance().getNewNVideo();
        n.setTitle(name);
        n.setModified();
        saveWork();
        createListNotes();
    }
}

void MainWindow::dialogNewAudio() {
    QString name = dialogNewNote();
    if (!name.isEmpty()) {
        NM::Note &n = NM::NotesManager::getInstance().getNewNAudio();
        n.setTitle(name);
        n.setModified();
        saveWork();
        createListNotes();
    }
}

void MainWindow::dialogNewDocument() {
    QString name = dialogNewNote();
    if (!name.isEmpty()) {
        NM::Note &n = NM::NotesManager::getInstance().getNewDocument();
        n.setTitle(name);
        n.setModified();
        saveWork();
        createListNotes();
    }
}

void MainWindow::viewItem(QListWidgetItem *wi) {
    ui->tabWidget->setCurrentIndex(0);
    if (ui->tab_editor->layout()) {
        QLayoutItem *child;
        while( (child = ui->tab_editor->layout()->takeAt(0)) )  {
            ui->tab_editor->layout()->removeItem( child );
            delete child->widget();
            delete child;
         }
    } else {
        QVBoxLayout *lay = new QVBoxLayout();
        ui->tab_editor->setLayout(lay);
    }

    NM::Note *n = NM::NotesManager::getInstance().getNote(dynamic_cast<QNMListWidgetItem*>(wi)->getId());
    QWidget *wid = new QWidget();

    if (n->getType() == NM::Note::NArticle)
        wid = new Article_modif(n);
    else if (n->getType() == NM::Note::Document)
        wid = new Document_modif(n);

    ui->tab_editor->layout()->addWidget(wid);
}

