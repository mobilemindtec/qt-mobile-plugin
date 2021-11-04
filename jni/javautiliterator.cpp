#include "javautiliterator.h"

bool JavaUtilIterator::hasNext(){
    return this->getJniObject().callMethod<jboolean>("hasNext");
}

void JavaUtilIterator::remove(){
    this->getJniObject().callMethod<void>("remove");
}

JavaLangObject JavaUtilIterator::next(){
    QAndroidJniObject javaObject = this->getJniObject().callObjectMethod<jobject>("next");
    return JavaLangObject(javaObject);
}
