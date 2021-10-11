#include "qtchannelmessage.h"


const QString QtChannelMessage::JavaClassName = "[com/qt/plugin/core/QtChannelMessage;";

QList<JavaLangObject> QtChannelMessage::getData() const{
    char * signature =  JniMethodBuilder::builder()
            ->returnType(JniMethodBuilder::JavaClassNameList)
            ->build();
    QAndroidJniObject obj = this->jniObj->callObjectMethod("getData", signature);
    JavaUtilList jlist = JavaUtilList(obj);
    return jlist.toArray();
}

JavaLangObject QtChannelMessage::getFirstData() const{
    char * signature =  JniMethodBuilder::builder()
            ->returnObject()
            ->build();
    jobject obj = this->jniObj->callMethod<jobject>("getFirstData", signature);
    return JavaLangObject::fromLocalRef<JavaLangObject>(obj);
}

JavaLangObject QtChannelMessage::getData(int const &index) const{
    char * signature =  JniMethodBuilder::builder()
            ->argInt()
            ->returnObject()
            ->build();
    jobject obj = this->jniObj->callMethod<jobject>("getData", signature, jint(index));
    return JavaLangObject::fromLocalRef<JavaLangObject>(obj);
}

void QtChannelMessage::setId(QString const &id) const{
    char * signature =  JniMethodBuilder::builder()->argString()->build();
    QAndroidJniObject javaString = QAndroidJniObject::fromString(id);
    this->jniObj->callMethod<jobject>("setId", signature, javaString.object<jstring>());
}

QString QtChannelMessage::getId() const{
    jstring str = this->jniObj->callMethod<jstring>("getId");
    QAndroidJniEnvironment env;
    return env->GetStringUTFChars(str, nullptr);
}

void QtChannelMessage::setMethodName(QString const &methodName) const{
    char * signature =  JniMethodBuilder::builder()->argString()->build();
    QAndroidJniObject javaString = QAndroidJniObject::fromString(methodName);
    this->jniObj->callMethod<jobject>("setMethodName", signature, javaString.object<jstring>());
}

QString QtChannelMessage::getMethodName() const{
    jstring str = this->jniObj->callMethod<jstring>("getMethodName");
    QAndroidJniEnvironment env;
    return env->GetStringUTFChars(str, nullptr);
}

void QtChannelMessage::setChannelName(QString const &channelName) const{
    char * signature =  JniMethodBuilder::builder()->argString()->build();
    QAndroidJniObject javaString = QAndroidJniObject::fromString(channelName);
    this->jniObj->callMethod<jobject>("setChannelName", signature, javaString.object<jstring>());
}

QString QtChannelMessage::getChannelName() const{
    jstring str = this->jniObj->callMethod<jstring>("getChannelName");
    QAndroidJniEnvironment env;
    return env->GetStringUTFChars(str, nullptr);
}

bool QtChannelMessage::hasError() const{
    return this->jniObj->callMethod<jboolean>("hasError");
}

bool QtChannelMessage::hasThrowable() const{
    return this->jniObj->callMethod<jboolean>("hasThrowable");
}

JavaLangThrowable QtChannelMessage::getThrowable() const{
    jobject obj = this->jniObj->callMethod<jobject>("getThrowable");
    return JavaLangObject::fromLocalRef<JavaLangThrowable>(obj);
}

QString QtChannelMessage::getErrorDescription() const{
    jstring str = this->jniObj->callMethod<jstring>("getErrorDescription");
    return JavaLangObject::convertJavaString(str);
}

void QtChannelMessage::addArg(JavaLangObject &arg) const{
    char * signature =  JniMethodBuilder::builder()->argObject()->build();
    this->jniObj->callMethod<jobject>("addArg", signature, arg.object()->object());
}

QtChannelMessage * QtChannelMessage::withArg(JavaLangObject &arg){
    this->addArg(arg);
    return this;
}

QString QtChannelMessage::dump() const{
    jstring str = this->jniObj->callMethod<jstring>("dump");
    return JavaLangObject::convertJavaString(str);
}

QtChannelMessage newJavaObject(){
    QAndroidJniObject javaObj("com/qt/plugin/core/QtChannelMessage");
    QtChannelMessage message = QtChannelMessage(javaObj);
    return message;
}

QtChannelMessage newJavaObject(QString const &channelName, QString const &methodName){
    QtChannelMessage message = QtChannelMessage::newJavaObject();
    message.setChannelName(channelName);
    message.setMethodName(methodName);
    return message;
}

template <>
QtChannelMessage JavaLangObject::fromLocalRef<QtChannelMessage>(jobject obj){
    return QtChannelMessage(QAndroidJniObject::fromLocalRef(obj));
}
