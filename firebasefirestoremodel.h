#ifndef FIREBASE_H
#define FIREBASE_H

#include <QtQml>
#include <QAndroidJniObject>
#include <QAndroidJniEnvironment>
#include <QList>
#include "jni/qtchannel.h"
#include "jni/qtchannelmessage.h"
#include "jni/javautilmap.h"
#include "jni/javautillist.h"

//![0]
class FirebaseFirestoreModel : public QObject
{
    Q_OBJECT
    //Q_DISABLE_COPY(Firebase)
     QML_NAMED_ELEMENT(FirebaseFirestore)
//![0]
private:
    void registerNativeMethods();
    static FirebaseFirestoreModel *instance_;
    const QString kChannelName = "com.qt.plugin.firebase.Firestore";
    const QString kMethodGetCollection = "getCollection";
    const QString kMethodInit = "init";
    const QString kTag = "FirebaseFirestoreModel: ";

public:
    explicit FirebaseFirestoreModel(QObject *parent = nullptr);
    static FirebaseFirestoreModel  *instance() { return FirebaseFirestoreModel::instance_; }

    ~FirebaseFirestoreModel() override;

    Q_INVOKABLE void getCollection(QString const &collection);
    Q_INVOKABLE void init();

    static const QString kJavaClassName;


signals:

    void error(QString const &error);
    void collection(QString const &collection, QVariantList const &values);

    //void firestoreResultsFor(QString const &collection, QList<QString> const &values);
    //void firestoreResultsFor2(QString const &collection, QVariantList const &values);
    //void firestoreError(QString const &error);


public slots:
    void setMessage(QtChannelMessage &message);

};

#endif // FIREBASE_H
