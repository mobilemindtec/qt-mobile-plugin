#include "javaqtvariantlist.h"

const QString JavaQtVariantList::kJavaClassName = "com/qt/plugin/core/QtVariantList";

void JavaQtVariantList::addValue(JavaLangObject value){
    JniMethodBuilder builder;
    auto signature = builder.argTypedObject(kJavaLangObject)->build();
    this->getJniObject().callMethod<void>("toVariant", signature.toLocal8Bit().constData(), value.getJavaObject());
}

bool JavaQtVariantList::isVariant(){
    return this->getJniObject().callMethod<jboolean>("isVariant");
}

bool JavaQtVariantList::isMap(){
    return this->getJniObject().callMethod<jboolean>("isMap");
}

bool JavaQtVariantList::isList(){
    return this->getJniObject().callMethod<jboolean>("isList");
}

JavaIQtVariant JavaQtVariantList::toVariant(){
    JniMethodBuilder builder;
    auto signature = builder.returnTypedObject(JavaIQtVariant::kJavaClassName)->build();
    auto javaVariant = this->getJniObject().callObjectMethod("toVariant", signature.toLocal8Bit().constData());
    return JavaIQtVariant(javaVariant);
}

JavaUtilList JavaQtVariantList::toList(){
    JniMethodBuilder builder;
    auto signature = builder.returnTypedObject(kJavaUtilList)->build();
    auto javaList = this->getJniObject().callObjectMethod("toList", signature.toLocal8Bit().constData());
    return JavaUtilList(javaList);
}

JavaQtVariantList JavaQtVariantList::from(JavaUtilList value){
    JniMethodBuilder builder;
    auto signature = builder.returnTypedObject(JavaQtVariantList::kJavaClassName)
                            ->argTypedObject(kJavaUtilList)
                            ->build();

    auto javaVariant = QJniObject::callStaticObjectMethod(
                JavaQtVariantList::kJavaClassName.toLocal8Bit().constData(),
                "from",
                signature.toLocal8Bit().constData(),
                value.getJavaObject());

    return JavaQtVariantList(javaVariant);
}
