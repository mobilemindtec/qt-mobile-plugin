#include "javautilmap.h"


void JavaUtilMap::clear(){
    return this->jniObj->callMethod<void>("clear");
}

bool JavaUtilMap::isEmpty(){
    return this->jniObj->callMethod<jboolean>("isEmpty");
}

int JavaUtilMap::size(){
    return this->jniObj->callMethod<jint>("size");
}

JavaUtilSet JavaUtilMap::keySet(){
    char * signature =  JniMethodBuilder::builder()
            ->returnType(JniMethodBuilder::JavaClassNameSet)
            ->build();
    jobject javaObject = this->jniObj->callMethod<jobject>("keySet", signature);
    return JavaLangObject::fromLocalRef<JavaUtilSet>(javaObject);
}

QSet<JavaUtilMapEntry> JavaUtilMap::entrySet(){

    QSet<JavaUtilMapEntry> set;

    char * signature =  JniMethodBuilder::builder()
            ->returnType(JniMethodBuilder::JavaClassNameSet)
            ->build();
    jobject javaObject = this->jniObj->callMethod<jobject>("entrySet", signature);
    JavaUtilSet javaSet = JavaLangObject::fromLocalRef<JavaUtilSet>(javaObject);

    QList<JavaLangObject> items = javaSet.toArray();

    for(JavaLangObject it : items){
        set << it.cast<JavaUtilMapEntry>();
    }

    return set;

}

QList<JavaLangObject> JavaUtilMap::values(){

    char * signature =  JniMethodBuilder::builder()
            ->returnType(JniMethodBuilder::JavaClassNameCollection)
            ->build();
    jobject javaObject = this->jniObj->callMethod<jobject>("values", signature);
    JavaUtilCollection javaCollection = JavaLangObject::fromLocalRef<JavaUtilCollection>(javaObject);

    return javaCollection.toArray();
}

JavaLangObject JavaUtilMap::get(JavaLangObject key){
    char * signature =  JniMethodBuilder::builder()
            ->returnType(JniMethodBuilder::JavaClassNameObject)
            ->argObject()
            ->build();
    jobject javaObject = this->jniObj->callMethod<jobject>("get", signature, key.object());
    return JavaLangObject::fromLocalRef<JavaLangObject>(javaObject);
}

JavaLangObject JavaUtilMap::remove(JavaLangObject key){
    char * signature =  JniMethodBuilder::builder()
            ->returnType(JniMethodBuilder::JavaClassNameObject)
            ->argObject()
            ->build();
    jobject javaObject = this->jniObj->callMethod<jobject>("remove", signature, key.object());
    return JavaLangObject::fromLocalRef<JavaLangObject>(javaObject);
}

void JavaUtilMap::put(JavaLangObject key, JavaLangObject value){
    char * signature =  JniMethodBuilder::builder()
            ->argObject()
            ->argObject()
            ->build();
    this->jniObj->callMethod<void>("put", signature, key.object(), value.object());
}

template <>
JavaUtilMap JavaLangObject::fromLocalRef<JavaUtilMap>(jobject obj){
    return JavaUtilMap(QAndroidJniObject::fromLocalRef(obj));
}

template <>
JavaUtilMap JavaLangObject::fromClass<JavaUtilMap>(QString const &className, const char *sig, ...){
    QAndroidJniEnvironment env;
    jclass javaCllass = env.findClass(className.toLatin1().data());
    va_list args;
    va_start(args, sig);
    QAndroidJniObject jniObject(javaCllass, sig, args);
    va_end(args);
    return JavaUtilMap(jniObject);
}

template <>
JavaUtilMap JavaLangObject::fromClass<JavaUtilMap>(QString const &className){
    QAndroidJniEnvironment env;
    jclass javaCllass = env.findClass(className.toLatin1().data());
    QAndroidJniObject jniObject(javaCllass);
    return JavaUtilMap(jniObject);
}
