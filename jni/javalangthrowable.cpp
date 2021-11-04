#include "javalangthrowable.h"

JavaLangThrowable::JavaLangThrowable(QAndroidJniObject obj) {
    this->_jniObj = obj;
}

QAndroidJniObject JavaLangThrowable::getJniObject(){
    return this->_jniObj;
}

QString JavaLangThrowable::getMessage(){
    QAndroidJniObject javaObj = this->_jniObj.callObjectMethod<jstring>("getMessage");
    return javaObj.toString();

}

QString JavaLangThrowable::getStackTrace(){

    JavaLangObject javaStringWriter = JavaLangObject::fromClass("java/io/StringWriter");

    JniMethodBuilder* builer = new JniMethodBuilder();
    const char* signature =  builer->arg("Ljava/io/Writer;")->buildConstructor();

    JavaLangObject javaStringPrinter = JavaLangObject::fromClass("java/io/PrintWriter",
                                                                 signature,
                                                                 javaStringWriter.getJavaObject());

    this->_jniObj.callObjectMethod(
                "printStackTrace",
                builer->empty()->arg("Ljava/io/PrintStream")->build(),
                javaStringPrinter.getJavaObject());

    return javaStringWriter.toString();
}

JavaLangThrowable fromLocalRef(jobject obj){
    return JavaLangThrowable(QAndroidJniObject::fromLocalRef(obj));
}

