#include "javautillist.h"

JavaLangObject JavaUtilList::get(int const &index)
{
    const char* signature =  JniMethodBuilder::builder()
            ->returnTypedObject(JniMethodBuilder::kJavaClassNameObject)
            ->arg<int>()
            ->build();
    QAndroidJniObject javaObject = this->getJniObject().callObjectMethod("get", signature, jint(index));
    return JavaLangObject(javaObject);
}
