#include "qtmobileplugindispatcher.h"

QtMobilePluginDispatcher * QtMobilePluginDispatcher::instance_;

const QString QtMobilePluginDispatcher::kJavaClassName = "com/qt/plugin/core/QtMobilePluginDispatcher";

QtMobilePluginDispatcher::QtMobilePluginDispatcher(QJniObject obj) : JavaLangObject(obj){

    if(QtMobilePluginDispatcher::instance_ == NULL)
        QtMobilePluginDispatcher::instance_ = this;
    this->registerNativeMethods();
}

QtMobilePluginDispatcher * QtMobilePluginDispatcher::instance(){
    if(QtMobilePluginDispatcher::instance_ == NULL){
        QtMobilePluginDispatcher::instance_ = QtMobilePluginDispatcher::newJavaObject();
    }
    return QtMobilePluginDispatcher::instance_;
}

void QtMobilePluginDispatcher::dispatch(QtMobilePluginChannelMessage* message)
{
    auto signature =  JniMethodBuilder::builder()
            ->argTypedObject(kAndroidContentContext)
            ->argTypedObject(kAndroidAppActivity)
            ->argTypedObject(QtMobilePluginChannelMessage::kJavaClassName)
            ->build();

    QJniObject context = QNativeInterface::QAndroidApplication::context();
    //QJniObject activity = QNativeInterface::QAndroidApplication::context();

    this->getJniObject().callMethod<void>(
                "dispatch",
                signature.toLocal8Bit().constData(),
                context.object(),
                context.object(), //QtAndroid::androidActivity().object(),
                message->getJavaObject());
}

QtMobilePluginDispatcher * QtMobilePluginDispatcher::newJavaObject(){
    qDebug() << "QtMobilePluginDispatcher::newJavaObject";
    QJniObject javaObj(QtMobilePluginDispatcher::kJavaClassName.toLocal8Bit().constData());
    QtMobilePluginDispatcher * channel = new QtMobilePluginDispatcher(javaObj);
    return channel;
}

// recebe dados via callback do Java
static void onResultFromJava(JNIEnv *env, jobject thiz, jobject jmessage){
    Q_UNUSED(env)
    Q_UNUSED(thiz)
    // __android_log_write(ANDROID_LOG_INFO, "FirebasePlugin", "static_firestoreReadResult");
    qDebug() << "QtMobilePluginDispatcher c++: Message received";
    QJniObject javaMessage = QJniObject::fromLocalRef(jmessage);
    QtMobilePluginChannelMessage message = QtMobilePluginChannelMessage(javaMessage);
    qDebug() << "QtMobilePluginDispatcher Message.dump: " << message.dump();

    emit QtMobilePluginDispatcher::instance()->messageReceived(&message);
}


void QtMobilePluginDispatcher::registerNativeMethods(){

    qDebug() << kTag << "registerNativeMethods";

    QJniObject javaClass(QtMobilePluginDispatcher::kJavaClassName.toLocal8Bit().constData());
    QJniEnvironment env;
    jclass objectClass = env->GetObjectClass(javaClass.object<jobject>());

    auto _ = final_act([&]{
        env->DeleteLocalRef(objectClass);
    });

    JniMethodBuilder builder;
    auto signature = builder.argTypedObject(QtMobilePluginChannelMessage::kJavaClassName)->build();

    qDebug() << "class is valid = " << javaClass.isValid() << ", toString = " << javaClass.toString();
    qDebug() << "ref " << objectClass;
    qDebug() << "signature " << signature;

    const JNINativeMethod methods[] = {
      {"onQtResult", signature.toLocal8Bit().constData() , reinterpret_cast<void *>(onResultFromJava)},
    };

    //auto registerStatus = env.registerNativeMethods(javaClass.objectClass(), methods, 2);
    auto registerStatus = env->RegisterNatives(objectClass,
                         methods,
                         sizeof(methods) /  sizeof(methods[0]));

    qDebug() << "register status: " << registerStatus;

    if(env->ExceptionCheck()){
        qDebug() << "Excetpion!!! ";
        env->ExceptionDescribe();
    }

    qRegisterMetaType<QtMobilePluginChannelMessage>("QtMobilePluginChannelMessage&");
    qRegisterMetaType<QtMobilePluginChannelMessage>("QtMobilePluginChannelMessage");
    qRegisterMetaType<QtMobilePluginChannelMessage>("QtMobilePluginChannelMessage*");

    qDebug() << kTag << "try registerNativeMethods is done";
}
