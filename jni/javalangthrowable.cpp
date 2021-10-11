#include "javalangthrowable.h"

JavaLangThrowable::JavaLangThrowable(QAndroidJniObject obj) {
    this->jniObj = obj;
}

QAndroidJniObject JavaLangThrowable::object(){
    return this->jniObj;
}

QString JavaLangThrowable::getMessage(){
    JniMethodBuilder* builer = new JniMethodBuilder();
    char * signature =  builer->returnString()->noArgs()->build();
    QAndroidJniObject javaObj = this->jniObj.callObjectMethod("getMessage", signature);
    return javaObj.toString();

}

QString JavaLangThrowable::getStackTrace(){
    JavaLangObject javaStringWriter = JavaLangObject::fromClass<JavaLangObject>("java/io/StringWriter");

    JniMethodBuilder* builer = new JniMethodBuilder();
    char* signature =  builer->arg("Ljava/io/Writer;")->buildConstructor();

    JavaLangObject javaStringPrinter = JavaLangObject::fromClass<JavaLangObject>("java/io/PrintWriter", signature, javaStringWriter.object());

    this->jniObj.callObjectMethod(
                "printStackTrace",
                builer->empty()->arg("Ljava/io/PrintStream")->build(),
                javaStringPrinter.object());

    return javaStringWriter.toString();
}

JavaLangThrowable fromLocalRef(jobject obj){
    return JavaLangThrowable(QAndroidJniObject::fromLocalRef(obj));
}

