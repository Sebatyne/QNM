#pragma once

#include <QString>
#include <QDebug>
#include <QList>
#include <QFile>
#include <QtXml>
#include "NotesManager.h"

/**
 * \namespace NM
 * \brief{Namespace regroupant tous les composants du gestionnaire de notes}
 */

namespace NM {

    /**
     * \class Note
     * \brief Classe décrivant les différents types de Note
     * La classe de base Note regroupe les attributs communs aux cinq types de notes:
     * - Article (NArticle) : Note composée principalement de texte
     * - Video (NVideo) : Note comportant un fichier video et une description
     * - Audio (NAudio) : Note comportant un fichier audio et une description
     * - Image (NImage) : Note comportant une image et une description
     * - Document (Document) : Note composée d'autre notes, pouvant elles-même être des documents
     * <b>Classe non instanciable</b>
     *}
     *
     */

    class Note {
    private :

        /**
         * \brief Constructeur de copie de la classe Note
         */

        Note(const Note & n);

    protected :

        /**
         * \brief Constructeur de la classe Note
         * \param i : Identifiant de la note
         * \param te : Titre de la note
         */

        Note(const unsigned int i = 0, const QString & te = "");

        unsigned int id;
        QString title;
        bool loaded;
        bool modified;

    public :
        enum noteType{NArticle, Document, NVideo, NAudio, NImage};

        virtual ~Note() {}

        /**
         * \brief Retourne une référence constante sur un QString représentant le titre de la note
        */
        const QString & getTitle () const {return title;}

        /**
         * \brief Retourne un entier représentant l'identifiant de la note
        */
        unsigned int getId () const {return id;}

        /**
         * \brief Détermine si la note a été modifiée ou non
        */
        bool isModified () const {return modified;}

        /**
         * \brief Permet de modifier le titre de la note
        */
        void setTitle (const QString & te) {modified = true; title = te;}

        /**
         * \brief Permet d'indiquer que les informations de la note ont été chargées en mémoire
        */
        void setLoaded() {loaded = true;}

        /**
         * \brief Permet d'indiquer que la note a été modifiée
        */
        void setModified (bool m = true) {modified = m;}

        /**
         * \brief Renvoie la note au format textuel
        */
        virtual QString toText() const = 0;

        /**
         * \brief Charge les informations de la note en mémoire
        */
        virtual void load() = 0;

        /**
         * \brief Renvoie le type de la note
        */
        virtual noteType getType() const = 0;

        /**
         * \brief Renvoie le type de la note au format textuel
        */
        virtual QString getTypeText() const = 0;


        /**
         * \brief Opérateur de comparaison inferieur
         * Une note est inférieure à une autre si son identifiant est inférieur
        */
        bool operator<(const Note & n ) {return this->id < n.getId();}

        /**
         * \brief Opérateur de comparaison supérieur
         * Une note est supérieure à une autre si son identifiant est supérieure
        */
        bool operator>(const Note & n ) {return this->id > n.getId();}

        /**
         * \brief Opérateur de comparaison d'égalité
         * Une note est égale à une autre si son identifiant est égal
        */
        bool operator==(const Note & n) {return this->id == n.getId();}

        /**
         * \brief Opérateur de comparaison de différence
         * Une note est différente d'une une autre si son identifiant est différente
        */
        bool operator!=(const Note & n) {return this->id != n.getId();}

        virtual void log() const = 0;

    };

    /**
     * \class NArticle
     * \brief Classe représentant les notes de type Article
     * Un article est caractérisé par un \b titre et un \b texte
    */

    class NArticle : public Note {
        QString text;

    public :

        /**
         * \brief Constructeur de la classe NArticle
         * \param i : Identifiant de l'article
         * \param te : Titre de l'article
         * \param txt : Texte de l'article
        */
        NArticle(unsigned int i,const QString & te = "", const QString & txt = "");
        ~NArticle() {}


        /**
         * \brief Renvoie une référence constante sur un QString contenant le texte de l'article
        */
        const QString & getText () const {return text;}

        /**
         * \brief Permet de modifier le titre de l'article
         * \param txt : Texte de l'article
        */
        void setText (const QString & txt) {modified = true; text = txt;}

        QString toText () const;
        void load();

        Note::noteType getType() const {return Note::NArticle;}
        QString getTypeText() const {return QString("NArticle");}

        void log() const;

    };


    /**
     * \class Document
     * \brief Classe représentant les notes de type Document
     * Un article est un type de note spécial, permettant d'agréger des notes de tout type (Document compris)
     * Chaque document est caractérisé par un titre et par les notes qu'il contient
    */
    class Document : public Note {
        QList<Note*> notes;
    public :

        /**
         * \class Document::Iterator
         * \brief Classe permettant de parcourir les notes contenues dans un document (Design pattern \b Iterator)
        */
        class Iterator {
            friend class Document;
            QList<Note*>::iterator i;

        public :

            /**
             * \brief Constructeur de l'Iterateur
             * \param s : Liste (QList) de notes
            */
            Iterator(QList<Note*> &s) {i=s.begin();}

            /**
             * \brief Second constructeur de l'Iterateur
             * \param j : Iterateur de document
            */
            Iterator(QList<Note*>::iterator j) {i = j;}

            /**
             * \brief Operateur d'accès à la note courante de l'itérateur
            */
            Note * operator*() {return i.operator *();}

            /**
             * \brief Renvoie l'itérateur courant et passe à la note suivante
            */
            Iterator operator++() {i++; return *this;}

            /**
             * \brief Passe à la note suivante et renvoie l'itérateur associé
            */
            Iterator operator++(int) {Iterator j(i); i++; return j;}

            /**
             * \brief Renvoie l'itérateur courant et passe à la note précédente
            */
            Iterator operator--() {i--; return i;}

            /**
             * \brief Passe à la note précédente et renvoie l'itérateur associé
            */
            Iterator operator--(int) {Iterator j(i); i--; return j;}

            /**
             * \brief Opérateur de comparaison d'égalité entre deux itérateurs
             * Deux itérateurs sont dits égaux si ils pointent sur la même note
            */
            bool operator==(QList<Note*>::iterator j) {return i==j;}

            /**
             * \brief Opérateur de comparaison d'inégalité entre deux itérateurs
             * Deux itérateurs sont dits inégaux si ils ne pointent pas sur la même note
            */
            bool operator!=(QList<Note*>::iterator j) {return i!=j;}

            /**
             * \brief Opérateur de comparaison d'inégalité entre deux itérateurs
             * Deux itérateurs sont dits inégaux si ils ne pointent pas sur la même note
            */
            bool operator!=(Iterator j) {return (*i)!=(*j);}
        };

        /**
         * \brief Constructeur de Document
         * \param i : Identifiant du document
         * \param te : Titre du document
        */
        Document(unsigned int i,const QString & te = "");

        /**
         * \brief Ajoute une note au document
         * \param n : Pointeur sur une note
        */
        void addNote (Note *n);

        /**
         * \brief Opérateur permettant d'ajouter une note à la liste de notes
         * \param n : Pointeur sur une note
        */
        void operator<< (Note *n);

        /**
         * \brief Supprime une note de la liste de note
         * La note est enlevée de la liste sans être désallouée. Cette méthode n'a aucun effet si la note à supprimer n'est pas dans la liste
         * \param n : Pointeur sur une note
        */
        void removeNote (Note *n);

        QString toText () const;
        void load();

        Note::noteType getType() const {return Note::Document;}
        QString getTypeText() const {return QString("Document");}

        void clear() {notes.clear(); modified = true;}

        /**
         * \brief Renvoie un itérateur sur la première note de la liste
        */
        Iterator begin() {this->load(); return Iterator(notes);}

        /**
         * \brief Renvoie un itérateur sur la dernière note de la liste
        */
        Iterator end() {this->load(); Iterator i(notes.end()); return i;}

        void log() const;
    };

    /**
     * \class NMedia
     * \brief Classe représentant les notes de type Media
     * Un media représente les notes de type Audio, Video et Image, qui possèdent des caractéristiques identiques
     * <b>Classe non instanciable</b>
    */
    class NMedia : public Note{
    protected :
        QString url;    //qui peut aussi contenir un path
        QString description;
        NMedia(unsigned int i, const QString & te = "" , const QString & u = "", const QString & desc = "");

    public :

        /**
         * \brief Renvoie l'URL du media
        */
        const QString & getUrl() const{return url;}

        /**
         * \brief Permet de modifier l'URL du media
         * \param url : Url du media
        */
        void setUrl(const QString & u) {modified = true; url = u;}

        /**
         * \brief Renvoie la description associée au media
        */
        const QString & getDescription() const {return description;}

        /**
         * \brief Permet de la description associée au media
         * \param description : Description du media
        */
        void setDescription(QString const & desc) {modified = true; description = desc;}

        virtual QString toText() const = 0;
        virtual Note::noteType getType() const = 0;
        QString getTypeText() const = 0;


        void log() const;

        void load();
    };

    /**
     * \class NAudio
     * \brief Classe représentant les notes de type Audio
    */
    class NAudio : public NMedia{
    public:
        NAudio(unsigned int i, const QString & te = "", const QString & url = "", const QString & desc = ""): NMedia(i, te, url, desc) {}
        QString toText() const;
        Note::noteType getType() const {return Note::NAudio;}
        QString getTypeText() const {return QString("NAudio");}
    };

    /**
     * \class NVideo
     * \brief Classe représentant les notes de type Video
    */
    class NVideo : public NMedia{
    public:
        NVideo(unsigned int i, const QString & te = "", const QString & url = "", const QString & desc = ""): NMedia(i, te, url, desc) {}
        QString toText() const;
        Note::noteType getType() const {return Note::NVideo;}
        QString getTypeText() const {return QString("NVideo");}
    };

    /**
     * \class NImage
     * \brief Classe représentant les notes de type Image
    */
    class NImage : public NMedia{
    public:
        NImage(unsigned int i, const QString & te = "", const QString & url = "", const QString & desc = ""): NMedia(i, te, url, desc) {}
        QString toText() const;
        Note::noteType getType() const {return Note::NImage;}
        QString getTypeText() const {return QString("NImage");}
    };

}
