#ifndef JAVAUTILLIST_H
#define JAVAUTILLIST_H

#include "javalangobject.h"
#include "javautilcollection.h"

class JavaUtilList : public JavaUtilCollection{
public:
    JavaUtilList() : JavaUtilCollection(){}
    JavaUtilList(QAndroidJniObject obj) : JavaUtilCollection(obj){}
    JavaLangObject get(int const &index);
};

#endif // JAVAUTILLIST_H
