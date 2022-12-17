#include "javalangthrowable.h"

JavaLangThrowable::JavaLangThrowable(QJniObject obj) {
    this->_jniObj = obj;
}

QJniObject JavaLangThrowable::getJniObject(){
    return this->_jniObj;
}

QString JavaLangThrowable::getMessage() const{
    QJniObject javaObj = this->_jniObj.callObjectMethod<jstring>("getMessage");
    return javaObj.toString();

}

QString JavaLangThrowable::getStackTrace() const{

    JavaLangObject javaStringWriter = JavaLangObject::fromClass("java/io/StringWriter");

    QScopedPointer<JniMethodBuilder> builer(new JniMethodBuilder());
    auto signature =  builer->arg("Ljava/io/Writer;")->buildConstructor();

    JavaLangObject javaStringPrinter = JavaLangObject::fromClass("java/io/PrintWriter",
                                                                 signature.toLocal8Bit().constData(),
                                                                 javaStringWriter.getJavaObject());    

    this->_jniObj.callObjectMethod(
                "printStackTrace",
                builer->empty()->arg("Ljava/io/PrintStream")->build().toLocal8Bit().constData(),
                javaStringPrinter.getJavaObject());

    return javaStringWriter.toString();
}

JavaLangThrowable fromLocalRef(jobject obj){
    return JavaLangThrowable(QJniObject::fromLocalRef(obj));
}

