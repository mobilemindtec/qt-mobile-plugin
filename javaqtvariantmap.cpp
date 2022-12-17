#include "javaqtvariantmap.h"

const QString JavaQtVariantMap::kJavaClassName = "com/qt/plugin/core/QtVariantMap";

void JavaQtVariantMap::addValue(JavaLangObject value){
    JniMethodBuilder builder;
    auto signature = builder.argTypedObject(kJavaLangObject)->build();
    this->getJniObject().callMethod<void>("toVariant", signature.toLocal8Bit().constData(), value.getJavaObject());
}

bool JavaQtVariantMap::isVariant(){
    return this->getJniObject().callMethod<jboolean>("isVariant");
}

bool JavaQtVariantMap::isMap(){
    return this->getJniObject().callMethod<jboolean>("isMap");
}

bool JavaQtVariantMap::isList(){
    return this->getJniObject().callMethod<jboolean>("isList");
}

JavaIQtVariant JavaQtVariantMap::toVariant(){
    JniMethodBuilder builder;
    auto signature = builder.returnTypedObject(JavaIQtVariant::kJavaClassName)->build();
    auto javaVariant = this->getJniObject().callObjectMethod("toVariant", signature.toLocal8Bit().constData());
    return JavaIQtVariant(javaVariant);
}

JavaUtilMap JavaQtVariantMap::toMap(){
    JniMethodBuilder builder;
    auto signature = builder.returnTypedObject(kJavaUtilMap)->build();
    auto javaList = this->getJniObject().callObjectMethod("toMap", signature.toLocal8Bit().constData());
    return JavaUtilMap(javaList);
}

JavaQtVariantMap JavaQtVariantMap::from(JavaUtilMap value){
    JniMethodBuilder builder;
    auto signature = builder.returnTypedObject(JavaQtVariantMap::kJavaClassName)
                            ->argTypedObject(kJavaUtilMap)
                            ->build();

    auto javaVariant = QJniObject::callStaticObjectMethod(
                JavaQtVariantMap::kJavaClassName.toLocal8Bit().constData(),
                "from",
                signature.toLocal8Bit().constData(),
                value.getJavaObject());

    return JavaQtVariantMap(javaVariant);
}
