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

JavaLangObject::JavaLangObject(jobject obj) : JavaLangObject(QJniObject::fromLocalRef(obj)){

}

JavaLangObject::JavaLangObject(QJniObject jniObj) : QObject(nullptr)
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

QJniObject JavaLangObject::getJniObject(){
    return this->_jniObject;
}

void JavaLangObject::setJniObject(QJniObject o){
    this->_jniObject = o;
}

jobject JavaLangObject::getJavaObject(){
    return this->_jniObject.object();
}

bool JavaLangObject::error() const{
    return this->_error;
}

QString JavaLangObject::getErrorMessage() const{
    return this->_errorMessage;
}

QString JavaLangObject::toString(){
    return this->_jniObject.toString();
}

JavaLangObject JavaLangObject::fromString(QString const &str){
    return JavaLangObject(QJniObject::fromString(str));
}

JavaLangObject JavaLangObject::fromLocalRef(jobject obj){
    return JavaLangObject(QJniObject::fromLocalRef(obj));
}

JavaLangObject JavaLangObject::fromClass(QString const &className, const char *sig, ...){
    QJniEnvironment env;
    jclass javaCllass = env.findClass(className.toLocal8Bit().constData());
    va_list args;
    va_start(args, sig);
    QJniObject jniObject(javaCllass, sig, args);
    va_end(args);
    return JavaLangObject(jniObject);
}

JavaLangObject JavaLangObject::fromClass(QString const &className){
    QJniEnvironment env;
    jclass javaCllass = env.findClass(className.toLocal8Bit().constData());
    QJniObject jniObject(javaCllass);
    return JavaLangObject(jniObject);
}


void JavaLangObject::exceptionCheck(){
    QJniEnvironment env;

    if(env->ExceptionCheck()){
        env->ExceptionDescribe();
        JavaLangThrowable throwable = JavaLangThrowable(QJniObject::fromLocalRef(env->ExceptionOccurred()));
        this->_error = true;
        this->_errorMessage = throwable.getStackTrace();

        qDebug() << "Object error: " << this->_errorMessage;
    }

    if(this->_jniObject != NULL){
        qDebug() << "is valid " << this->_jniObject.isValid() << " - ";
    }
}

QString JavaLangObject::toQString(jstring const &str){
    return QJniObject::fromLocalRef(str).toString();
}

QString JavaLangObject::getJavaClassName(){
    return this->_jniObject.className();
}

bool JavaLangObject::isValidJavaInstace(){
    return this->_jniObject.isValid();
}


