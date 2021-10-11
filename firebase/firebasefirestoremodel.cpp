#include "firebasefirestoremodel.h"
#include <android/log.h>


FirebaseFirestoreModel* FirebaseFirestoreModel::m_instance;

FirebaseFirestoreModel::FirebaseFirestoreModel(QObject *parent)
    : QObject(parent)
{
    // By default, QQuickItem does not draw anything. If you subclass
    // QQuickItem to create a visual item, you will need to uncomment the
    // following line and re-implement updatePaintNode()

    // setFlag(ItemHasContents, true);
    FirebaseFirestoreModel::m_instance = this;
    this->registerNativeMethods();
}

FirebaseFirestoreModel::~FirebaseFirestoreModel()
{

}

static void static_firestoreReadResult(JNIEnv *env, jobject thiz, jstring collection, jobjectArray values){
    Q_UNUSED(env)
    Q_UNUSED(thiz)
    __android_log_write(ANDROID_LOG_INFO, "FirebasePlugin", "static_firestoreReadResult");
    qDebug() << "collection " << collection << " values " << values;

    //QAndroidJniEnvironment jenv;

    QList<QString> list;

    jint size = env->GetArrayLength(values);
    for(int i = 0; i < size; i++){
       jobject jobj =  env->GetObjectArrayElement(values, i);
       QAndroidJniObject string = QAndroidJniObject::fromLocalRef(jobj);
       list << string.toString();
    }



    emit FirebaseFirestoreModel::instance()->firestoreResultsFor(env->GetStringUTFChars(collection, nullptr), list);
}

static void static_firestoreReadResult2(JNIEnv *env, jobject thiz, jstring collection, jobject values){
    Q_UNUSED(env)
    Q_UNUSED(thiz)
    __android_log_write(ANDROID_LOG_INFO, "FirebasePlugin", "static_firestoreReadResult2");
    qDebug() << "collection " << collection << " values " << values;

    //QAndroidJniEnvironment jenv;

    JniMethodBuilder* builder = new JniMethodBuilder();
    QVariantList list;

    QAndroidJniObject javaList = QAndroidJniObject::fromLocalRef(values);

    qDebug() << "step 1";

    int size = builder->callMethodCollection_Size(javaList); //javaList.callMethod<jint>("size");

    qDebug() << "size " << size;

    for(jint i = 0; i < size; i++){
        qDebug() << "step 2";
        QAndroidJniObject javaMap = javaList.callObjectMethod("get", "(I)Ljava/lang/Object;", i);
        qDebug() << "step 4 ";
        QAndroidJniObject javaSet = javaMap.callObjectMethod("entrySet", "()Ljava/util/Set;");
        qDebug() << "step 6";
        QAndroidJniObject javaArray = javaSet.callObjectMethod("toArray", "()[Ljava/lang/Object;");
        qDebug() << "step 7";
        jobjectArray array = javaArray.object<jobjectArray>();
        jint arrlen = env->GetArrayLength(array);
        qDebug() << "step 8";
        qDebug() << "arrlen " << arrlen ;

        QVariantMap mapData;

        for(jint j = 0; j < arrlen; j++){
            qDebug() << "step 9";
            jobject jobj =  env->GetObjectArrayElement(array, j);
            qDebug() << "step 10";
            QAndroidJniObject mapEntry = QAndroidJniObject::fromLocalRef(jobj);
            qDebug() << "step 11";
            QAndroidJniObject strKey = mapEntry.callObjectMethod<jobject>("getKey");
            qDebug() << "step 12";
            QAndroidJniObject strObj = mapEntry.callObjectMethod<jobject>("getValue");
            qDebug() << "step 13";
            mapData[strKey.toString()] = strObj.toString();
            qDebug() << "step 14";
        }

        list << mapData;
    }



    emit FirebaseFirestoreModel::instance()->firestoreResultsFor2(env->GetStringUTFChars(collection, nullptr), list);
}

static void static_firestoreError(JNIEnv *env, jobject thiz, jstring error){
    Q_UNUSED(env)
    Q_UNUSED(thiz)
    qDebug() << "collection " << error;
    __android_log_write(ANDROID_LOG_INFO, "FirebasePlugin", "static_firestoreError");
    emit FirebaseFirestoreModel::instance()->firestoreError(env->GetStringUTFChars(error, nullptr));
}

void FirebaseFirestoreModel::firestoreRead(const QString &collection){
    __android_log_write(ANDROID_LOG_INFO, "FirebasePlugin", "firestoreRead");
    QAndroidJniObject javaCollection = QAndroidJniObject::fromString(collection);
    QAndroidJniObject javaClass("com/qt/plugin/firebase/QtFirebasePlugin");
    javaClass.callMethod<void>("firestoreRead", "(Ljava/lang/String;)V", javaCollection.object<jobject>());
    __android_log_write(ANDROID_LOG_INFO, "FirebasePlugin", "firestoreRead ok");
}


void FirebaseFirestoreModel::registerNativeMethods() {

    __android_log_write(ANDROID_LOG_INFO, "FirebasePlugin", "registerNativeMethods");

    QAndroidJniObject javaClass("com/qt/plugin/firebase/QtFirebasePlugin");
    QAndroidJniEnvironment env;       

    jclass objectClass = env->GetObjectClass(javaClass.object<jobject>());

    JNINativeMethod methods[] = {
      {"static_firestoreReadResult", "(Ljava/lang/String;[Ljava/lang/String;)V", reinterpret_cast<void *>(static_firestoreReadResult)},
      {"static_firestoreReadResult2", "(Ljava/lang/String;Ljava/util/List;)V", reinterpret_cast<void *>(static_firestoreReadResult2)},
      {"static_firestoreError", "(Ljava/lang/String;)V", reinterpret_cast<void *>(static_firestoreError)}
    };

    env->RegisterNatives(objectClass,
                         methods,
                         sizeof(methods) /  sizeof(methods[0]));
    env->DeleteLocalRef(objectClass);

    __android_log_write(ANDROID_LOG_INFO, "FirebasePlugin", "registerNativeMethods end");
}
