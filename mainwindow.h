#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidget>
#include <QList>
#include <QSet>
#include <QListWidgetItem>
#include <QStringList>
#include <QString>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QInputDialog>
#include <QVBoxLayout>
#include <QWidget>
#include <QTextEdit>
#include <QtWebKit/QWebView>
#include <QCheckBox>
#include "TagManager.h"
#include "Tag.h"
#include "NotesManager.h"
#include "QNMListWidgetItem.h"
#include "Article_modif.h"
#include "Document_modif.h"
#include "Image_modif.h"
#include "Audio_modif.h"
#include "Video_modif.h"
#include "Corbeille_modif.h"
#include "Tag_modif.h"
#include "Show_source.h"

namespace Ui {
class MainWindow;
}

class QNMListWidgetItem;

/**
 * \class MainWindow
 * \brief Classe singleton représentant l'interface graphique. Dépend d'un fichier .ui
 */

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    ~MainWindow();

    /**
     * \brief Retourne l'unique instance permise de la fenêtre principale
    */
    static MainWindow* getInstance();

    /**
     * \brief Libére la mémoire occupée par la fenêtre de l'application
    */
    static void releaseIntance();

private slots :
    /**
     * \brief Indique au Notes-Manager d'enregistrer l'espace de travail.
     *Cette fonction est invoquée lors de la destruction de la fenêtre
    */
    void saveWork();

    /**
     * \brief S'occupe de la création d'un nouvel Article
    */
    void dialogNewArticle();
    /**
     * \brief S'occupe de la création d'une nouvelle Image
    */
    void dialogNewImage();
    /**
     * \brief S'occupe de la création d'une nouvlle Video
    */
    void dialogNewVideo();
    /**
     * \brief S'occupe de la création d'un nouveau media Audio
    */
    void dialogNewAudio();
    /**
     * \brief S'occupe de la création d'un nouveau Document
    */
    void dialogNewDocument();
    /**
     * \brief Demande un nom de note à l'utilisateur
     *Cette fonction est appelée par :
     *  - dialogNewArticle
     *  - dialogNew...
    */
    QString dialogNewNote();
    /**
     * \brief Affiche le widget correspondant à la note que l'utilisateur veut éditer
    */
    void viewItem(QListWidgetItem *wi);
    /**
     * \brief Affiche l'export HTML correspondant à la note que l'utilisateur veut éditer
    */
    void viewHTML(QListWidgetItem *wi);
    /**
     * \brief Affiche l'export TeX correspondant à la note que l'utilisateur veut éditer
    */
    void viewTeX(QListWidgetItem *wi);
    /**
     * \brief Affiche l'export texte correspondant à la note que l'utilisateur veut éditer
    */
    void viewText(QListWidgetItem *wi);
    /**
     * \brief lance la popup de la corbeille
    */
    void showCorbeille();
    /**
     * \brief lance la popup du gestionnaire de tags
    */
    void showTagManager();
    /**
     * \brief Affiche l'export de la note actuellement sélectionnée
     *Fonction appelée lors de l'appui sur l'un des onglets de la zone d'affichage
     */
    void showExport(int nbTab);
    /**
     * \brief affiche une popup lors d'un export HTML affichant le texte de la source
     */
    void popup_export_HTML();
    /**
     * \brief affiche une popup lors d'un export TeX affichant le texte de la source
     */
    void popup_export_TeX();
    /**
     * \brief affiche une popup lors d'un export texte affichant le texte de la source
     */
    void popup_export_text();
public slots :
    /**
     * \brief Met à jour l'affichage de la liste des notes du workspace
    */
    void createListNotes();

    /**
     * \brief Met à jour l'affichage de la liste des tags du workspace
    */
    void createListTags();

    void createFiltre();
    
private:
    Ui::MainWindow *ui;
    //QStandardItemModel *arborescence;
    //QStandardItem *parentItem;

    static MainWindow *mw;

    explicit MainWindow(QWidget *parent = 0);

    QSet<const NM::Tag*> filtre;
};



#endif // MAINWINDOW_H
