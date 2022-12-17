#ifndef JAVAQTVARIANT_H
#define JAVAQTVARIANT_H

#include "javaiqtvariant.h"
#include "jni/javalangobject.h"



class JavaQtVariant : public JavaIQtVariant
{
    Q_OBJECT
public:

    explicit JavaQtVariant() : JavaIQtVariant() {}
    JavaQtVariant(QJniObject obj) : JavaIQtVariant(obj){}
    JavaQtVariant(const QString  &errorMessage) : JavaIQtVariant(errorMessage){};
    JavaQtVariant(jobject obj) : JavaIQtVariant(obj){};
    JavaQtVariant(const JavaQtVariant & obj) : JavaIQtVariant(obj) {}
    JavaQtVariant(const JavaLangObject & obj) : JavaIQtVariant(obj) {}
    ~JavaQtVariant();

    template<typename T>
    T getValue();
    void setValue(JavaLangObject value);
    bool isValueInt();
    bool isValueLong();
    bool isValueDouble();
    bool isValueFloat();
    bool isValueBool();
    bool isValueVariant();
    bool isValueList();
    bool isValueMap();
    bool isValueNull();
    bool isVariant() override;
    bool isMap() override;
    bool isList() override;
    JavaIQtVariant toVariant() override;

    static JavaQtVariant from(JavaLangObject value);
    static const QString kJavaClassName;
};

#endif // JAVAQTVARIANT_H
