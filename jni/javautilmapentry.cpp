#include "javautilmapentry.h"

JavaLangObject JavaUtilMapEntry::getKey(){
    const char* signature =  JniMethodBuilder::builder()
            ->returnTypedObject(JniMethodBuilder::kJavaClassNameObject)
            ->build();
    QAndroidJniObject javaObject = this->getJniObject().callObjectMethod("getKey", signature);
    return JavaLangObject(javaObject);
}

JavaLangObject JavaUtilMapEntry::getValue(){
    const char* signature =  JniMethodBuilder::builder()
            ->returnTypedObject(JniMethodBuilder::kJavaClassNameObject)
            ->build();
    QAndroidJniObject javaObject = this->getJniObject().callObjectMethod("getValue", signature);
    return JavaLangObject(javaObject);
}

JavaLangObject JavaUtilMapEntry::setValue(JavaLangObject &obj){
    const char* signature =  JniMethodBuilder::builder()
            ->returnTypedObject(JniMethodBuilder::kJavaClassNameObject)
            ->arg<jobject>()
            ->build();
    QAndroidJniObject javaObject = this->getJniObject().callObjectMethod("setValue", signature, obj.getJavaObject());
    return JavaLangObject(javaObject);
}
