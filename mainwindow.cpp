#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow *MainWindow::mw = 0;

MainWindow * MainWindow::getInstance() {
    if (mw == 0)
        mw = new MainWindow();
    return mw;
}

void MainWindow::releaseIntance() {
    if (mw != 0)
        delete mw;
    mw = 0;
}

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
    createListTags();
    ui->tree->setCurrentRow(0);

    connect(ui->actionNewArticle,SIGNAL(triggered()), this, SLOT(dialogNewArticle()));
    connect(ui->actionNewDocument,SIGNAL(triggered()), this, SLOT(dialogNewDocument()));
    connect(ui->actionNewVideo,SIGNAL(triggered()), this, SLOT(dialogNewVideo()));
    connect(ui->actionNewImage,SIGNAL(triggered()), this, SLOT(dialogNewImage()));
    connect(ui->actionNewAudio,SIGNAL(triggered()), this, SLOT(dialogNewAudio()));
    connect(ui->actionCorbeille, SIGNAL(triggered()), this, SLOT(showCorbeille()));

    connect(ui->tree, SIGNAL(itemActivated(QListWidgetItem*)), this, SLOT(viewItem(QListWidgetItem*)));
    connect(ui->tree, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(viewItem(QListWidgetItem*)));

    //affichage des exports
    connect(ui->tabWidget, SIGNAL(currentChanged(int)), this, SLOT(showExport(int)));

    //Actions
    connect(ui->actionHTML, SIGNAL(triggered()), this, SLOT(popup_export_HTML()));
    connect(ui->actionTeX, SIGNAL(triggered()), this, SLOT(popup_export_TeX()));
    connect(ui->actionText, SIGNAL(triggered()), this, SLOT(popup_export_text()));
    connect(ui->actionTag, SIGNAL(triggered()), this, SLOT(showTagManager()));
}

MainWindow::~MainWindow()
{
    delete ui;
    saveWork();
    NM::NotesManager::releaseInstance();
}

void MainWindow::saveWork() {
    NM::NotesManager::getInstance().saveWorkspace();
}

void MainWindow::createListNotes() {
    ui->tree->clear();

    QSet<const NM::Note*> toPrint;

    for(NM::NotesManager::Iterator i = NM::NotesManager::getInstance().begin();
            i != NM::NotesManager::getInstance().end(); i++)
        toPrint.insert(*i);

    if (!filtre.empty())
        toPrint = toPrint.intersect(NM::TagManager::getInstance()->Filter(filtre));

    for(QSet<const NM::Note*>::iterator i = toPrint.begin(); i != toPrint.end(); i++) {
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

void MainWindow::createListTags() {
    if(ui->list_Tags->layout()) {
        QLayoutItem *child;
        while( (child = ui->list_Tags->layout()->takeAt(0)) )  {
            ui->list_Tags->layout()->removeItem( child );
            delete child->widget();
            delete child;
         }
    } else {
        QVBoxLayout *lay = new QVBoxLayout();
        ui->list_Tags->setLayout(lay);
    }

    NM::TagManager::Iterator it = NM::TagManager::getInstance()->getIterator();
    while (it.hasNext()) {
        it.next();
        QCheckBox *cb = new QCheckBox(it.getTagLabel());
        connect(cb, SIGNAL(stateChanged(int)), this, SLOT(createFiltre()));
        ui->list_Tags->layout()->addWidget(cb);
    }
}

void MainWindow::createFiltre() {
    connect(this->sender(), SIGNAL(stateChanged(int)), this, SLOT(createFiltre()));

    filtre.clear();
    QLayoutItem *child;

    int i=0;

    while((child = ui->list_Tags->layout()->takeAt(i)) != 0) {
        QCheckBox *ch = dynamic_cast<QCheckBox*>(child->widget());
        if (ch->isChecked())
            filtre << NM::TagManager::getInstance()->addTag(ch->text());
        i++;
     }

    createListNotes();
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
    else if (n->getType() == NM::Note::NImage)
        wid = new Image_modif(n);
    else if (n->getType() == NM::Note::NAudio)
        wid = new Audio_modif(n);
    else if (n->getType() == NM::Note::NVideo)
        wid = new Video_modif(n);
    else
        return;

    ui->tab_editor->layout()->addWidget(wid);
}

void MainWindow::viewHTML(QListWidgetItem *wi) {
    ui->tabWidget->setCurrentIndex(1);
    if (ui->tab_html->layout()) {
        QLayoutItem *child;
        while( (child = ui->tab_html->layout()->takeAt(0)) )  {
            ui->tab_html->layout()->removeItem( child );
            delete child->widget();
            delete child;
         }
    } else {
        QVBoxLayout *lay = new QVBoxLayout();
        ui->tab_html->setLayout(lay);
    }

    NM::Note *n = NM::NotesManager::getInstance().getNote(dynamic_cast<QNMListWidgetItem*>(wi)->getId());
    NM::HTMLNotesExporter * exporter = new NM::HTMLNotesExporter(n);
    QWebView *wv = new QWebView();
    wv->settings()->setAttribute(QWebSettings::AutoLoadImages, true);
    wv->settings()->setAttribute(QWebSettings::PluginsEnabled, true);
    qDebug() << "le HTML : " << exporter->getRawExport();
    wv->setContent(exporter->getRawExport().toAscii(), QString("text/html"), QUrl::fromLocalFile("/"));
    //wv->load(QUrl("/home/nwavrant/Bureau/index.html"));
    ui->tab_html->layout()->addWidget(wv);
}

void MainWindow::viewTeX(QListWidgetItem *wi) {
    ui->tabWidget->setCurrentIndex(2);
    if (ui->tab_TeX->layout()) {
        QLayoutItem *child;
        while( (child = ui->tab_TeX->layout()->takeAt(0)) )  {
            ui->tab_TeX->layout()->removeItem( child );
            delete child->widget();
            delete child;
         }
    } else {
        QVBoxLayout *lay = new QVBoxLayout();
        ui->tab_TeX->setLayout(lay);
    }

    NM::Note *n = NM::NotesManager::getInstance().getNote(dynamic_cast<QNMListWidgetItem*>(wi)->getId());
    NM::LaTexNotesExporter * exporter = new NM::LaTexNotesExporter(n);
    QTextEdit *te = new QTextEdit();
    te->setReadOnly(true);
    ui->tab_TeX->layout()->addWidget(te);
    te->setText(exporter->getRawExport());
}

void MainWindow::viewText(QListWidgetItem *wi) {
    ui->tabWidget->setCurrentIndex(3);
    if (ui->tab_text->layout()) {
        QLayoutItem *child;
        while( (child = ui->tab_text->layout()->takeAt(0)) )  {
            ui->tab_text->layout()->removeItem( child );
            delete child->widget();
            delete child;
         }
    } else {
        QVBoxLayout *lay = new QVBoxLayout();
        ui->tab_text->setLayout(lay);
    }

    NM::Note *n = NM::NotesManager::getInstance().getNote(dynamic_cast<QNMListWidgetItem*>(wi)->getId());
    NM::textNotesExporter * exporter = new NM::textNotesExporter(n);
    QTextEdit *te = new QTextEdit();
    te->setReadOnly(true);
    ui->tab_text->layout()->addWidget(te);
    te->setText(exporter->getRawExport());
}

void MainWindow::showCorbeille() {
    Corbeille_modif *cm = new Corbeille_modif(this);
    cm->show();
}

void MainWindow::showTagManager() {
    if (ui->tree->currentRow() == -1)
        return;

    NM::Note *n = NM::NotesManager::getInstance().getNote(dynamic_cast<QNMListWidgetItem*>(ui->tree->currentItem())->getId());

    Tag_modif *tm = new Tag_modif(n);
    tm->show();
}

void MainWindow::showExport(int nbTab) {
    if (nbTab != 1)
        if (ui->tab_html->layout()) {
            QLayoutItem *child;
            while( (child = ui->tab_html->layout()->takeAt(0)) )  {
                ui->tab_html->layout()->removeItem( child );
                delete child->widget();
                delete child;
             }
        }

    switch (nbTab) {
        case 0 :
            viewItem(ui->tree->currentItem());
            break;

        case 1 :
            viewHTML(ui->tree->currentItem());
            break;

        case 2 :
            viewTeX(ui->tree->currentItem());
            break;

        case 3 :
            viewText(ui->tree->currentItem());
            break;
    }
}

void MainWindow::popup_export_HTML() {
    if (ui->tabWidget->currentIndex() == -1)
        return;

    NM::Note *note = NM::NotesManager::getInstance().getNote(dynamic_cast<QNMListWidgetItem*>(ui->tree->currentItem())->getId());
    NM::HTMLNotesExporter *exporter = new NM::HTMLNotesExporter(note);

    Show_source *sour = new Show_source(exporter->getRawExport(), this);
    sour->exec();
}

void MainWindow::popup_export_TeX() {
    if (ui->tabWidget->currentIndex() == -1)
        return;

    NM::Note *note = NM::NotesManager::getInstance().getNote(dynamic_cast<QNMListWidgetItem*>(ui->tree->currentItem())->getId());
    NM::LaTexNotesExporter *exporter = new NM::LaTexNotesExporter(note);

    Show_source *sour = new Show_source(exporter->getRawExport(), this);
    sour->exec();
}

void MainWindow::popup_export_text() {
    if (ui->tabWidget->currentIndex() == -1)
        return;

    NM::Note *note = NM::NotesManager::getInstance().getNote(dynamic_cast<QNMListWidgetItem*>(ui->tree->currentItem())->getId());
    NM::textNotesExporter *exporter = new NM::textNotesExporter(note);

    Show_source *sour = new Show_source(exporter->getRawExport(), this);
    sour->exec();
}
