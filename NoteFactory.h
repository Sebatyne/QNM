#pragma once

#include <QString>
#include <QMap>
#include <QDateTime>
#include "Note.h"

namespace NM {

    class Note;

    /**
     * \class NoteFactory
     * \brief Classe permettant d'allouer des notes de tout type (Design pattern abstract factory)
     * <b>Classe non instanciable</b>
     */
    class NoteFactory
    {
        QString name;
    protected :

        /**
         * \brief Constructeur de la classe NoteFactory. La classe de base étant abstraite, le constructeur de cette classe n'est accessible que par les factories filles.
         * \param n : Nom de la factory
         */
        NoteFactory(QString & n);

        /**
         * \brief Génère un identifiant unique pour une note à partir de l'heure courante
         */
        unsigned int getNewId();
    public:

        /**
         * \brief Permet d'obtenir le nom de la Factory
         */
        const QString & getName() const {return name;}

        /**
         * \brief Instancie une note dont le sous-type (NArticle, Document, NAudio, NVideo, NImage) dépend de la Factory
         * Méthode <b>virtuelle pure</b> devant être redéfinie par chacune des factories fille.
         *
         * \param id : Identifiant de la note
         * \param title : Titre de la note
         */
        virtual Note * buildNote(const unsigned int id, const QString & title = "") = 0;

        /**
         * \brief Instancie une note dont le sous-type (NArticle, Document, NAudio, NVideo, NImage) dépend de la Factory
         * Méthode <b>virtuelle pure</b> devant être redéfinie par chacune des factories fille.
         * Cette méthode fait appel à la méthode getNewId qui permet de générer un identifiant de note automatiquement
         * \param title : Titre de la note
         */
        virtual Note * buildNewNote(const QString & title = "") = 0;
        //virtual Note * buildNote(Note * n);
    };

    /**
     * \class ArticleFactory
     * \brief Classe permettant de produire des notes de type article
     */
    class ArticleFactory : public NoteFactory {

    public :
        /**
         * \brief Constructeur de la classe ArticleFactory
         * \param n : Nom de la factory
         */
        ArticleFactory(QString & n);

        /**
         * \brief Instancie une note de type Article (NArticle)
         * \param id : Identifiant de la note
         * \param title : Titre de la note
         */
        Note * buildNote(const unsigned int id, const QString & title = "");

        /**
         * \brief Instancie une note de type Article
         * \param title : Titre de la note
         */
        Note * buildNewNote(const QString & title = "");
    };

    /**
     * \class DocumentFactory
     * \brief Classe permettant de produire des notes de type Document
     */
    class DocumentFactory : public NoteFactory {

    public :
        /**
         * \brief Constructeur de la classe DocumentFactory
         * \param n : Nom de la factory
         */
        DocumentFactory(QString & n);

        /**
         * \brief Instancie une note de type Document
         * \param id : Identifiant de la note
         * \param title : Titre de la note
         */
        Note * buildNote(const unsigned int id, const QString & title = "");

        /**
         * \brief Instancie une note de type Document
         * \param title : Titre de la note
         */
        Note * buildNewNote(const QString & title = "");
    };

    /**
     * \class DocumentFactory
     * \brief Classe permettant de produire tout type de notes de type Media (NMedia). (Design pattern abstract factory)
     * <b>Classe non instanciable</b>
     */
    class MediaFactory : public NoteFactory {
    protected:
        /**
         * \brief Constructeur de la classe MediaFactory
         * \param n : Nom de la factory
         */
        MediaFactory(QString &n);
    public :
        /**
         * \brief Instancie une note de type Media
         * \param id : Identifiant de la note
         * \param title : Titre de la note
         */
        virtual Note * buildNote(const unsigned int id, const QString &title) = 0;

        /**
         * \brief Instancie une note de type Media
         * \param title : Titre de la note
         */
        virtual Note * buildNewNote(const QString &title) = 0;
    };

    /**
     * \class AudioFactory
     * \brief Classe permettant de produire des notes de type Audio
     */
    class AudioFactory : public MediaFactory{
    public:

        /**
         * \brief Constructeur de la classe AudioFactory
         * \param n : Nom de la factory
         */
        AudioFactory(QString & n) : MediaFactory(n){}

        /**
         * \brief Instancie une note de type Audio (NAudio)
         * \param id : Identifiant de la note
         * \param title : Titre de la note
         */
        Note * buildNote(const unsigned int id, const QString &title);

        /**
         * \brief Instancie une note de type Audio (NAudio)
         * \param title : Titre de la note
         */
        Note * buildNewNote(const QString &title);

    };

    /**
     * \class VideoFactory
     * \brief Classe permettant de produire des notes de type Video (NVideo)
     */
    class VideoFactory : public MediaFactory{
    public:
        /**
         * \brief Constructeur de la classe VideoFactory
         * \param n : Nom de la factory
         */
        VideoFactory(QString & n) : MediaFactory(n){}
        /**
         * \brief Instancie une note de type Video (NVideo)
         * \param id : Identifiant de la note
         * \param title : Titre de la note
         */
        Note * buildNote(const unsigned int id, const QString &title);
        /**
         * \brief Instancie une note de type Audio (NVideo)
         * \param title : Titre de la note
         */
        Note * buildNewNote(const QString &title);
    };

    /**
     * \class ImageFactory
     * \brief Classe permettant de produire des notes de type Image (NImage)
     */
    class ImageFactory : public MediaFactory{
    public:
        /**
         * \brief Constructeur de la classe ImageFactory
         * \param n : Nom de la factory
         */
        ImageFactory(QString & n) : MediaFactory(n){}
        /**
         * \brief Instancie une note de type Image (NImage)
         * \param id : Identifiant de la note
         * \param title : Titre de la note
         */
        Note * buildNote(const unsigned int id, const QString &title);

        /**
         * \brief Instancie une note de type Audio (NVideo)
         * \param title : Titre de la note
         */
        Note * buildNewNote(const QString &title);
    };

}
