#include "qtmobilepluginchannelmessage.h"


const QString QtMobilePluginChannelMessage::kJavaClassName = "com/qt/plugin/core/QtMobilePluginChannelMessage";

QList<JavaLangObject> QtMobilePluginChannelMessage::getData(){
    auto signature =  JniMethodBuilder::builder()
            ->returnTypedObject(kJavaUtilList)
            ->build();
    QJniObject obj = this->getJniObject().callObjectMethod("getData", signature.toLocal8Bit().constData());
    JavaUtilList * jlist = new JavaUtilList(obj);
    return jlist->toArray();
}

JavaLangObject QtMobilePluginChannelMessage::getFirstData(){
    auto signature =  JniMethodBuilder::builder()
            ->returnType<jobject>()
            ->build();
    return this->getData(0, signature.toLocal8Bit().constData());
}

JavaLangObject QtMobilePluginChannelMessage::getData(int const &index){
    auto signature =  JniMethodBuilder::builder()
            ->arg<int>()
            ->returnType<jobject>()
            ->build();
    return this->getData(index, signature.toLocal8Bit().constData());
}

JavaLangObject QtMobilePluginChannelMessage::getData(int const &index, const QString& methodSignature){
    QJniObject obj = this->getJniObject().callObjectMethod("getData", methodSignature.toLocal8Bit().constData(), jint(index));
    qDebug() << "getData " << obj.isValid();
    return JavaLangObject(obj);
}

void QtMobilePluginChannelMessage::setId(QString const &id){
    auto signature =  JniMethodBuilder::builder()->arg<jstring>()->build();
    QJniObject javaString = QJniObject::fromString(id);
    this->getJniObject().callMethod<void>("setId", signature.toLocal8Bit().constData(), javaString.object<jstring>());
}

QString QtMobilePluginChannelMessage::getId(){
    QJniObject str = this->getJniObject().callObjectMethod<jstring>("getId");
    return str.toString();
}

void QtMobilePluginChannelMessage::setMethodName(QString const &methodName){
    auto signature =  JniMethodBuilder::builder()->arg<jstring>()->build();
    QJniObject jstr = QJniObject::fromString(methodName);
    this->getJniObject().callMethod<void>("setMethodName", signature.toLocal8Bit().constData(), jstr.object<jstring>());
}

QString QtMobilePluginChannelMessage::getMethodName(){
    QJniObject str = this->getJniObject().callObjectMethod<jstring>("getMethodName");
    return str.toString();
}

void QtMobilePluginChannelMessage::setChannelName(QString const &channelName){
    auto signature =  JniMethodBuilder::builder()->arg<jstring>()->build();
    QJniObject jstr = QJniObject::fromString(channelName);
    this->getJniObject().callMethod<void>("setChannelName", signature.toLocal8Bit().constData(), jstr.object<jstring>());
}

QString QtMobilePluginChannelMessage::getChannelName(){
    QJniObject str = this->getJniObject().callObjectMethod<jstring>("getChannelName");
    return str.toString();
}

bool QtMobilePluginChannelMessage::hasError(){
    return this->getJniObject().callMethod<jboolean>("hasError");
}

bool QtMobilePluginChannelMessage::hasThrowable(){
    return this->getJniObject().callMethod<jboolean>("hasThrowable");
}

JavaLangThrowable QtMobilePluginChannelMessage::getThrowable(){
    QJniObject obj = this->getJniObject().callObjectMethod<jobject>("getThrowable");
    return JavaLangThrowable(obj);
}

QString QtMobilePluginChannelMessage::getErrorDescription(){
    QJniObject str = this->getJniObject().callObjectMethod<jstring>("getErrorDescription");
    return str.toString();
}

void QtMobilePluginChannelMessage::addArg(JavaLangObject &arg){
    auto signature =  JniMethodBuilder::builder()->arg<jobject>()->build();
    this->getJniObject().callMethod<void>("addArg", signature.toLocal8Bit().constData(), arg.getJavaObject());
}

QtMobilePluginChannelMessage* QtMobilePluginChannelMessage::withArg(JavaLangObject &arg){
    this->addArg(arg);
    return this;
}

QtMobilePluginChannelMessage* QtMobilePluginChannelMessage::withArg(const QString &arg){
    QJniObject javaString = QJniObject::fromString(arg);
    JavaLangObject javaObj(javaString);
    this->addArg(javaObj);
    return this;
}

QString QtMobilePluginChannelMessage::dump(){
    QJniObject str = this->getJniObject().callObjectMethod<jstring>("dump");
    return str.toString();
}

QtMobilePluginChannelMessage* QtMobilePluginChannelMessage::newJavaObject(){
    QJniObject javaObj(QtMobilePluginChannelMessage::kJavaClassName.toLocal8Bit().constData());
    QtMobilePluginChannelMessage*  message = new QtMobilePluginChannelMessage(javaObj);
    return message;
}

QtMobilePluginChannelMessage* QtMobilePluginChannelMessage::newJavaObject(QString const &channelName, QString const &methodName){
    QtMobilePluginChannelMessage* message = QtMobilePluginChannelMessage::newJavaObject();
    message->setChannelName(channelName);
    message->setMethodName(methodName);
    return message;
}
