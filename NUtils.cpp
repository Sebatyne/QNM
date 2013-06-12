#include "NUtils.h"

QString NUtils::repeat(unsigned int n, QString repeatedChar){
    QString c = "";
    for(int i = 0; i < n; i++){
        c += repeatedChar;
    }
    return c;
}
