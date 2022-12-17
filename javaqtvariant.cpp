#include "javaqtvariant.h"


const QString JavaQtVariant::kJavaClassName = "com/qt/plugin/core/QtVariant";

JavaQtVariant::~JavaQtVariant(){

}

template<typename T>
T JavaQtVariant::getValue(){

}

void JavaQtVariant::setValue(JavaLangObject value){
    JniMethodBuilder builder;
    auto signature = builder.argTypedObject(kJavaLangObject)->build();
    this->getJniObject().callMethod<void>("toVariant", signature.toLocal8Bit().constData(), value.getJavaObject());
}

bool JavaQtVariant::isValueInt(){
    return this->getJniObject().callMethod<jboolean>("isValueInt");
}

bool JavaQtVariant::isValueLong(){
    return this->getJniObject().callMethod<jboolean>("isValueLong");
}

bool JavaQtVariant::isValueDouble(){
    return this->getJniObject().callMethod<jboolean>("isValueDouble");
}

bool JavaQtVariant::isValueFloat(){
    return this->getJniObject().callMethod<jboolean>("isValueFloat");
}

bool JavaQtVariant::isValueBool(){
    return this->getJniObject().callMethod<jboolean>("isValueBool");
}

bool JavaQtVariant::isValueVariant(){
    return this->getJniObject().callMethod<jboolean>("isValueVariant");
}

bool JavaQtVariant::isValueList(){
    return this->getJniObject().callMethod<jboolean>("isValueList");
}

bool JavaQtVariant::isValueMap(){
    return this->getJniObject().callMethod<jboolean>("isValueMap");
}

bool JavaQtVariant::isValueNull(){
    return this->getJniObject().callMethod<jboolean>("isValueNull");
}

bool JavaQtVariant::isVariant(){
    return this->getJniObject().callMethod<jboolean>("isVariant");
}

bool JavaQtVariant::isMap(){
    return this->getJniObject().callMethod<jboolean>("isMap");
}

bool JavaQtVariant::isList(){
    return this->getJniObject().callMethod<jboolean>("isList");
}

JavaIQtVariant JavaQtVariant::toVariant(){
    JniMethodBuilder builder;
    auto signature = builder.returnTypedObject(JavaIQtVariant::kJavaClassName)->build();
    auto javaVariant = this->getJniObject().callObjectMethod("toVariant", signature.toLocal8Bit().constData());
    return JavaIQtVariant(javaVariant);
}

JavaQtVariant JavaQtVariant::from(JavaLangObject value){
    //auto variant = JavaQtVariant::fromClass(JavaQtVariant::kJavaClassName);
    JniMethodBuilder builder;
    auto signature = builder.returnTypedObject(JavaQtVariant::kJavaClassName)
                            ->argTypedObject(kJavaLangObject)
                            ->build();

    auto javaVariant = QJniObject::callStaticObjectMethod(
                JavaQtVariant::kJavaClassName.toLocal8Bit().constData(),
                "from",
                signature.toLocal8Bit().constData(),
                value.getJavaObject());

    return JavaQtVariant(javaVariant);
}
