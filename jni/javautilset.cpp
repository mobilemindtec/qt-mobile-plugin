#include "javautilset.h"

template <>
JavaUtilSet JavaLangObject::fromLocalRef<JavaUtilSet>(jobject obj){
    return JavaUtilSet(QAndroidJniObject::fromLocalRef(obj));
}

template <>
JavaUtilSet JavaLangObject::fromClass<JavaUtilSet>(QString const &className, const char *sig, ...){
    QAndroidJniEnvironment env;
    jclass javaCllass = env.findClass(className.toLatin1().data());
    va_list args;
    va_start(args, sig);
    QAndroidJniObject jniObject(javaCllass, sig, args);
    va_end(args);
    return JavaUtilSet(jniObject);
}

template <>
JavaUtilSet JavaLangObject::fromClass<JavaUtilSet>(QString const &className){
    QAndroidJniEnvironment env;
    jclass javaCllass = env.findClass(className.toLatin1().data());
    QAndroidJniObject jniObject(javaCllass);
    return JavaUtilSet(jniObject);
}
