#ifndef FIREBASE_H
#define FIREBASE_H

#include <QtQml>
#include <QAndroidJniObject>
#include <QAndroidJniEnvironment>
#include <QList>

//![0]
class FirebaseFirestoreModel : public QObject
{
    Q_OBJECT
    //Q_DISABLE_COPY(Firebase)
     QML_NAMED_ELEMENT(FirebaseFirestore)
//![0]
private:
    void registerNativeMethods();
    static FirebaseFirestoreModel *m_instance;

public:
    explicit FirebaseFirestoreModel(QObject *parent = nullptr);
    static FirebaseFirestoreModel  *instance() { return FirebaseFirestoreModel::m_instance; }

    ~FirebaseFirestoreModel() override;

    Q_INVOKABLE void firestoreRead(QString const &collection);    


signals:
    void firestoreResultsFor(QString const &collection, QList<QString> const &values);
    void firestoreResultsFor2(QString const &collection, QVariantList const &values);
    void firestoreError(QString const &error);


public slots:

};

#endif // FIREBASE_H
