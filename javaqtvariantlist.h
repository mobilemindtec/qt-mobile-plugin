#ifndef JAVAQTVARIANTLIST_H
#define JAVAQTVARIANTLIST_H

#include "javaiqtvariant.h"

#include "jni/javautillist.h"



class JavaQtVariantList : public JavaIQtVariant
{
    Q_OBJECT
public:
    JavaQtVariantList() : JavaIQtVariant() {}
    JavaQtVariantList(QJniObject obj) : JavaIQtVariant(obj) {}
    JavaQtVariantList(const QString  &errorMessage) : JavaIQtVariant(errorMessage) {};
    JavaQtVariantList(jobject obj) : JavaIQtVariant(obj){};
    JavaQtVariantList(const JavaQtVariantList & obj) : JavaIQtVariant(obj) {}
    JavaQtVariantList(const JavaLangObject & obj) : JavaIQtVariant(obj) {}


    void addValue(JavaLangObject obj);
    JavaUtilList toList();

    bool isVariant() override;
    bool isMap() override;
    bool isList() override;
    JavaIQtVariant toVariant() override;

    static JavaQtVariantList from(JavaUtilList value);
    static const QString kJavaClassName;

};

#endif // JAVAQTVARIANTLIST_H
