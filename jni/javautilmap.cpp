#include "javautilmap.h"


void JavaUtilMap::clear(){
    return this->getJniObject().callMethod<void>("clear");
}

bool JavaUtilMap::isEmpty(){
    return this->getJniObject().callMethod<jboolean>("isEmpty");
}

int JavaUtilMap::size(){
    return this->getJniObject().callMethod<jint>("size");
}

JavaUtilSet JavaUtilMap::keySet(){
    auto signature =  JniMethodBuilder::builder()
            ->returnTypedObject(kJavaUtilSet)
            ->build();
    QJniObject javaObject = this->getJniObject().callObjectMethod("keySet", signature.toLocal8Bit().constData());
    return JavaLangObject(javaObject);
}

QList<JavaUtilMapEntry> JavaUtilMap::entrySet(){

    QList<JavaUtilMapEntry> list;

    auto signature =  JniMethodBuilder::builder()
            ->returnTypedObject(kJavaUtilSet)
            ->build();
    QJniObject javaObject = this->getJniObject().callObjectMethod("entrySet", signature.toLocal8Bit().constData());
    JavaUtilSet javaSet = JavaLangObject(javaObject);

    QList<JavaLangObject> items = javaSet.toArray();

    for(auto&& it : items){
        list.append(it);
    }

    return list;

}

QList<JavaLangObject> JavaUtilMap::values(){

    auto signature =  JniMethodBuilder::builder()
            ->returnTypedObject(kJavaUtilCollection)
            ->build();
    QJniObject javaObject = this->getJniObject().callObjectMethod("values", signature.toLocal8Bit().constData());
    JavaUtilCollection javaCollection = JavaLangObject(javaObject);

    return javaCollection.toArray();
}

JavaLangObject JavaUtilMap::get(JavaLangObject &key){
    auto signature =  JniMethodBuilder::builder()
            ->returnTypedObject(kJavaLangObject)
            ->arg<jobject>()
            ->build();
    QJniObject javaObject = this->getJniObject().callObjectMethod("get", signature.toLocal8Bit().constData(), key.getJavaObject());
    return JavaLangObject(javaObject);
}

JavaLangObject JavaUtilMap::get(QString const &key){
    auto signature =  JniMethodBuilder::builder()
            ->returnTypedObject(kJavaLangObject)
            ->arg<jobject>()
            ->build();
    QJniObject javaObject = this->getJniObject().callObjectMethod("get", signature.toLocal8Bit().constData(), QJniObject::fromString(key).object<jstring>());
    return JavaLangObject(javaObject);
}

JavaLangObject JavaUtilMap::remove(JavaLangObject &key){
    auto signature =  JniMethodBuilder::builder()
            ->returnTypedObject(kJavaLangObject)
            ->arg<jobject>()
            ->build();
    QJniObject javaObject = this->getJniObject().callObjectMethod("remove", signature.toLocal8Bit().constData(), key.getJavaObject());
    return JavaLangObject(javaObject);
}

JavaLangObject JavaUtilMap::remove(const QString& key){
    auto signature =  JniMethodBuilder::builder()
            ->returnTypedObject(kJavaLangObject)
            ->arg<jobject>()
            ->build();
    QJniObject javaObject = this->getJniObject().callObjectMethod("remove", signature.toLocal8Bit().constData(), QJniObject::fromString(key).object<jstring>());
    return JavaLangObject(javaObject);
}

void JavaUtilMap::put(JavaLangObject &key, JavaLangObject &value){
    auto signature =  JniMethodBuilder::builder()
            ->arg<jobject>()
            ->arg<jobject>()
            ->build();
    this->getJniObject().callMethod<void>("put", signature.toLocal8Bit().constData(), key.getJavaObject(), value.getJavaObject());
}

void JavaUtilMap::put(JavaLangObject &key, QString const &value){
    auto signature =  JniMethodBuilder::builder()
            ->arg<jobject>()
            ->arg<jobject>()
            ->build();
    this->getJniObject().callMethod<void>("put", signature.toLocal8Bit().constData(), key.getJavaObject(), QJniObject::fromString(value).object<jstring>());
}

void JavaUtilMap::put(JavaLangObject &key, int const &value){
    auto signature =  JniMethodBuilder::builder()
            ->arg<jobject>()
            ->arg<jobject>()
            ->build();
    this->getJniObject().callMethod<void>("put", signature.toLocal8Bit().constData(), key.getJavaObject(), value);
}

void JavaUtilMap::put(JavaLangObject &key, long const &value){
    auto signature =  JniMethodBuilder::builder()
            ->arg<jobject>()
            ->arg<jobject>()
            ->build();
    this->getJniObject().callMethod<void>("put", signature.toLocal8Bit().constData(), key.getJavaObject(), value);
}

void JavaUtilMap::put(JavaLangObject &key, bool const &value){
    auto signature =  JniMethodBuilder::builder()
            ->arg<jobject>()
            ->arg<jobject>()
            ->build();
    this->getJniObject().callMethod<void>("put", signature.toLocal8Bit().constData(), key.getJavaObject(), value);
}

void JavaUtilMap::put(JavaLangObject &key, double const &value){
    auto signature =  JniMethodBuilder::builder()
            ->arg<jobject>()
            ->arg<jobject>()
            ->build();
    this->getJniObject().callMethod<void>("put", signature.toLocal8Bit().constData(), key.getJavaObject(), value);
}

void JavaUtilMap::put(JavaLangObject &key, float const &value){
    auto signature =  JniMethodBuilder::builder()
            ->arg<jobject>()
            ->arg<jobject>()
            ->build();
    this->getJniObject().callMethod<void>("put", signature.toLocal8Bit().constData(), key.getJavaObject(), value);
}

void JavaUtilMap::put(QString const &key, JavaLangObject &value){
    auto signature =  JniMethodBuilder::builder()
            ->arg<jobject>()
            ->arg<jobject>()
            ->build();
    this->getJniObject().callMethod<void>("put", signature.toLocal8Bit().constData(), QJniObject::fromString(key).object<jstring>(), value.getJavaObject());
}

void JavaUtilMap::put(QString const &key, QString const &value){
    auto signature =  JniMethodBuilder::builder()
            ->arg<jobject>()
            ->arg<jobject>()
            ->build();
    this->getJniObject().callMethod<void>("put", signature.toLocal8Bit().constData(), QJniObject::fromString(key).object<jstring>(), QJniObject::fromString(value).object<jstring>());
}

void JavaUtilMap::put(QString const &key, int const &value){
    auto signature =  JniMethodBuilder::builder()
            ->arg<jobject>()
            ->arg<jobject>()
            ->build();
    this->getJniObject().callMethod<void>("put", signature.toLocal8Bit().constData(), QJniObject::fromString(key).object<jstring>(), value);
}

void JavaUtilMap::put(QString const &key, long const &value){
    auto signature =  JniMethodBuilder::builder()
            ->arg<jobject>()
            ->arg<jobject>()
            ->build();
    this->getJniObject().callMethod<void>("put", signature.toLocal8Bit().constData(), QJniObject::fromString(key).object<jstring>(), value);
}

void JavaUtilMap::put(QString const &key, bool const &value){
    auto signature =  JniMethodBuilder::builder()
            ->arg<jobject>()
            ->arg<jobject>()
            ->build();
    this->getJniObject().callMethod<void>("put", signature.toLocal8Bit().constData(), QJniObject::fromString(key).object<jstring>(), value);
}

void JavaUtilMap::put(QString const &key, double const &value){
    auto signature =  JniMethodBuilder::builder()
            ->arg<jobject>()
            ->arg<jobject>()
            ->build();
    this->getJniObject().callMethod<void>("put", signature.toLocal8Bit().constData(), QJniObject::fromString(key).object<jstring>(), value);
}

void JavaUtilMap::put(QString const &key, float const &value){
    auto signature =  JniMethodBuilder::builder()
            ->arg<jobject>()
            ->arg<jobject>()
            ->build();
    this->getJniObject().callMethod<void>("put", signature.toLocal8Bit().constData(), QJniObject::fromString(key).object<jstring>(), value);
}

JavaUtilMap JavaUtilMap::newObject() {
    return JavaUtilMap::fromClass(kJavaUtilMap.toLocal8Bit().constData());
}
