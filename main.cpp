#include "mainwindow.h"
#include <QApplication>
#include <cstdlib>
#include <QDebug>

#include "NotesManager.h"
#include "NotesExporter.h"

using namespace NM;

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));

    NotesManager &nm = NotesManager::getInstance();

    qDebug() << nm.getNbNotes() <<endl;
    
    MainWindow *w = MainWindow::getInstance();

    TagManager::getInstance()->addTag("tag1");
    TagManager::getInstance()->addTag("tag2");
    TagManager::getInstance()->addTag("tag3");

    //nm.saveWorkspace();

    w->show();

    //nm.releaseInstance();

    /*NArticle * A1 = new NArticle(1, "Premièrement", "Essai d'exportation du 1er article au format Latex");
    NVideo * A2 = new NVideo(2, "Deuxièmement, regarde attentivement", "http://youtube.com/?w=FEG6382", "Documentaire sur les papillons");
    NArticle * A3 = new NArticle(3, "Troisièmement", "Essai d'exportation du 3em article au format Latex");
    NImage * A4 = new NImage(4, "Coucou", "1.jpg", "J'ai un regard trop vénere");
    NArticle * A5 = new NArticle(5, "Cinquièmement", "Essai d'exportation du 5em article au format Latex");
    NAudio * A6 = new NAudio(6, "Sixièmement, ecoute attentivement", "http://deezer.com/qsk7x2m9", "Daft Punk - Get Lucky");

    Document * D3 = new Document(9, "Exportation d'un document dans un document dans un document");
    D3->addNote(A5);

    Document * D2 = new Document(8, "Exportation d'un document dans un document");
    D2->addNote(A4);
    D2->addNote(D3);
    D2->addNote(A6);

    Document * D1 = new Document(7, "Test d'exportation d'un ensemble de notes");
    D1->addNote(A1);
    D1->addNote(A2);
    D1->addNote(D2);
    D1->addNote(A3);

    LaTexNotesExporter * Exp1 = new LaTexNotesExporter(D1);
    QString t = Exp1->getRawExport();
    qDebug() << t;*/
    return a.exec();
}

