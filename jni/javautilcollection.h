#ifndef JAVAUTILCOLLECTION_H
#define JAVAUTILCOLLECTION_H

#include "javalangobject.h"
#include "javautiliterator.h"

class JavaUtilCollection: public JavaLangObject{
public:
    JavaUtilCollection() : JavaLangObject() {}
    JavaUtilCollection(QAndroidJniObject obj) : JavaLangObject(obj){}
    int size();
    bool remove(JavaLangObject obj);
    bool contains(JavaLangObject obj);
    bool isEmpty();
    void clear();
    void add(JavaLangObject obj);
    JavaUtilIterator iterator();
    QList<JavaLangObject> toArray();
};

#endif // JAVAUTILCOLLECTION_H
