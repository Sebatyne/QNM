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

        saveWorkspace();
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
                createNoteFromNode(n);
                n = n.nextSibling();
            }

            /*
            n = docElem.firstChild();
            while (!n.isNull()) {
                if(n.nodeName() == "document") {
                        //puis ajout des documents
                        createDocFromNode(n);
                }
                    n = n.nextSibling();
            }*/

        //ancienne solution chargeant le workspace en fonction des fichiers présents
        /*workspace.setFilter(QDir::Files | QDir::NoSymLinks | QDir::NoDotAndDotDot | QDir::Readable | QDir::Writable);
        QStringList dir = workspace.entryList();

        //lecture des fichiers
        for (int i = 0; i < dir.size(); i++) {
            //affiche le nom du fichier disque correspondant
            qDebug() <<  workspace.path() + "/" + dir.at(i);

            //on déclare un descripteur de fichier, ouvert en read-only
            QFile fd(workspace.path() + "/" + dir.at(i));
            fd.open(QIODevice::ReadOnly);

            //on récupère l'id de la note, son type et son titre (chop supprime le dernier caractère de ligne "\n"
            QString sid = fd.readLine();
            sid.chop(1);
            unsigned int id = sid.toUInt(); //vérification du nom ??
            qDebug() << id;
            QString type = fd.readLine();
            type.chop(1);
            QString title = fd.readLine();
            title.chop(1);

            //ajout à notes de la note qui vient d'être lue, puis fermeture de la note
            qDebug() << "type :" << type<< " title :" << title;
            notes << factories[type]->buildNote(id, title);

            fd.close();
        }*/
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

/*
    void NotesManager::createDocFromNode(const QDomNode n) {
        QDomNode n2 = n.firstChild();

        unsigned int id;
        QString title;
        QList<unsigned int> sn;

        qDebug() << n2.toElement().text();

        while (!n2.isNull()) {
            QDomElement e = n2.toElement();
            //qDebug() << e.text();

            if (!e.isNull()) {
                if (e.tagName() == QString("title")) {
                        title = e.text();
                } else if (e.tagName() == QString("id")) {
                    id = e.text().toUInt();
                } else if (e.tagName() == QString("sous-note")) {
                    sn << e.text().toUInt();
                }
            }

            n2 = n2.nextSibling();
        }

        NM::Document *d = dynamic_cast<NM::Document*>(factories["Document"]->buildNote(id, title));

        for(QList<unsigned int>::iterator it = sn.begin(); it != sn.end(); it++) {
            d->addNote(this->getNote(*it));
        }

        notes << d;
    }
*/
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
        doc.appendChild(root);

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

        QFile fd(workspace.path() + "/" + workspace.dirName());
        fd.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text);

        QTextStream in(&fd);
        in << doc.toString();

        fd.close();
    }
}
