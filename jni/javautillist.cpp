#include "javautillist.h"

JavaLangObject JavaUtilList::get(int const &index)
{
    char * signature =  JniMethodBuilder::builder()
            ->returnType(JniMethodBuilder::JavaClassNameObject)
            ->argInt()
            ->build();
    jobject javaObject = this->jniObj->callMethod<jobject>("get", signature, jint(index));
    return JavaLangObject::fromLocalRef<JavaLangObject>(javaObject);
}


template <>
JavaUtilList JavaLangObject::fromLocalRef<JavaUtilList>(jobject obj){
    return JavaUtilList(QAndroidJniObject::fromLocalRef(obj));
}


template <>
JavaUtilList JavaLangObject::fromClass<JavaUtilList>(QString const &className, const char *sig, ...){
    QAndroidJniEnvironment env;
    jclass javaCllass = env.findClass(className.toLatin1().data());
    va_list args;
    va_start(args, sig);
    QAndroidJniObject jniObject(javaCllass, sig, args);
    va_end(args);
    return JavaUtilList(jniObject);
}

template <>
JavaUtilList JavaLangObject::fromClass<JavaUtilList>(QString const &className){
    QAndroidJniEnvironment env;
    jclass javaCllass = env.findClass(className.toLatin1().data());
    QAndroidJniObject jniObject(javaCllass);
    return JavaUtilList(jniObject);
}
