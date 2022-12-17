#include "javautilmapentry.h"

JavaLangObject JavaUtilMapEntry::getKey(){
    auto signature =  JniMethodBuilder::builder()
            ->returnTypedObject(kJavaLangObject)
            ->build();
    QJniObject javaObject = this->getJniObject().callObjectMethod("getKey", signature.toLocal8Bit().constData());
    return JavaLangObject(javaObject);
}

JavaLangObject JavaUtilMapEntry::getValue(){
    auto signature =  JniMethodBuilder::builder()
            ->returnTypedObject(kJavaLangObject)
            ->build();
    QJniObject javaObject = this->getJniObject().callObjectMethod("getValue", signature.toLocal8Bit().constData());
    return JavaLangObject(javaObject);
}

JavaLangObject JavaUtilMapEntry::setValue(JavaLangObject &obj){
    auto signature =  JniMethodBuilder::builder()
            ->returnTypedObject(kJavaLangObject)
            ->arg<jobject>()
            ->build();
    QJniObject javaObject = this->getJniObject().callObjectMethod("setValue", signature.toLocal8Bit().constData(), obj.getJavaObject());
    return JavaLangObject(javaObject);
}
