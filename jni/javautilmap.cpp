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
    const char* signature =  JniMethodBuilder::builder()
            ->returnTypedObject(JniMethodBuilder::kJavaClassNameSet)
            ->build();
    QAndroidJniObject javaObject = this->getJniObject().callObjectMethod("keySet", signature);
    return JavaLangObject(javaObject);
}

QList<JavaUtilMapEntry> JavaUtilMap::entrySet(){

    QList<JavaUtilMapEntry> list;

    const char* signature =  JniMethodBuilder::builder()
            ->returnTypedObject(JniMethodBuilder::kJavaClassNameSet)
            ->build();
    QAndroidJniObject javaObject = this->getJniObject().callObjectMethod("entrySet", signature);
    JavaUtilSet javaSet = JavaLangObject(javaObject);

    QList<JavaLangObject> items = javaSet.toArray();

    for(JavaUtilMapEntry it : items){
        list.append(it);
    }

    return list;

}

QList<JavaLangObject> JavaUtilMap::values(){

    const char* signature =  JniMethodBuilder::builder()
            ->returnTypedObject(JniMethodBuilder::kJavaClassNameCollection)
            ->build();
    QAndroidJniObject javaObject = this->getJniObject().callObjectMethod("values", signature);
    JavaUtilCollection javaCollection = JavaLangObject(javaObject);

    return javaCollection.toArray();
}

JavaLangObject JavaUtilMap::get(JavaLangObject &key){
    const char* signature =  JniMethodBuilder::builder()
            ->returnTypedObject(JniMethodBuilder::kJavaClassNameObject)
            ->arg<jobject>()
            ->build();
    QAndroidJniObject javaObject = this->getJniObject().callObjectMethod("get", signature, key.getJavaObject());
    return JavaLangObject(javaObject);
}

JavaLangObject JavaUtilMap::remove(JavaLangObject &key){
    const char* signature =  JniMethodBuilder::builder()
            ->returnTypedObject(JniMethodBuilder::kJavaClassNameObject)
            ->arg<jobject>()
            ->build();
    QAndroidJniObject javaObject = this->getJniObject().callObjectMethod("remove", signature, key.getJavaObject());
    return JavaLangObject(javaObject);
}

void JavaUtilMap::put(JavaLangObject &key, JavaLangObject &value){
    const char* signature =  JniMethodBuilder::builder()
            ->arg<jobject>()
            ->arg<jobject>()
            ->build();
    this->getJniObject().callMethod<void>("put", signature, key.getJavaObject(), value.getJavaObject());
}
