#ifndef JAVAUTILMAPENTRY_H
#define JAVAUTILMAPENTRY_H

#include "javalangobject.h"

class JavaUtilMapEntry : public JavaLangObject {
public:
    JavaUtilMapEntry() : JavaLangObject(){}
    JavaUtilMapEntry(QAndroidJniObject obj) : JavaLangObject(obj){}
    JavaUtilMapEntry(const JavaUtilMapEntry &obj) : JavaLangObject(obj){}
    JavaUtilMapEntry(const JavaLangObject &obj) : JavaLangObject(obj){}
    JavaLangObject getKey();
    JavaLangObject getValue();
    JavaLangObject setValue(JavaLangObject &obj);
};


#endif // JAVAUTILMAPENTRY_H
