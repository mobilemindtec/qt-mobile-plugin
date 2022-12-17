#include "javautillist.h"

JavaLangObject JavaUtilList::get(int const &index)
{
    auto signature =  JniMethodBuilder::builder()
            ->returnTypedObject(kJavaLangObject)
            ->arg<int>()
            ->build();
    QJniObject javaObject = this->getJniObject().callObjectMethod("get", signature.toLocal8Bit().constData(), jint(index));
    return JavaLangObject(javaObject);
}
