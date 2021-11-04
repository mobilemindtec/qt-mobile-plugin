#ifndef JAVAUTILMAP_H
#define JAVAUTILMAP_H

#include "javalangobject.h"
#include "javautilmapentry.h"
#include "javautilset.h"
#include <QList>


class JavaUtilMap : public JavaLangObject{
public:
    JavaUtilMap() : JavaLangObject(){}
    JavaUtilMap(QAndroidJniObject obj) : JavaLangObject(obj){}
    JavaUtilMap(const JavaUtilMap &obj) : JavaLangObject(obj){}
    JavaUtilMap(const JavaLangObject &obj) : JavaLangObject(obj){}
    void clear();
    bool isEmpty();
    int size();
    JavaUtilSet keySet();
    QList<JavaUtilMapEntry> entrySet();
    QList<JavaLangObject> values();
    JavaLangObject get(JavaLangObject &key);
    JavaLangObject remove(JavaLangObject &key);
    void put(JavaLangObject  &key, JavaLangObject &value);
};


#endif // JAVAUTILMAP_H
