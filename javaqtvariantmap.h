#ifndef JAVAQTVARIANTMAP_H
#define JAVAQTVARIANTMAP_H

#include "javaiqtvariant.h"
#include "jni/javautilmap.h"


class JavaQtVariantMap : public JavaIQtVariant
{
    Q_OBJECT
public:
    JavaQtVariantMap() : JavaIQtVariant() {}
    JavaQtVariantMap(QJniObject obj) : JavaIQtVariant(obj) {}
    JavaQtVariantMap(const QString  &errorMessage) : JavaIQtVariant(errorMessage) {};
    JavaQtVariantMap(jobject obj) : JavaIQtVariant(obj) {};
    JavaQtVariantMap(const JavaQtVariantMap & obj) : JavaIQtVariant(obj) {}
    JavaQtVariantMap(const JavaLangObject & obj) : JavaIQtVariant(obj) {}


    void addValue(JavaLangObject obj);
    JavaUtilMap toMap();

    bool isVariant() override;
    bool isMap() override;
    bool isList() override;
    JavaIQtVariant toVariant() override;

    static JavaQtVariantMap from(JavaUtilMap value);
    static const QString kJavaClassName;

};

#endif // JAVAQTVARIANTMAP_H
