#ifndef JAVAIQTVARIANT_H
#define JAVAIQTVARIANT_H

#include "jni/javalangobject.h"
#include "jni/jniutil/javaclassnames.h"

class JavaIQtVariant : public JavaLangObject
{
    Q_OBJECT
public:
    JavaIQtVariant() : JavaLangObject() {}
    JavaIQtVariant(QJniObject obj) : JavaLangObject(obj){}
    JavaIQtVariant(const QString  &errorMessage) : JavaLangObject(errorMessage){};
    JavaIQtVariant(jobject obj) : JavaLangObject(obj){};
    JavaIQtVariant(const JavaIQtVariant & obj) : JavaLangObject(obj) {}
    JavaIQtVariant(const JavaLangObject & obj) : JavaLangObject(obj) {}


    virtual JavaIQtVariant toVariant(){};
    virtual bool isVariant(){ return false; };
    virtual bool isList(){ return false; };
    virtual bool isMap(){ return false; };

    static const QString kJavaClassName;
};



#endif // JAVAIQTVARIANT_H
