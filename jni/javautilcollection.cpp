#include "javautilcollection.h"

int JavaUtilCollection::size(){
    return this->getJniObject().callMethod<jboolean>("size");
}

bool JavaUtilCollection::remove(JavaLangObject &obj){
    const char* signature =  JniMethodBuilder::builder()->returnType<bool>()->arg<jobject>()->build();
    return this->getJniObject().callMethod<jboolean>("remove", signature, obj.getJavaObject());
}

bool JavaUtilCollection::contains(JavaLangObject &obj){
    const char* signature =  JniMethodBuilder::builder()->returnType<bool>()->arg<jobject>()->build();
    return this->getJniObject().callMethod<jboolean>("contains", signature, obj.getJavaObject());
}

bool JavaUtilCollection::isEmpty(){
    return this->getJniObject().callMethod<jboolean>("isEmpty");
}

void JavaUtilCollection::clear(){
    this->getJniObject().callMethod<void>("clear");
}

void JavaUtilCollection::add(JavaLangObject &obj){
    const char* signature =  JniMethodBuilder::builder()->arg<jobject>()->build();
    this->getJniObject().callMethod<void>("add", signature, obj.getJavaObject());
}

JavaUtilIterator JavaUtilCollection::iterator(){
    const char* signature =  JniMethodBuilder::builder()->returnTypedObject(JniMethodBuilder::kJavaClassNameIterator)->build();
    qDebug() << "toString " << this->getJniObject().toString();
    QAndroidJniObject javaObject = this->getJniObject().callObjectMethod("iterator", signature);

    return JavaLangObject(javaObject);
}

QList<JavaLangObject> JavaUtilCollection::toArray(){
    JavaUtilIterator it = this->iterator();
    QList<JavaLangObject> results;
    while(it.hasNext()){
        results.append(it.next());
    }
    return results;
}
