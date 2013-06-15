#pragma once
#include <QString>

namespace NM
{
    class Tag
    {
        QString label;
    public:
        Tag(const QString & label) : label(label){}

        void setLabel(const QString & label){this->label = label;}

        const QString & getLabel() const{return this->label;}
        QString & getLabel(){return this->label;}

        bool operator==(const Tag & t) const {return label == t.label;}
        bool operator==(const QString & str) const {return label == str;}

        bool operator!=(const Tag & t) const {return label != t.label;}
        bool operator!=(const QString & str) const {return label != str;}

        operator QString(){return this->label;}
    };
}
