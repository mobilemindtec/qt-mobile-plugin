#ifndef JAVAUTILCOLLECTION_H
#define JAVAUTILCOLLECTION_H

#include "javalangobject.h"
#include "javautiliterator.h"
#include "jniutil/jnimethodbuilder.h"
#include "jniutil/javaclassnames.h"

class JavaUtilCollection: public JavaLangObject{
public:
    JavaUtilCollection() : JavaLangObject() {}
    JavaUtilCollection(QJniObject obj) : JavaLangObject(obj){}
    JavaUtilCollection(jobject obj): JavaLangObject(obj){}
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
