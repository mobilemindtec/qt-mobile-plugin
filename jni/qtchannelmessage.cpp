#include "qtchannelmessage.h"


const QString QtChannelMessage::kJavaClassName = "com/qt/plugin/core/QtChannelMessage";

QList<JavaLangObject> QtChannelMessage::getData(){
    const char* signature =  JniMethodBuilder::builder()
            ->returnTypedObject(JniMethodBuilder::kJavaClassNameList)
            ->build();
    QAndroidJniObject obj = this->getJniObject().callObjectMethod("getData", signature);
    JavaUtilList * jlist = new JavaUtilList(obj);
    return jlist->toArray();
}

JavaLangObject QtChannelMessage::getFirstData(){
    const char* signature =  JniMethodBuilder::builder()
            ->returnType<jobject>()
            ->build();
    return this->getData(0, signature);
}

JavaLangObject QtChannelMessage::getData(int const &index){
    const char* signature =  JniMethodBuilder::builder()
            ->arg<int>()
            ->returnType<jobject>()
            ->build();
    return this->getData(index, signature);
}

JavaLangObject QtChannelMessage::getData(int const &index, const char* methodSignature){
    QAndroidJniObject obj = this->getJniObject().callObjectMethod("getData", methodSignature, jint(index));
    qDebug() << "getData " << obj.isValid();
    return JavaLangObject(obj);
}

void QtChannelMessage::setId(QString const &id){
    const char* signature =  JniMethodBuilder::builder()->arg<jstring>()->build();
    QAndroidJniObject javaString = QAndroidJniObject::fromString(id);
    this->getJniObject().callMethod<void>("setId", signature, javaString.object<jstring>());
}

QString QtChannelMessage::getId(){
    QAndroidJniObject str = this->getJniObject().callObjectMethod<jstring>("getId");
    return str.toString();
}

void QtChannelMessage::setMethodName(QString const &methodName){
    const char* signature =  JniMethodBuilder::builder()->arg<jstring>()->build();
    QAndroidJniObject jstr = QAndroidJniObject::fromString(methodName);
    this->getJniObject().callMethod<void>("setMethodName", signature, jstr.object<jstring>());
}

QString QtChannelMessage::getMethodName(){
    QAndroidJniObject str = this->getJniObject().callObjectMethod<jstring>("getMethodName");
    return str.toString();
}

void QtChannelMessage::setChannelName(QString const &channelName){
    const char* signature =  JniMethodBuilder::builder()->arg<jstring>()->build();    
    QAndroidJniObject jstr = QAndroidJniObject::fromString(channelName);
    this->getJniObject().callMethod<void>("setChannelName", signature, jstr.object<jstring>());
}

QString QtChannelMessage::getChannelName(){
    QAndroidJniObject str = this->getJniObject().callObjectMethod<jstring>("getChannelName");
    return str.toString();
}

bool QtChannelMessage::hasError(){
    return this->getJniObject().callMethod<jboolean>("hasError");
}

bool QtChannelMessage::hasThrowable(){
    return this->getJniObject().callMethod<jboolean>("hasThrowable");
}

JavaLangThrowable QtChannelMessage::getThrowable(){
    QAndroidJniObject obj = this->getJniObject().callObjectMethod<jobject>("getThrowable");
    return JavaLangThrowable(obj);
}

QString QtChannelMessage::getErrorDescription(){
    QAndroidJniObject str = this->getJniObject().callObjectMethod<jstring>("getErrorDescription");
    return str.toString();
}

void QtChannelMessage::addArg(JavaLangObject &arg){
    const char* signature =  JniMethodBuilder::builder()->arg<jobject>()->build();
    this->getJniObject().callMethod<void>("addArg", signature, arg.getJavaObject());
}

QtChannelMessage* QtChannelMessage::withArg(JavaLangObject &arg){
    this->addArg(arg);
    return this;
}

QtChannelMessage* QtChannelMessage::withArg(QString const &arg){
    QAndroidJniObject javaString = QAndroidJniObject::fromString(arg);
    JavaLangObject javaObj(javaString);
    this->addArg(javaObj);
    return this;
}

QString QtChannelMessage::dump(){
    QAndroidJniObject str = this->getJniObject().callObjectMethod<jstring>("dump");
    return str.toString();
}

QtChannelMessage* QtChannelMessage::newJavaObject(){
    QAndroidJniObject javaObj(JavaLangObject::toChar(QtChannelMessage::kJavaClassName));
    QtChannelMessage*  message = new QtChannelMessage(javaObj);
    return message;
}

QtChannelMessage* QtChannelMessage::newJavaObject(QString const &channelName, QString const &methodName){
    QtChannelMessage* message = QtChannelMessage::newJavaObject();
    message->setChannelName(channelName);
    message->setMethodName(methodName);
    return message;
}
