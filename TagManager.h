#pragma once

#include <Note.h>
#include <Tag.h>

#include <QHash>
#include <QSet>
#include <QString>
#include <QHashIterator>

namespace NM
{
    /**
     * \class TagManager
     * \brief Class permettant de gérer les associations entre des Tags (Tag) et des Notes
     */
    class TagManager
    {
    public :
        class Iterator{
        friend class TagManager;
            QHashIterator<const Tag*, QSet<const Note*> > hashIt;
        public:
            Iterator(QHash<const Tag*, QSet<const Note*> > & hash): hashIt(hash) {}
            bool hasNext(){return hashIt.hasNext();}
            bool hasPrevious(){return hashIt.hasPrevious();}
            const Tag * getTag(){return hashIt.key();}
            const QString & getTagLabel(){return hashIt.key()->getLabel();}
            const QSet<const Note *> & getNoteList(){return hashIt.value();}
            Iterator next(){hashIt.next(); return *this;}
            Iterator previous(){hashIt.previous(); return *this;}
        };


    private :

        static TagManager * Instance;

        QHash<const Tag*, QSet<const Note*> > hash;


        TagManager(TagManager & T);
        TagManager(){}

    public:
        static TagManager * getInstance();

        /**
         * \brief Ajoute un Tag déjà existant à la liste de Tags.
         * \param T : Tag à ajouter
         * \return Si un Tag de la liste possède le même Label que le Tag à ajouter, cette méthode retourne l'adresse du Tag déjà présent. Dans le cas inverse, la méthode renvoie le Tag passé en paramètre
         */
        const Tag * addTag(const Tag * T);

        /**
         * \brief Ajoute un Tag créé à partir de son label
         * Le Tag est créé et ajouté à la liste si aucun Tag de la liste ne possède le même label. Dans le cas échéant, la méthode n'a aucun impact sur la liste de Tag
         * \param label : Label du Tag à créer et à ajouter à la liste de Tags
         * \return \b Un pointeur sur le Tag créé. Si le Tag était déjà présent dans la liste, un pointeur vers ce Tag est renvoyé
         */
        const Tag * addTag(const QString & label);

        /**
         * \brief Opérateur permettant d'ajouter un Tag existant à la liste de Tags
         * Le Tag est créé et ajouté à la liste si aucun Tag de la liste ne possède le même label. Dans le cas échéant, la méthode n'a aucun impact sur la liste de Tag
         * \param label : Tag à ajouter
         * \return \b Un pointeur sur le Tag créé. Si le Tag était déjà présent dans la liste, un pointeur vers ce Tag est renvoyé
         */
        const Tag * operator<<(const Tag * T);

        /**
         * \brief Opérateur permettant d'Ajouter un Tag créé à partir de son label
         * \param label : Label du Tag à créer et à ajouter à la liste de Tags
         * \return Si un Tag de la liste possède le même Label que le Tag à ajouter, cette méthode retourne l'adresse du Tag déjà présent. Dans le cas inverse, la méthode renvoie le Tag passé en paramètre
         */
        const Tag * operator<<(const QString & label);

        /**
         * \brief Supprime le Tag passé en paramètre de la liste de Tags. Si ce tag n'est pas dans la liste, cette méthode n'a aucun effet.
         * \param T : Tag à supprimer
         */
        void removeTag(const Tag * T);

        /**
         * \brief Supprime le Tag dont le Label est passé en paramètre . Si il n'existe aucun tag dans la liste possédant ce Label, cette méthode n'a aucun effet
         * \param label : Label du Tag à supprimer
         */
        void removeTag(const QString & label);

        /**
         * \brief Ajoute un lien entre un Tag et une Note
         * Le tag spécifié est automatiquement ajouté à la liste si il n'est pas déjà présent
         * \param T : Tag
         * \param N : Note
         */
        void addLink(const Tag * T, const Note * N);

        /**
         * \brief Ajoute un lien entre un Tag de Label donné et une Note
         * Le tag spécifié est automatiquement ajouté à la liste si aucun Tag ne passède le Label spécifié
         * \param label : Label du Tag
         * \param N : Note
         */
        void addLink(const QString & label, const Note * N);

        /**
         * \brief Supprime le lien existant entre un Tag et une Note
         * Cette fonction n'a aucun effet si le lien à supprimer était inexistant
         * \param T : Tag
         * \param N : Note
         */
        void removeLink(const Tag * T, const Note * N);

        /**
         * \brief Supprime le lien existant entre un Tag de Label donné et une Note
         * Cette fonction n'a aucun effet si le lien à supprimer était inexistant
         * \param T : Tag
         * \param N : Note
         */
        void removeLink(const QString & label, const Note * N);

        /**
         * \brief Retrouve un tag dans la liste à partir de son Label
         * \param label : Label de la note à trouver
         * \return Un pointeur sur le tag si le tag à dans la liste, NULL si le tag n'est pas présent
         */
        const Tag * find(const QString & label);

        /**
         * \brief Retrouve l'ensemble de notes ayant un lien avec une collection de Tags
         * \param requestedTags : Collection de tags
         * \return L'ensemble de notes liées à l'ensemble des tags passé en paramètre
         */
        QSet<const Note*>Filter(QSet<const Tag*> requestedTags);

        /**
         * \brief Retrouve l'ensemble de notes ayant un lien avec une collection de Tags
         * \param requestedTags : Collection de label de Tags
         * \return L'ensemble de notes liées à l'ensemble des tags passé en paramètre
         */
        QSet<const Note*>Filter(QSet<QString> requestedTags);

        /**
         * \brief Retrouve l'ensemble de notes ayant un lien avec un Tag
         * \param requestedTag : Label d'un Tag
         * \return L'ensemble de notes liées à l'ensemble des tags passé en paramètre
         */
        QSet<const Note*>Filter(QString requestedTag);

        /**
         * \brief Retrouve les tags associés à une note
         * \param N : Note
         * \return L'ensemble des tags associés à la note
         */

        QSet<const Tag*>getLinkedTags(const Note * N) const;

        bool isLinked(QString label, Note * N);

        Iterator getIterator(){return Iterator(this->hash);}
    };
}
