#include "TagManager.h"

namespace NM
{
    TagManager * TagManager::Instance = 0;

    TagManager * TagManager::getInstance(){
        if(!Instance){
            Instance = new TagManager();
        }
        return Instance;
    }

    const Tag * TagManager::addTag(const Tag * T){
        NM::NotesManager::getInstance().saveWorkspace();
        if(!hash.contains(T)){
            QString label = T->getLabel();

            QHashIterator<const Tag*, QSet<const Note*> > it(hash);
            while(it.hasNext()){
                it.next();
                if(it.key()->getLabel() == label){
                    return it.key();
                }
            }
            hash[T].empty();
        }
        return T;
    }

    const Tag * TagManager::addTag(const QString & label){
        NM::NotesManager::getInstance().saveWorkspace();
        QHashIterator<const Tag*, QSet<const Note*> > it(hash);
        while(it.hasNext()){
            it.next();
            if(it.key()->getLabel() == label){
                return it.key();
            }
        }

        Tag * NewTag = new Tag(label);
        hash[NewTag].empty();
        return NewTag;
    }

    const Tag * TagManager::operator<<(const Tag * T){
        return this->addTag(T);
    }

    const Tag * TagManager::operator<<(const QString & label){
        return this->addTag(label);
    }

    void TagManager::removeTag(const Tag * T){
        NM::NotesManager::getInstance().saveWorkspace();
        hash.remove(T);
    }

    void TagManager::removeTag(const QString & label){
        NM::NotesManager::getInstance().saveWorkspace();
        QHashIterator<const Tag*, QSet<const Note*> > it(hash);

        bool found = false;
        const Tag * T;
        while(it.hasNext() && !found){
            it.next();
            if(it.key()->getLabel() == label){
                found = true;
                T = it.key();
            }
        }

        if(found){
            hash.remove(T);
        }
    }

    void TagManager::addLink(const Tag * T, const Note * N){
        NM::NotesManager::getInstance().saveWorkspace();
        if(!hash[T].contains(N)){
            hash[T].insert(N);
        }
    }

    void TagManager::addLink(const QString & label, const Note * N){
        NM::NotesManager::getInstance().saveWorkspace();
        this->addLink(this->addTag(label), N);
    }

    void TagManager::removeLink(const Tag * T, const Note * N){
        if(hash.contains(T)){
            hash[T].remove(N);
        }
    }

    void TagManager::removeLink(const QString & label, const Note * N){
        NM::NotesManager::getInstance().saveWorkspace();
        const Tag * T = this->find(label);
        if(T){
            hash[T].remove(N);
        }
    }

    const Tag * TagManager::find(const QString & label){
        QHashIterator<const Tag*, QSet<const Note*> > it(hash);
        while(it.hasNext()){
            it.next();
            if(it.key()->getLabel() == label){
                return it.key();
            }
        }
        return 0;
    }

    QSet<const Note*> TagManager::Filter(QSet<const Tag*> requestedTags){
        QSet<const Tag*>::Iterator it = requestedTags.begin();
        QSet<const Note*> rNotes = hash[(*it++)];
        for(;it != requestedTags.end(); it++){
            rNotes.intersect(hash[*it]);
        }
        return rNotes;
    }

    QSet<const Note*> TagManager::Filter(QSet<QString> requestedStringTags){
        QSet<QString>::Iterator it = requestedStringTags.begin();
        QSet<const Tag*> requestedTags;

        QSet<const Note*> rNotes;

        for(;it != requestedStringTags.end(); it++){
            const Tag * foundTag = this->find(*it);
            if(!foundTag){
                rNotes.empty();
                return rNotes;
            }
            requestedTags.insert(foundTag);
        }
        return this->Filter(requestedTags);
    }

    QSet<const Note*> TagManager::Filter(QString requestedTag) {
        QSet<QString> set;
        set << requestedTag;
        return Filter(set);
    }

    QSet<const Tag*> TagManager::getLinkedTags(const Note * N) const{
        QHashIterator<const Tag*, QSet<const Note*> > it(hash);
        QSet<const Tag*> linkedTags;
        while(it.hasNext()){
            it.next();
            const QSet<const Note*> noteSet = it.value();
            if(noteSet.contains(N)){
                linkedTags.insert(it.key());
            }
        }
        return linkedTags;
    }
}
