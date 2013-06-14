#pragma once

#include <QList>
#include <QDateTime>
#include <QMap>

#include "Note.h"
#include "NUtils.h"

namespace NM{

    /**
     * \brief Classe définissant le comportement de tous les exporters de notes (Design Pattern Strategy).
     *
     * <b>Classe non instanciable</b>
     */

    class NotesExporter
    {
    protected:
        Note * ExportedNote;

        /**
         * \brief Constructeur de la classe NotesExporter
         *
         * \param ExportedNote : Note à exporter
         */
        NotesExporter(Note * ExportedNote) : ExportedNote(ExportedNote){}
        bool delimitParts;
        bool displayDate;

        /**
         * \brief Permet de définir si la date doit être affichée sur l'export
         */
        void setDisplayDate(bool DisplayDate){displayDate = DisplayDate;}

        /**
         * \brief Définit si la fin d'un document doit être succédé d'une barre horizontale de séparation
         */
        void setDelimitParts(bool DelimitParts){delimitParts = DelimitParts;}

    public:
        /**
         * \brief Méthode permettant d'obtenir la conversion de la note au format voulu. Ce format dépend de l'implémentation de cette méthode dans les classes filles.
         */
        virtual QString getRawExport() = 0;

        /**
         * \brief Permet de définir la note à exporter
         * \param ExportedNote : Note à exporter
         */
        void setExportedNote(Note * ExportedNote);
    };

    /**
     * \class textNotesExporter
     * \brief Classe permettant d'exporter une note dans un format texte basique.
     * Implémentation de l'interface NotesExporter
     */
    class textNotesExporter : NotesExporter{
        /**
         * \brief Méthode (\b privée) permettant de convertir n'importe quel type de note, en une note au format textuel
         * Cette méthode convertis l'intégralité d'une note en parcourant de manière récursive les documents qu'elle contient.
         * \param convertedNote : Note à convertir
         * \param TitleLevel : Niveau de titre de la note convertie: 0 (Titre de la page) - N (Nième partie du document)
         * \return Un QString contenant le la note convertie au format textuel
         */
        QString NoteToText(Note * convertedNote, unsigned int TitleLevel);

        /**
         * \brief Permet de convertir un article au format textuel (\b privée)
         * \param convertedNote : Note à convertir
         * \param TitleLevel : Niveau de titre de la note convertie: 0 (Titre de la page) - N (Nième partie du document)
         * \return Un QString contenant le l'article converti au format textuel
         */
        QString ArticleToText(NArticle * ConvertedArticle, unsigned int titleLevel);

        /**
         * \brief Permet de convertir une Image au format textuel (\b privée)
         * Puisqu'il est impossible d'afficher une image dans un format textuel brut, un lien vers l'image est fourni lors de la conversion
         * \param convertedNote : Note à convertir
         * \param TitleLevel : Niveau de titre de la note convertie: 0 (Titre de la page) - N (Nième partie du document)
         * \return Un QString contenant le l'article converti au format textuel
         */
        QString ImageToText(NImage * ConvertedImage, unsigned int titleLevel);

        /**
         * \brief Permet de convertir une note Audio au format textuel (\b privée)
         * Puisqu'il est impossible de jouer un fichier audio dans un format textuel brut, un lien vers le fichier audio est fourni lors de la conversion
         * \param convertedNote : Note à convertir
         * \param TitleLevel : Niveau de titre de la note convertie: 0 (Titre de la page) - N (Nième partie du document)
         * \return Un QString contenant la note audio convertie au format textuel
         */
        QString AudioToText(NAudio * ConvertedAudio, unsigned int titleLevel);

        /**
         * \brief Permet de convertir une note Video au format textuel (\b privée)
         * Puisqu'il est impossible de jouer un fichier video dans un format textuel brut, un lien vers le fichier video est fourni lors de la conversion
         * \param convertedNote : Note à convertir
         * \param TitleLevel : Niveau de titre de la note convertie: 0 (Titre de la page) - N (Nième partie du document)
         * \return Un QString contenant la note video convertie au format textuel
         */
        QString VideoToText(NVideo * ConvertedVideo, unsigned int titleLevel);
    public:
        /**
         * \brief Constructeur de la classe textNotesExporter
         *
         * \param ExportedNote : Note à exporter
         */
        textNotesExporter(Note * ExportedNote) : NotesExporter(ExportedNote){
            delimitParts = true;
            displayDate = false;
        }
        QString getRawExport();
    };

    class HTMLNotesExporter : NotesExporter{
        QString spreadSheet;
    public:
        HTMLNotesExporter(Note * ExportedNote) : NotesExporter(ExportedNote){

        }

        void setSpreadSheet(QString & css);
        QString getSpreadSheet(){return spreadSheet;}

        QString getRawExport();

    };

    /**
     * \class LaTexNotesExporter
     * \brief Classe permettant d'exporter une note au format LaTex.
     * Implémentation de l'interface NotesExporter
     */
    class LaTexNotesExporter : NotesExporter{
    public:
        enum latexDocType{book, article, report};


        /**
         * \brief Constructeur de la classe LaTexNotesExporter
         * \param ExportedNote : Note à exporter
         */
        LaTexNotesExporter(Note * ExportedNote) : NotesExporter(ExportedNote){
            ignoreAudio = false;
            ignoreVideo = false;
            ignoreNumbering = true;
            delimitParts = true;
            displayDate = false;
            docType = article;

            titleSize.insert(1, "part");
            titleSize.insert(2, "section");
            titleSize.insert(3, "subsection");
            titleSize.insert(4, "subsubsection");
        }

        /**
         * \brief Permet d'indiquer vers quel type de document latex convertir la note ("Book", "Article", "Report")
         * \param docType : Type de document. Liste disponible dans l'énumération LaTexNotesExporter::latexDocType
         */
        void setDocType(latexDocType docType);

        /**
         * \brief Permet d'obtenir le type de document Latex choisi
         */
        latexDocType getDocType() const {return docType;}

        /**
         * \brief Permet de choisir si les notes au format Audio doivent êtres pris en compte ou ignorés lors de la conversion
         */
        void setIgnoreAudio(bool IgnoreAudio){ignoreAudio = IgnoreAudio;}

        /**
         * \brief Permet de choisir si les notes au format Video doivent êtres pris en compte ou ignorés lors de la conversion
         */
        void setIgnoreVideo(bool IgnoreVideo){ignoreVideo = IgnoreVideo;}

        /**
         * \brief Permet de choisir si la numérotation des parties du document doit être affichée ou non
         */
        void setIgnoreNumerotation(bool IgnoreNumbering){ignoreNumbering = IgnoreNumbering;}

        QString getRawExport();
    private:
        latexDocType docType;
        bool ignoreAudio;
        bool ignoreVideo;
        bool ignoreNumbering;

        QMap <int, QString> titleSize;

        /**
         * \brief Méthode (\b privée) permettant de convertir n'importe quel type de note, en une note au format latex
         * Cette méthode convertis l'intégralité d'une note en parcourant de manière récursive les documents qu'elle contient.
         * \param convertedNote : Note à convertir
         * \param TitleLevel : Niveau de titre de la note convertie: 0 (Titre de la page) - N (Nième partie du document).
         * \return Un QString contenant le la note convertie au format textuel
         */
        QString NoteToLatex(Note * ConvertedNote, unsigned int titleLevel);

        /**
         * \brief Permet de convertir un article au format latex (\b privée)
         * \param convertedNote : Note à convertir
         * \param TitleLevel : Niveau de titre de la note convertie: 0 (Titre de la page) - N (Nième partie du document)
         * \return Un QString contenant le l'article converti au format latex
         */
        QString ArticleToLatex(NArticle * ConvertedArticle, unsigned int titleLevel);

        /**
         * \brief Permet de convertir une note de type Image au format latex (\b privée)
         * \param convertedNote : Note à convertir
         * \param TitleLevel : Niveau de titre de la note convertie: 0 (Titre de la page) - N (Nième partie du document)
         * \return Un QString contenant la note Image convertie au format latex
         */
        QString ImageToLatex(NImage * ConvertedImage, unsigned int titleLevel);

        /**
         * \brief Permet de convertir une note de type Audio au format latex (\b privée)
         * \param convertedNote : Note à convertir
         * \param TitleLevel : Niveau de titre de la note convertie: 0 (Titre de la page) - N (Nième partie du document)
         * \return Un QString contenant la note Audio convertie au format latex
         */
        QString AudioToLatex(NAudio * ConvertedAudio, unsigned int titleLevel);

        /**
         * \brief Permet de convertir une note de type Video au format latex (\b privée)
         * \param convertedNote : Note à convertir
         * \param TitleLevel : Niveau de titre de la note convertie: 0 (Titre de la page) - N (Nième partie du document)
         * \return Un QString contenant la note Video convertie au format latex
         */
        QString VideoToLatex(NVideo * ConvertedVideo, unsigned int titleLevel);
    };
}
