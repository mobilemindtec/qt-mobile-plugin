#include "javautilcollection.h"


int JavaUtilCollection::size(){
    return this->getJniObject().callMethod<jboolean>("size");
}

bool JavaUtilCollection::remove(JavaLangObject &obj){
    auto signature =  JniMethodBuilder::builder()->returnType<bool>()->arg<jobject>()->build();
    return this->getJniObject().callMethod<jboolean>("remove", signature.toLocal8Bit().constData(), obj.getJavaObject());
}

bool JavaUtilCollection::contains(JavaLangObject &obj){
    auto signature =  JniMethodBuilder::builder()->returnType<bool>()->arg<jobject>()->build();
    return this->getJniObject().callMethod<jboolean>("contains", signature.toLocal8Bit().constData(), obj.getJavaObject());
}

bool JavaUtilCollection::isEmpty(){
    return this->getJniObject().callMethod<jboolean>("isEmpty");
}

void JavaUtilCollection::clear(){
    this->getJniObject().callMethod<void>("clear");
}

void JavaUtilCollection::add(JavaLangObject &obj){
    auto signature =  JniMethodBuilder::builder()->arg<jobject>()->build();
    this->getJniObject().callMethod<void>("add", signature.toLocal8Bit().constData(), obj.getJavaObject());
}

JavaUtilIterator JavaUtilCollection::iterator(){
    auto signature =  JniMethodBuilder::builder()->returnTypedObject(kJavaUtilIterator)->build();
    qDebug() << "toString " << this->getJniObject().toString();
    QJniObject javaObject = this->getJniObject().callObjectMethod("iterator", signature.toLocal8Bit().constData());

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
