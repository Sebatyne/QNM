#include "NotesManager.h"

namespace NM {

    NotesManager *NotesManager::nmInstance = 0;

    NotesManager::NotesManager ()
        : path(QString("../Ressources/"))
    {
        QString s("NArticle");
        NoteFactory *nf = new ArticleFactory(s);
        factories.insert(s, nf);

        s = "Document";
        nf = new DocumentFactory(s);
        factories.insert(s, nf);

        s = "NVideo";
        nf = new VideoFactory(s);
        factories.insert(s, nf);

        s = "NAudio";
        nf = new AudioFactory(s);
        factories.insert(s, nf);

        s = "NImage";
        nf = new ImageFactory(s);
        factories.insert(s, nf);

        loadWorkspace(QString("workspace1"));
    }

    NotesManager & NotesManager::getInstance () {
        if (nmInstance == 0) {
            nmInstance = new NotesManager();
        }

        return *nmInstance;
    }

    void NotesManager::releaseInstance () {
        if (nmInstance != 0) {
            delete nmInstance;
        }
        nmInstance = 0;
    }

    NotesManager::~NotesManager(){
        saveWorkspace();

        //delete sur les factories, les notes si elles ne sont pas enregistrées...
        //save des docs avant les notes, sinon problème
        for(Iterator i = begin(); i != end(); i++) {
            if ((*i)->getType() == Note::Document) {
            if ((*i)->isModified())
                save(*i);
            delete *i;
            }
        }
        for(Iterator i = begin(); i != end(); i++) {
            if ((*i)->getType() != Note::Document) {
            if ((*i)->isModified())
                save(*i);
            delete *i;
            }
        }

        for(Iterator i = corbeille_begin(); i != corbeille_end(); i++)
            delete *i;
    }

    void NotesManager::loadWorkspace(QString fold) {
        if (fold == "")
            fold = "workspace1";

        workspace.mkdir(path + fold);   //crée le dossier si jamais il n'existe pas
        workspace.setPath(path + fold);

        //parcourt le dossier. Si note : ajout au set notes. Si document, crée un document,
        //l'ajoute au set notes, lui fait référencer ses notes (les crée au besoin, en not loaded)

        //parsage du fichier de workspace
        QDomDocument doc(workspace.path());

        QFile file(workspace.path() + "/" +workspace.dirName());

            if (!file.open(QIODevice::ReadOnly))
                qDebug() << "echec à l'ouverture de la ressource\n";
            if (!doc.setContent(&file)) {
                qDebug() << "echec lors de la lecture du dom\n";
                 file.close();
            }

            file.close();

            QDomElement docElem = doc.documentElement();

            QDomNode n = docElem.firstChild();

            //parcours des noeuds
            while (!n.isNull()) {
                //on teste si note
                if (n.toElement().text() != "note")
                    createNoteFromNode(n);
                n = n.nextSibling();
            }
    }

    void NotesManager::createNoteFromNode(const QDomNode n) {
        QDomNode n2 = n.firstChild();

        unsigned int id;
        QString title;
        QString type;

        qDebug() << n2.toElement().text();

        while (!n2.isNull()) {
            QDomElement e = n2.toElement();

            if (!e.isNull()) {
                if (e.tagName() == QString("title")) {
                        title = e.text();
                } else if (e.tagName() == QString("type")) {
                        type = e.text();
                } else if (e.tagName() == QString("id")) {
                        id = e.text().toUInt();
                }
            }

            n2 = n2.nextSibling();
        }

        qDebug() << "Note id :" << id;
        notes << factories[type]->buildNote(id, title);
    }

    Note* NotesManager::getNote (unsigned int id) {
        QSet<Note*>::iterator i;
        for (i = notes.begin(); i != notes.end(); ++i) {
            if ((*i)->getId() == id)
                return *i;
        }
        return 0;
    }

    void NotesManager::addArticle (Note*n) {
        notes<<n;
    }

    void NotesManager::operator <<(Note *n) {
        notes<<n;
    }

    Note & NotesManager::getNewNote(const QString & fact) {
        if(factories.keys().indexOf(fact) != -1) {
            Note *na = factories[fact]->buildNewNote();
            notes<<na;
            return *na;
        } else {
            throw "this factory does not exist";
        }
    }

    Note & NotesManager::getNewNArticle () {
        Note *na = factories["NArticle"]->buildNewNote();
        notes<<na;
        return *na;
    }

    Note & NotesManager::getNewDocument() {
        Note *na = factories["Document"]->buildNewNote();
        notes<<na;
        return *na;
    }

    Note &NotesManager::getNewNImage()
    {
        Note &na = getNewNote("NImage");
        notes<<&na;
        return na;
    }

    Note & NotesManager::getNewNAudio() {
        Note &na = getNewNote("NAudio");
        notes<<&na;
        return na;
    }

    Note & NotesManager::getNewNVideo() {
        Note &na = getNewNote("NVideo");
        notes<<&na;
        return na;
    }

    void NotesManager::save(Note * note) const {
        if (!note->isModified())
            return;

        QFile fd(workspace.path() + "/" + QString::number(note->getId()));
        qDebug() << "Note sauvée dans :" << workspace.path() + "/" + QString::number(note->getId()) << "\n";
        fd.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text);

        QTextStream in(&fd);
        qDebug() << note->toText();
        in << note->toText();

        fd.close();

        note->setModified(false);
    }

    void NotesManager::saveWorkspace() {
        QDomDocument doc("QNM");
        QDomElement root = doc.createElement(workspace.dirName());
        qDebug() << workspace.dirName();
        doc.appendChild(root);

        //ajout des notes au DOM
        for (Iterator it = begin(); it != end(); it++) {
            QDomElement node = doc.createElement("note");
            root.appendChild(node);

            QDomElement tag = doc.createElement("type");
            node.appendChild(tag);
            QDomText t = doc.createTextNode((*it)->getTypeText());
            tag.appendChild(t);

            tag = doc.createElement("id");
            node.appendChild(tag);
            t = doc.createTextNode(QString::number((*it)->getId()));
            tag.appendChild(t);

            tag = doc.createElement("title");
            node.appendChild(tag);
            t = doc.createTextNode((*it)->getTitle());
            tag.appendChild(t);
        }

        //ajout des tag au DOM
        /*TagManager::Iterator it = TagManager::getInstance()->getIterator();

        while (it.hasNext()) {
            QDomElement node = doc.createElement("tag");
            root.appendChild(node);

            QDomElement tag = doc.createElement("name");
            node.appendChild(tag);
            QDomText t = doc.createTextNode(it.getTagLabel());
            tag.appendChild(t);


            QSet<const Note*> setnotes = TagManager::getInstance()->Filter(it.getTagLabel());
            for (QSet<const Note*>::iterator it2 = setnotes.begin(); it2 != setnotes.end(); it2++) {
                tag = doc.createElement("links");
                node.appendChild(tag);
                t = doc.createTextNode(QString::number((*it2)->getId()));
            }

            it.next();
        }*/

        //enregistrement de l'architecture sur le disque
        QFile fd(workspace.path() + "/" + workspace.dirName());
        fd.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text);

        QTextStream in(&fd);
        in << doc.toString();

        fd.close();
    }

void NotesManager::deleteNote(Note *n) {
    corbeille += n;
    notes -= n;

    //suppression de cette note dans les documents
    for (Iterator it = begin(); it != end(); it++) {
        if ((*it)->getType() == Note::Document) {
            Document *doc = dynamic_cast<Document*>(*it);
            doc->removeNote(n);
            save(doc);
        }
    }
    saveWorkspace();
}

Note* NotesManager::restoreNote(unsigned int id) {
    QSet<Note*>::iterator i;
    Note *n;
    for (i = corbeille.begin(); i != corbeille.end(); ++i) {
        if ((*i)->getId() == id)
            n = *i;
    }

    corbeille -= n;
    notes += n;
    return n;
}

}
