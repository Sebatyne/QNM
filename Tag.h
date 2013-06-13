#pragma once
#include <QString>

namespace NM
{
    class Tag
    {
        QString tagName;
    public:
        Tag(QString tagName) : tagName(tagName){}

        void setTagName(QString tagName){this->tagName = tagName;}

        const QString & getTagName() const{return this->tagName;}
        QString & getTagName(){return this->tagName;}

        bool operator==(const Tag & t) const {return tagName == t.tagName;}
        bool operator==(const QString & str) const {return tagName == str;}

        bool operator!=(const Tag & t) const {return tagName != t.tagName;}
        bool operator!=(const QString & str) const {return tagName != str;}
    };
}
