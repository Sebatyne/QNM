#pragma once

#include <QString>
#include <QDebug>
#include <QList>

namespace NM {
    class Note {
    private :
        Note(const Note & n);
        virtual ~Note() {};
        
    protected :
        Note(const unsigned int i, const QString & te = "");
    
        unsigned int id;
        QString title;
        bool loaded;
        bool modified;
    
    public :
    
        const QString & getTitle () const {return title;}
        unsigned int getId () const {return id;}
    
        void setTitle (const QString & te) {title = te;}
    
        bool operator<(const Note & n ) {return this->id < n.getId();}
        bool operator>(const Note & n ) {return this->id > n.getId();}
        bool operator==(const Note & n) {return this->id == n.getId();}
        bool operator!=(const Note & n) {return this->id != n.getId();}
    
        virtual void log() const = 0;
    
    };
    
    class Document : public Note {
        QList<Note*> notes;
    public :
        Document(unsigned int i,const QString & te = "");
    
        void addNote (Note *n);
        void operator<< (Note *n);
    
        void removeNote (Note *n);
    
        void log() const;
    };
    
    class NArticle : public Note {
        QString text;
    
    public :
        NArticle(unsigned int i,const QString & te = "", const QString & txt = "");
        ~NArticle() {}
    
        const QString & getText () const {return text;}
        void setText (const QString & txt) {text = txt;}
    
        void log() const;
    
    };
    
    class NMedia : public Note{
        QString url;
        QString description;
        
    protected :
        NMedia(unsigned int i, const QString & te = "", const QString & url = "", const QString & desc = "");
    public :
        const QString & getUrl() const{return url;}
        void setUrl(QString & const url);
        
        const QString & getDescription() const{return description;}
        void setDescription(QString const & description);
    }
    
    class NAudio : public NMedia{
    public:
        NAudio(unsigned int i, const QString & te = "", const QString & url = "", const QString & desc = "");
    }
    
    class NVideo : public NMedia{
    public:
        NVideo(unsigned int i, const QString & te = "", const QString & url = "", const QString & desc = "");
    }
    
    class NImage : public NMedia{
        NImage(unsigned int i, const QString & te = "", const QString & url = "", const QString & desc = "");
    }
}
