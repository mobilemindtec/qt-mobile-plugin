#ifndef JAVAUTILLIST_H
#define JAVAUTILLIST_H

#include "javalangobject.h"
#include "javautilcollection.h"
#include "jniutil/jnimethodbuilder.h"
#include "jniutil/javaclassnames.h"

class JavaUtilList : public JavaUtilCollection{
public:
    JavaUtilList() : JavaUtilCollection(){}
    JavaUtilList(QJniObject obj) : JavaUtilCollection(obj){}
    JavaUtilList(jobject obj): JavaUtilCollection(obj){}
    JavaUtilList(const JavaUtilList &obj) : JavaUtilCollection(obj) {}
    JavaUtilList(const JavaLangObject &obj) : JavaUtilCollection(obj) {}
    JavaLangObject get(int const &index);

};

#endif // JAVAUTILLIST_H
