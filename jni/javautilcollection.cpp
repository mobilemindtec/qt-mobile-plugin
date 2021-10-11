#include "javautilcollection.h"



int JavaUtilCollection::size(){
    return this->jniObj->callMethod<jboolean>("size");
}

bool JavaUtilCollection::remove(JavaLangObject obj){
    char * signature =  JniMethodBuilder::builder()->returnArrayBoolean()->argObject()->build();
    return this->jniObj->callMethod<jboolean>("remove", signature, obj.object());
}

bool JavaUtilCollection::contains(JavaLangObject obj){
    char * signature =  JniMethodBuilder::builder()->returnArrayBoolean()->argObject()->build();
    return this->jniObj->callMethod<jboolean>("contains", signature, obj.object());
}

bool JavaUtilCollection::isEmpty(){
    return this->jniObj->callMethod<jboolean>("isEmpty");
}

void JavaUtilCollection::clear(){
    this->jniObj->callMethod<void>("clear");
}

void JavaUtilCollection::add(JavaLangObject obj){
    char * signature =  JniMethodBuilder::builder()->argObject()->build();
    this->jniObj->callMethod<void>("add", signature, obj.object());
}

JavaUtilIterator JavaUtilCollection::iterator(){
    char * signature =  JniMethodBuilder::builder()->returnType(JniMethodBuilder::JavaClassNameIterator)->build();
    jobject javaObject = this->jniObj->callMethod<jobject>("iterator", signature);
    return JavaLangObject::fromLocalRef<JavaUtilIterator>(javaObject);
}

QList<JavaLangObject> JavaUtilCollection::toArray(){
    JavaUtilIterator it = this->iterator();
    QList<JavaLangObject> results;
    while(it.hasNext()){
        results << it.next();
    }
    return results;
}

template <>
JavaUtilCollection JavaLangObject::fromLocalRef<JavaUtilCollection>(jobject obj){
    return JavaUtilCollection(QAndroidJniObject::fromLocalRef(obj));
}


template <>
JavaUtilCollection JavaLangObject::fromClass<JavaUtilCollection>(QString const &className, const char *sig, ...){
    QAndroidJniEnvironment env;
    jclass javaCllass = env.findClass(className.toLatin1().data());
    va_list args;
    va_start(args, sig);
    QAndroidJniObject jniObject(javaCllass, sig, args);
    va_end(args);
    return JavaUtilCollection(jniObject);
}

template <>
JavaUtilCollection JavaLangObject::fromClass<JavaUtilCollection>(QString const &className){
    QAndroidJniEnvironment env;
    jclass javaCllass = env.findClass(className.toLatin1().data());
    QAndroidJniObject jniObject(javaCllass);
    return JavaUtilCollection(jniObject);
}
