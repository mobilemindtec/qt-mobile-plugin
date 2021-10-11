#ifndef JAVAUTILITERATOR_H
#define JAVAUTILITERATOR_H

#include "javalangobject.h"

class JavaUtilIterator : public JavaLangObject{
public:
    JavaUtilIterator() : JavaLangObject() {}
    JavaUtilIterator(QAndroidJniObject obj) : JavaLangObject(obj) {}
    void remove();
    JavaLangObject next();
    bool hasNext();
};

#endif // JAVAUTILITERATOR_H
