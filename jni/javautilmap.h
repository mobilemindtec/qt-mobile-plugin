#ifndef JAVAUTILMAP_H
#define JAVAUTILMAP_H

#include "javalangobject.h"
#include "javautilmapentry.h"
#include "javautilset.h"
#include <QSet>


class JavaUtilMap : public JavaLangObject{
public:
    JavaUtilMap() : JavaLangObject(){}
    JavaUtilMap(QAndroidJniObject obj) : JavaLangObject(obj){}
    void clear();
    bool isEmpty();
    int size();
    JavaUtilSet keySet();
    QSet<JavaUtilMapEntry> entrySet();
    QList<JavaLangObject> values();
    JavaLangObject get(JavaLangObject key);
    JavaLangObject remove(JavaLangObject key);
    void put(JavaLangObject key, JavaLangObject value);
};

#endif // JAVAUTILMAP_H
