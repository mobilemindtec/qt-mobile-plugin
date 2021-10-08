#ifndef FIREBASE_H
#define FIREBASE_H

#include <QtQml>
#include <QAndroidJniObject>
#include <QAndroidJniEnvironment>
#include <QList>

//![0]
class FirebaseModel : public QObject
{
    Q_OBJECT
    //Q_DISABLE_COPY(Firebase)
     QML_NAMED_ELEMENT(Firebase)
//![0]
private:
    void registerNativeMethods();
    static FirebaseModel *m_instance;

public:
    explicit FirebaseModel(QObject *parent = nullptr);
    static FirebaseModel  *instance() { return FirebaseModel::m_instance; }

    ~FirebaseModel() override;

    Q_INVOKABLE void firestoreRead(QString const &collection);    


signals:
    void firestoreResultsFor(QString const &collection, QList<QString> const &values);
    void firestoreResultsFor2(QString const &collection, QVariantList const &values);
    void firestoreError(QString const &error);


public slots:

};

#endif // FIREBASE_H
