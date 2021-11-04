#ifndef JAVAUTILITERATOR_H
#define JAVAUTILITERATOR_H

#include "javalangobject.h"

class JavaUtilIterator : public JavaLangObject{
public:
    JavaUtilIterator() : JavaLangObject() {}
    JavaUtilIterator(jobject obj) : JavaLangObject(obj) {}
    JavaUtilIterator(QAndroidJniObject obj) : JavaLangObject(obj) {}
    JavaUtilIterator(const JavaUtilIterator &obj) : JavaLangObject(obj) {}
    JavaUtilIterator(const JavaLangObject &obj) : JavaLangObject(obj) {}
    void remove();
    JavaLangObject next();
    bool hasNext();
};

#endif // JAVAUTILITERATOR_H
