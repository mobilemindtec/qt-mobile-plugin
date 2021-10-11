#include "javautiliterator.h"


bool JavaUtilIterator::hasNext(){
    return this->jniObj->callMethod<jboolean>("hasNext");
}

void JavaUtilIterator::remove(){
    this->jniObj->callObjectMethod<void>("remove");
}

JavaLangObject JavaUtilIterator::next(){
    jobject javaObject = this->jniObj->callMethod<jobject>("next");
    return JavaLangObject::fromLocalRef<JavaLangObject>(javaObject);
}


template <>
JavaUtilIterator JavaLangObject::fromLocalRef<JavaUtilIterator>(jobject obj){
    return JavaUtilIterator(QAndroidJniObject::fromLocalRef(obj));
}

template <>
JavaUtilIterator JavaLangObject::fromClass<JavaUtilIterator>(QString const &className, const char *sig, ...){
    QAndroidJniEnvironment env;
    jclass javaCllass = env.findClass(className.toLatin1().data());
    va_list args;
    va_start(args, sig);
    QAndroidJniObject jniObject(javaCllass, sig, args);
    va_end(args);
    return JavaUtilIterator(jniObject);
}

template <>
JavaUtilIterator JavaLangObject::fromClass<JavaUtilIterator>(QString const &className){
    QAndroidJniEnvironment env;
    jclass javaCllass = env.findClass(className.toLatin1().data());
    QAndroidJniObject jniObject(javaCllass);
    return JavaUtilIterator(jniObject);
}
