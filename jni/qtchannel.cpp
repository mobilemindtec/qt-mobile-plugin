#include "qtchannel.h"

QtChannel * QtChannel::_instance;

const QString QtChannel::JavaClassName = "[com/qt/plugin/core/QtChannelImpl;";

QtChannel::QtChannel() : QtChannel(NULL){
}

QtChannel::QtChannel(QAndroidJniObject obj) : JavaLangObject(obj){
    QtChannel::_instance = this;
}

void QtChannel::callMethod(QtChannelMessage &message) const
{
    char * signature =  JniMethodBuilder::builder()
            ->argType(QtChannelMessage::JavaClassName)
            ->build();
    this->jniObj->callMethod<jobject>(
                "callMethod",
                signature,
                message.object()->object());
}

void QtChannel::callMethod(const QString &channelName, const QString &methodName, QtChannelMessage &message) const{
    char * signature =  JniMethodBuilder::builder()
            ->argString()
            ->argString()
            ->argType(QtChannelMessage::JavaClassName)
            ->build();

    QAndroidJniObject javaChannelName = QAndroidJniObject::fromString(channelName);
    QAndroidJniObject javaMethodName = QAndroidJniObject::fromString(methodName);

    this->jniObj->callMethod<jobject>(
                "callMethod",
                signature,
                javaChannelName.object<jstring>(),
                javaMethodName.object<jstring>(),
                message.object()->object());
}

QtChannel newJavaObject(){
    QAndroidJniObject javaObj("com/qt/plugin/core/QtChannelImpl");
    QAndroidJniEnvironment env;
    QtChannel channel = QtChannel(javaObj);
    return channel;
}

template <>
QtChannel JavaLangObject::fromLocalRef<QtChannel>(jobject obj){
    return QtChannel(QAndroidJniObject::fromLocalRef(obj));
}


static void callback(JNIEnv *env, jobject thiz, jobject jmessage){
    Q_UNUSED(env)
    Q_UNUSED(thiz)
    // __android_log_write(ANDROID_LOG_INFO, "FirebasePlugin", "static_firestoreReadResult");
    qDebug() << "QtChannel c++: Message received";
    QAndroidJniObject javaMessage = QAndroidJniObject::fromLocalRef(jmessage);
    QtChannelMessage message = QtChannelMessage(javaMessage);
    qDebug() << "QtChannel Message.dump: " << message.dump();
    emit QtChannel::instance()->messageReceived(message);
}

//void FirebaseFirestoreModel::firestoreRead(const QString &collection){
//    __android_log_write(ANDROID_LOG_INFO, "FirebasePlugin", "firestoreRead");
//    QAndroidJniObject javaCollection = QAndroidJniObject::fromString(collection);
//    QAndroidJniObject javaClass("com/qt/plugin/firebase/QtFirebasePlugin");
//    javaClass.callMethod<void>("firestoreRead", "(Ljava/lang/String;)V", javaCollection.object<jobject>());
//    __android_log_write(ANDROID_LOG_INFO, "FirebasePlugin", "firestoreRead ok");
//}


void QtChannel::registerNativeMethods() const{

    __android_log_write(ANDROID_LOG_INFO, "FirebasePlugin", "registerNativeMethods");

    //QAndroidJniObject javaClass("com/qt/plugin/firebase/QtFirebasePlugin");
    QAndroidJniEnvironment env;
    jclass objectClass = env->GetObjectClass(this->jniObj->object());

    char * signature = JniMethodBuilder::builder()
               ->argType(QtChannelMessage::JavaClassName)
               ->build();

    JNINativeMethod methods[] = {
      {"callback", signature, reinterpret_cast<void *>(callback)},
    };

    env->RegisterNatives(objectClass,
                         methods,
                         sizeof(methods) /  sizeof(methods[0]));
    env->DeleteLocalRef(objectClass);

    __android_log_write(ANDROID_LOG_INFO, "FirebasePlugin", "registerNativeMethods end");
}
