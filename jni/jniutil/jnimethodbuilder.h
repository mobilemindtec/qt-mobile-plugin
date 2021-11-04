#ifndef JNIMETHODBUILDER_H
#define JNIMETHODBUILDER_H

#include <QAndroidJniObject>
#include <QtCore>

class JavaArrayList{};
class JavaSet{};
class JavaMap{};
class JavaList{};

class JniMethodBuilder {

private:
    QString _qualifiedReturn;
    QList<QString> _qualifiedArgs;

public:
    JniMethodBuilder();
    ~JniMethodBuilder();

    JniMethodBuilder* returnTypedObject(QString const &fullyQualifiedName);
    JniMethodBuilder* returnTypedArray(QString const &fullyQualifiedName);
    JniMethodBuilder* returnTyped(QString const &fullyQualifiedName);

    template<typename T>
    JniMethodBuilder* returnType();


    JniMethodBuilder* argTypedObject(QString const &fullyQualifiedName);
    JniMethodBuilder* argTypedArray(QString const &fullyQualifiedName);
    JniMethodBuilder* arg(QString const &fullyQualifiedName);

    template<typename T>
    JniMethodBuilder* arg();

    JniMethodBuilder* empty();

    const char* build();
    const char* buildConstructor();
    void clear();

    int callMethodJavaUtilCollection_Size(QAndroidJniObject const &obj);
    QAndroidJniObject callMethodJavaUtilMap_EntrySet(QAndroidJniObject const &obj);
    QAndroidJniObject callMethodJavaUtilSet_ToArray(QAndroidJniObject const &obj);
    QAndroidJniObject callMethodJavaUtilList_Get(QAndroidJniObject const &obj);
    QAndroidJniObject callMethodJavaUtil_MapEntry_GetKey(QAndroidJniObject const &obj);
    QAndroidJniObject callMethodJavaUtil_MapEntry_GetValue(QAndroidJniObject const &obj);

    static JniMethodBuilder* builder();

    static const QString kJavaClassNameObject;
    static const QString kJavaClassNameString;
    static const QString kJavaClassNameList;
    static const QString kJavaClassNameMap;
    static const QString kJavaClassNameSet;
    static const QString kJavaClassNameArrayList;
    static const QString kJavaClassNameIterator;
    static const QString kJavaClassNameCollection;
};



#endif // JNIMETHODBUILDER_H
