#ifndef JAVAUTILSET_H
#define JAVAUTILSET_H

#include "javalangobject.h"
#include "javautilcollection.h"
#include "jniutil/javaclassnames.h"

class JavaUtilSet : public JavaUtilCollection{
public:
    JavaUtilSet() : JavaUtilCollection() {}
    JavaUtilSet(QJniObject obj) : JavaUtilCollection(obj){}
    JavaUtilSet(const JavaUtilSet &obj) : JavaUtilCollection(obj){}
    JavaUtilSet(const JavaLangObject &obj) : JavaUtilCollection(obj){}

};


#endif // JAVAUTILSET_H
