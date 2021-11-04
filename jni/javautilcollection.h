#ifndef JAVAUTILCOLLECTION_H
#define JAVAUTILCOLLECTION_H

#include "javalangobject.h"
#include "javautiliterator.h"
#include "jniutil/jnimethodbuilder.h"

class JavaUtilCollection: public JavaLangObject{
public:
    JavaUtilCollection() : JavaLangObject() {}
    JavaUtilCollection(QAndroidJniObject obj) : JavaLangObject(obj){}
    JavaUtilCollection(const JavaUtilCollection &obj) : JavaLangObject(obj) {}
    JavaUtilCollection(const JavaLangObject &obj) : JavaLangObject(obj) {}
    int size();
    bool remove(JavaLangObject &);
    bool contains(JavaLangObject &);
    bool isEmpty();
    void clear();
    void add(JavaLangObject &);
    JavaUtilIterator iterator();
    QList<JavaLangObject> toArray();
};

#endif // JAVAUTILCOLLECTION_H
