#include "javalangobject.h"
#include "javalangthrowable.h"

/*
 * java.lang.Object
 */

JavaLangObject::JavaLangObject() : QObject(nullptr){

}

JavaLangObject::JavaLangObject(QString const &errorMessage) : QObject(nullptr){
    this->_error = true;
    this->_errorMessage = errorMessage;
}

JavaLangObject::JavaLangObject(jobject obj) : JavaLangObject(QAndroidJniObject::fromLocalRef(obj)){

}

JavaLangObject::JavaLangObject(QAndroidJniObject jniObj) : QObject(nullptr)
{
    if(jniObj != NULL){
        this->_jniObject = jniObj;

        if(!this->_jniObject.isValid()){
            this->_error = true;
            this->_errorMessage = "Invalid object";
        }

        this->exceptionCheck();
    }

}

JavaLangObject::~JavaLangObject(){
    //delete this->_jniObject;
}

QAndroidJniObject JavaLangObject::getJniObject(){
    return this->_jniObject;
}

void JavaLangObject::setJniObject(QAndroidJniObject o){
    this->_jniObject = o;
}

jobject JavaLangObject::getJavaObject(){
    return this->_jniObject.object();
}

bool JavaLangObject::error(){
    return this->_error;
}

QString JavaLangObject::getErrorMessage(){
    return this->_errorMessage;
}

QString JavaLangObject::toString(){
    return this->_jniObject.toString();
}

JavaLangObject JavaLangObject::fromLocalRef(jobject obj){
    return JavaLangObject(QAndroidJniObject::fromLocalRef(obj));
}

JavaLangObject JavaLangObject::fromClass(QString const &className, const char *sig, ...){
    QAndroidJniEnvironment env;
    jclass javaCllass = env.findClass(className.toLocal8Bit().constData());
    va_list args;
    va_start(args, sig);
    QAndroidJniObject jniObject(javaCllass, sig, args);
    va_end(args);
    return JavaLangObject(jniObject);
}

JavaLangObject JavaLangObject::fromClass(QString const &className){
    QAndroidJniEnvironment env;
    jclass javaCllass = env.findClass(className.toLocal8Bit().constData());
    QAndroidJniObject jniObject(javaCllass);
    return JavaLangObject(jniObject);
}


void JavaLangObject::exceptionCheck(){
    QAndroidJniEnvironment env;

    if(env->ExceptionCheck()){
        env->ExceptionDescribe();
        JavaLangThrowable throwable = JavaLangThrowable(QAndroidJniObject::fromLocalRef(env->ExceptionOccurred()));
        this->_error = true;
        this->_errorMessage = throwable.getStackTrace();

        qDebug() << "Object error: " << this->_errorMessage;
    }

    if(this->_jniObject != NULL){
        qDebug() << "is valid " << this->_jniObject.isValid() << " - ";
    }
}

QString JavaLangObject::toQString(jstring const &str){
    return QAndroidJniObject::fromLocalRef(str).toString();
}

char* JavaLangObject::toChar(QString const &str) {
    return str.toLocal8Bit().data();
}

