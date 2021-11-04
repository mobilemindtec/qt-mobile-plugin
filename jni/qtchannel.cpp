#include "qtchannel.h"

QtChannel * QtChannel::instance_;

const QString QtChannel::kJavaClassName = "com/qt/plugin/core/QtChannelCaller";

QtChannel::QtChannel(QAndroidJniObject obj) : JavaLangObject(obj){

    if(QtChannel::instance_ == NULL)
        QtChannel::instance_ = this;
    this->registerNativeMethods();
}

QtChannel * QtChannel::instance(){
    if(QtChannel::instance_ == NULL){
        QtChannel::instance_ = QtChannel::newJavaObject();
    }
    return QtChannel::instance_;
}

void QtChannel::callMethod(QtChannelMessage &message)
{
    const char* signature =  JniMethodBuilder::builder()
            ->argTypedObject(QtChannelMessage::kJavaClassName)
            ->build();
    this->getJniObject().callMethod<void>(
                "callMethod",
                signature,
                message.getJavaObject());
}

void QtChannel::callMethod(const QString &channelName, const QString &methodName, QtChannelMessage &message){
    const char* signature =  JniMethodBuilder::builder()
            ->arg<jstring>()
            ->arg<jstring>()
            ->argTypedObject(QtChannelMessage::kJavaClassName)
            ->build();

    QAndroidJniObject javaChannelName = QAndroidJniObject::fromString(channelName);
    QAndroidJniObject javaMethodName = QAndroidJniObject::fromString(methodName);

    this->getJniObject().callMethod<void>(
                "callMethod",
                signature,
                javaChannelName.object<jstring>(),
                javaMethodName.object<jstring>(),
                message.getJavaObject());
}

QtChannel * QtChannel::newJavaObject(){
    qDebug() << "QtChannel::newJavaObject";
    QAndroidJniObject javaObj(JavaLangObject::toChar(QtChannel::kJavaClassName));
    QAndroidJniEnvironment env;
    QtChannel * channel = new QtChannel(javaObj);
    return channel;
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


void QtChannel::registerNativeMethods(){

    qDebug() << kTag << "registerNativeMethods";

    //QAndroidJniObject javaClass("com/qt/plugin/firebase/QtFirebasePlugin");
    QAndroidJniEnvironment env;
    jclass objectClass = env->GetObjectClass(this->getJavaObject());

    const char* signature = JniMethodBuilder::builder()
               ->argTypedObject(QtChannelMessage::kJavaClassName)
               ->build();

    JNINativeMethod methods[] = {
      {"callback", signature, reinterpret_cast<void *>(callback)},
    };

    env->RegisterNatives(objectClass,
                         methods,
                         sizeof(methods) /  sizeof(methods[0]));

    env->DeleteLocalRef(objectClass);


    qRegisterMetaType<QtChannelMessage>("QtChannelMessage&");

    qDebug() << kTag << "registerNativeMethods ok";
}
