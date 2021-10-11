#include "javalangobject.h"
#include "javalangthrowable.h"

/*
 * java.lang.Object
 */

JavaLangObject::JavaLangObject(){}
JavaLangObject::JavaLangObject(QString const &errorMessage){
    this->_error = true;
    this->_errorMessage = errorMessage;
}
JavaLangObject::JavaLangObject(QAndroidJniObject jniObj)
{
    this->jniObj = &jniObj;

    if(!this->jniObj->isValid()){
        this->_error = true;
        this->_errorMessage = "Invalid object";
    }

    this->exceptionCheck();

}

JavaLangObject::~JavaLangObject(){
    delete this->jniObj;
}

QAndroidJniObject* JavaLangObject::object(){
    return this->jniObj;
}

QString JavaLangObject::toString(){
    return this->jniObj->toString();
}

template <>
JavaLangObject JavaLangObject::fromLocalRef<JavaLangObject>(jobject obj){
    return JavaLangObject(QAndroidJniObject::fromLocalRef(obj));
}


void JavaLangObject::exceptionCheck(){
    QAndroidJniEnvironment env;

    if(env->ExceptionCheck()){
        env->ExceptionDescribe();
        JavaLangThrowable throwable = JavaLangThrowable::fromLocalRef(env->ExceptionOccurred());
        this->_error = true;
        this->_errorMessage = throwable.getStackTrace();
    }
}

QString convertJavaString(jstring const &str){
    QAndroidJniEnvironment env;
    return QString(env->GetStringUTFChars(str, nullptr));
}

