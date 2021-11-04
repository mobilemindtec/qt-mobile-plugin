#ifndef JAVAUTILLIST_H
#define JAVAUTILLIST_H

#include "javalangobject.h"
#include "javautilcollection.h"
#include "jni/jniutil/jnimethodbuilder.h"

class JavaUtilList : public JavaUtilCollection{
public:
    JavaUtilList() : JavaUtilCollection(){}
    JavaUtilList(QAndroidJniObject obj) : JavaUtilCollection(obj){}
    JavaUtilList(const JavaUtilList &obj) : JavaUtilCollection(obj) {}
    JavaUtilList(const JavaLangObject &obj) : JavaUtilCollection(obj) {}
    JavaLangObject get(int const &index);
};

#endif // JAVAUTILLIST_H
