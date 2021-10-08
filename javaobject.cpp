#include "javaobject.h"
#include "support.h"

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

template <>
JavaUtilList JavaLangObject::fromLocalRef<JavaUtilList>(jobject obj){
    return JavaUtilList(QAndroidJniObject::fromLocalRef(obj));
}

template <>
JavaUtilSet JavaLangObject::fromLocalRef<JavaUtilSet>(jobject obj){
    return JavaUtilSet(QAndroidJniObject::fromLocalRef(obj));
}

template <>
JavaUtilCollection JavaLangObject::fromLocalRef<JavaUtilCollection>(jobject obj){
    return JavaUtilCollection(QAndroidJniObject::fromLocalRef(obj));
}

template <>
JavaUtilMap JavaLangObject::fromLocalRef<JavaUtilMap>(jobject obj){
    return JavaUtilMap(QAndroidJniObject::fromLocalRef(obj));
}

template <>
JavaUtilIterator JavaLangObject::fromLocalRef<JavaUtilIterator>(jobject obj){
    return JavaUtilIterator(QAndroidJniObject::fromLocalRef(obj));
}

template <>
JavaUtilMapEntry JavaLangObject::fromLocalRef<JavaUtilMapEntry>(jobject obj){
    return JavaUtilMapEntry(QAndroidJniObject::fromLocalRef(obj));
}

template <>
JavaLangThrowable JavaLangObject::fromLocalRef<JavaLangThrowable>(jobject obj){
    return JavaLangThrowable(QAndroidJniObject::fromLocalRef(obj));
}


template <>
JavaUtilList JavaLangObject::fromClass<JavaUtilList>(QString const &className, const char *sig, ...){
    QAndroidJniEnvironment env;
    jclass javaCllass = env.findClass(className.toLatin1().data());
    va_list args;
    va_start(args, sig);
    QAndroidJniObject jniObject(javaCllass, sig, args);
    va_end(args);
    return JavaUtilList(jniObject);
}

template <>
JavaUtilCollection JavaLangObject::fromClass<JavaUtilCollection>(QString const &className, const char *sig, ...){
    QAndroidJniEnvironment env;
    jclass javaCllass = env.findClass(className.toLatin1().data());
    va_list args;
    va_start(args, sig);
    QAndroidJniObject jniObject(javaCllass, sig, args);
    va_end(args);
    return JavaUtilCollection(jniObject);
}

template <>
JavaUtilIterator JavaLangObject::fromClass<JavaUtilIterator>(QString const &className, const char *sig, ...){
    QAndroidJniEnvironment env;
    jclass javaCllass = env.findClass(className.toLatin1().data());
    va_list args;
    va_start(args, sig);
    QAndroidJniObject jniObject(javaCllass, sig, args);
    va_end(args);
    return JavaUtilIterator(jniObject);
}

template <>
JavaUtilMap JavaLangObject::fromClass<JavaUtilMap>(QString const &className, const char *sig, ...){
    QAndroidJniEnvironment env;
    jclass javaCllass = env.findClass(className.toLatin1().data());
    va_list args;
    va_start(args, sig);
    QAndroidJniObject jniObject(javaCllass, sig, args);
    va_end(args);
    return JavaUtilMap(jniObject);
}

template <>
JavaUtilMapEntry JavaLangObject::fromClass<JavaUtilMapEntry>(QString const &className, const char *sig, ...){
    QAndroidJniEnvironment env;
    jclass javaCllass = env.findClass(className.toLatin1().data());
    va_list args;
    va_start(args, sig);
    QAndroidJniObject jniObject(javaCllass, sig, args);
    va_end(args);
    return JavaUtilMapEntry(jniObject);
}

template <>
JavaUtilSet JavaLangObject::fromClass<JavaUtilSet>(QString const &className, const char *sig, ...){
    QAndroidJniEnvironment env;
    jclass javaCllass = env.findClass(className.toLatin1().data());
    va_list args;
    va_start(args, sig);
    QAndroidJniObject jniObject(javaCllass, sig, args);
    va_end(args);
    return JavaUtilSet(jniObject);
}


// name

template <>
JavaUtilList JavaLangObject::fromClass<JavaUtilList>(QString const &className){
    QAndroidJniEnvironment env;
    jclass javaCllass = env.findClass(className.toLatin1().data());
    QAndroidJniObject jniObject(javaCllass);
    return JavaUtilList(jniObject);
}

template <>
JavaUtilCollection JavaLangObject::fromClass<JavaUtilCollection>(QString const &className){
    QAndroidJniEnvironment env;
    jclass javaCllass = env.findClass(className.toLatin1().data());
    QAndroidJniObject jniObject(javaCllass);
    return JavaUtilCollection(jniObject);
}

template <>
JavaUtilIterator JavaLangObject::fromClass<JavaUtilIterator>(QString const &className){
    QAndroidJniEnvironment env;
    jclass javaCllass = env.findClass(className.toLatin1().data());
    QAndroidJniObject jniObject(javaCllass);
    return JavaUtilIterator(jniObject);
}

template <>
JavaUtilMap JavaLangObject::fromClass<JavaUtilMap>(QString const &className){
    QAndroidJniEnvironment env;
    jclass javaCllass = env.findClass(className.toLatin1().data());
    QAndroidJniObject jniObject(javaCllass);
    return JavaUtilMap(jniObject);
}

template <>
JavaUtilMapEntry JavaLangObject::fromClass<JavaUtilMapEntry>(QString const &className){
    QAndroidJniEnvironment env;
    jclass javaCllass = env.findClass(className.toLatin1().data());
    QAndroidJniObject jniObject(javaCllass);
    return JavaUtilMapEntry(jniObject);
}

template <>
JavaUtilSet JavaLangObject::fromClass<JavaUtilSet>(QString const &className){
    QAndroidJniEnvironment env;
    jclass javaCllass = env.findClass(className.toLatin1().data());
    QAndroidJniObject jniObject(javaCllass);
    return JavaUtilSet(jniObject);
}

void JavaLangObject::exceptionCheck(){
    QAndroidJniEnvironment env;

    if(env->ExceptionCheck()){
        env->ExceptionDescribe();
        JavaLangThrowable throwable = JavaLangObject::fromLocalRef<JavaLangThrowable>(env->ExceptionOccurred());
        this->_error = true;
        this->_errorMessage = throwable.getStackTrace();
    }
}

/*
 * java.lang.Throwable
 */

QString JavaLangThrowable::getMessage(){
    JniMethodBuilder* builer = new JniMethodBuilder();
    QString signature =  builer->returnString()->noArgs()->build();
    QAndroidJniObject javaObj = this->jniObj->callObjectMethod("getMessage", signature.toLocal8Bit().data());
    return javaObj.toString();

}

QString JavaLangThrowable::getStackTrace(){
    JavaLangObject javaStringWriter = JavaLangObject::fromClass<JavaLangObject>("java/io/StringWriter");

    JniMethodBuilder* builer = new JniMethodBuilder();
    char* signature =  builer->arg("Ljava/io/Writer;")->buildConstructor();

    JavaLangObject javaStringPrinter = JavaLangObject::fromClass<JavaLangObject>("java/io/PrintWriter", signature, javaStringWriter.object());

    this->jniObj->callObjectMethod(
                "printStackTrace",
                builer->empty()->arg("Ljava/io/PrintStream")->build(),
                javaStringPrinter.object());

    return javaStringWriter.toString();
}

void JavaLangThrowable::exceptionCheck(){

}

/*
 * java.util.Iterator
 */

bool JavaUtilIterator::hasNext(){

}

void JavaUtilIterator::remove(){
    //this->object.callObjectMethod<jobject>("remove");
    //this->env->ExceptionOccurred()
}

JavaLangObject JavaUtilIterator::next(){
    //return this->object.callObjectMethod<jobject>("next");
}
