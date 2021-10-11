#include "javautilmapentry.h"



JavaLangObject JavaUtilMapEntry::getKey(){
    char * signature =  JniMethodBuilder::builder()
            ->returnType(JniMethodBuilder::JavaClassNameObject)
            ->build();
    jobject javaObject = this->jniObj->callMethod<jobject>("getKey", signature);
    return JavaLangObject::fromLocalRef<JavaLangObject>(javaObject);
}

JavaLangObject JavaUtilMapEntry::getValue(){
    char * signature =  JniMethodBuilder::builder()
            ->returnType(JniMethodBuilder::JavaClassNameObject)
            ->build();
    jobject javaObject = this->jniObj->callMethod<jobject>("getValue", signature);
    return JavaLangObject::fromLocalRef<JavaLangObject>(javaObject);
}

JavaLangObject JavaUtilMapEntry::setValue(JavaLangObject obj){
    char * signature =  JniMethodBuilder::builder()
            ->returnType(JniMethodBuilder::JavaClassNameObject)
            ->argObject()
            ->build();
    jobject javaObject = this->jniObj->callMethod<jobject>("setValue", signature, obj.object());
    return JavaLangObject::fromLocalRef<JavaLangObject>(javaObject);
}


template <>
JavaUtilMapEntry JavaLangObject::fromLocalRef<JavaUtilMapEntry>(jobject obj){
    return JavaUtilMapEntry(QAndroidJniObject::fromLocalRef(obj));
}

template <>
JavaUtilMapEntry JavaLangObject::fromClass<JavaUtilMapEntry>(QString const &className, const char *sig, ...){
    QAndroidJniEnvironment env;
    jclass javaCllass = env.findClass(className.toLatin1().data());
    va_list args;
    va_start(args, sig);
    QAndroidJniObject jniObject(javaCllass, sig, args);
    va_end(args);
    return JavaUtilMapEntry(jniObject);
}


template <>
JavaUtilMapEntry JavaLangObject::fromClass<JavaUtilMapEntry>(QString const &className){
    QAndroidJniEnvironment env;
    jclass javaCllass = env.findClass(className.toLatin1().data());
    QAndroidJniObject jniObject(javaCllass);
    return JavaUtilMapEntry(jniObject);
}
