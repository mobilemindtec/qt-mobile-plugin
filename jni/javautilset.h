#ifndef JAVAUTILSET_H
#define JAVAUTILSET_H

#include "javalangobject.h"
#include "javautilcollection.h"


class JavaUtilSet : public JavaUtilCollection{
public:
    JavaUtilSet() : JavaUtilCollection() {}
    JavaUtilSet(QAndroidJniObject obj) : JavaUtilCollection(obj){}
    JavaUtilSet(const JavaUtilSet &obj) : JavaUtilCollection(obj){}
    JavaUtilSet(const JavaLangObject &obj) : JavaUtilCollection(obj){}
};


#endif // JAVAUTILSET_H
