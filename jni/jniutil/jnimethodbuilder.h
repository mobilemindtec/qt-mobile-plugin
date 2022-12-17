#ifndef JNIMETHODBUILDER_H
#define JNIMETHODBUILDER_H

#include <QtCore>
#include <QJniObject>


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

    const QString build();
    const QString buildConstructor();
    void clear();

    int callMethodJavaUtilCollection_Size(QJniObject const &obj);
    QJniObject callMethodJavaUtilMap_EntrySet(QJniObject const &obj);
    QJniObject callMethodJavaUtilSet_ToArray(QJniObject const &obj);
    QJniObject callMethodJavaUtilList_Get(QJniObject const &obj);
    QJniObject callMethodJavaUtil_MapEntry_GetKey(QJniObject const &obj);
    QJniObject callMethodJavaUtil_MapEntry_GetValue(QJniObject const &obj);

    static JniMethodBuilder* builder();

};



#endif // JNIMETHODBUILDER_H
