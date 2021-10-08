#ifndef SUPPORT_H
#define SUPPORT_H

#include <QString>
#include <QList>
#include <QAndroidJniObject>



class JniMethodBuilder {

private:
    QString qualifiedReturn;
    QList<QString> qualifiedArgs;

public:
    JniMethodBuilder();
    ~JniMethodBuilder();


    const QString javaClassObject = "Ljava/lang/Object;";
    const QString javaClassString = "Ljava/lang/String;";
    const QString javaClassList= "Ljava/util/List;";
    const QString javaClassMap= "Ljava/util/Map;";
    const QString javaClassSet = "Ljava/util/Set;";
    const QString javaClassArrayList = "Ljava/util/ArrayList;";



    JniMethodBuilder* returnVoid() { return this->addReturn("V"); };
    JniMethodBuilder* returnBoolean() { return this->addReturn("Z"); };
    JniMethodBuilder* returnInt() { return this->addReturn("I"); };
    JniMethodBuilder* returnChar() { return this->addReturn("C"); };
    JniMethodBuilder* returnShort() { return this->addReturn("S"); };
    JniMethodBuilder* returnLong() { return this->addReturn("J"); };
    JniMethodBuilder* returnFloat() { return this->addReturn("F"); };
    JniMethodBuilder* returnDouble() { return this->addReturn("D"); };
    JniMethodBuilder* returnObject() { return this->addReturn("Ljava/lang/Object;"); };
    JniMethodBuilder* returnClass() { return this->addReturn("Ljava/lang/Class;"); };
    JniMethodBuilder* returnString() { return this->addReturn("Ljava/lang/String;"); };
    JniMethodBuilder* returnThrowable() { return this->addReturn("Ljava/lang/Throwable;"); };

    JniMethodBuilder* returnList() { return this->addReturn("Ljava/util/List;"); };
    JniMethodBuilder* returnMap() { return this->addReturn("Ljava/util/Map;"); };
    JniMethodBuilder* returnSet() { return this->addReturn("Ljava/util/Set;"); };
    JniMethodBuilder* returnArrayList() { return this->addReturn("Ljava/util/ArrayList;"); };

    JniMethodBuilder* returnType(QString const &fullyQualifiedName) { return this->addReturn(QString("L%1").arg(fullyQualifiedName)); };

    JniMethodBuilder* returnArrayTyped(QString const &fullyQualifiedName) { return this->addReturn(QString("[%1").arg(fullyQualifiedName)); };

    JniMethodBuilder* returnArrayObject() { return this->addReturn("[Ljava/lang/Object;"); };
    JniMethodBuilder* returnArrayBoolean() { return this->addReturn("[Z"); };
    JniMethodBuilder* returnArrayByte() { return this->addReturn("[B"); };
    JniMethodBuilder* returnArrayChar() { return this->addReturn("[C"); };
    JniMethodBuilder* returnArrayShort() { return this->addReturn("[S"); };
    JniMethodBuilder* returnArrayInt() { return this->addReturn("[I"); };
    JniMethodBuilder* returnArrayFloat() { return this->addReturn("[F"); };
    JniMethodBuilder* returnArrayDouble() { return this->addReturn("[D"); };

    JniMethodBuilder* addReturn(QString const &fullyQualifiedName);

    ////

    JniMethodBuilder* noArgs() { return this->arg(""); };
    JniMethodBuilder* argBoolean() { return this->arg("Z"); };
    JniMethodBuilder* argInt() { return this->arg("I"); };
    JniMethodBuilder* argChar() { return this->arg("C"); };
    JniMethodBuilder* argShort() { return this->arg("S"); };
    JniMethodBuilder* argLong() { return this->arg("J"); };
    JniMethodBuilder* argFloat() { return this->arg("F"); };
    JniMethodBuilder* argDouble() { return this->arg("D"); };
    JniMethodBuilder* argObject() { return this->arg("Ljava/lang/Object;"); };
    JniMethodBuilder* argClass() { return this->arg("Ljava/lang/Class;"); };
    JniMethodBuilder* argString() { return this->arg("Ljava/lang/String;"); };
    JniMethodBuilder* argThrowable() { return this->arg("Ljava/lang/Throwable;"); };

    JniMethodBuilder* argList() { return this->arg("Ljava/util/List;"); };
    JniMethodBuilder* argMap() { return this->arg("Ljava/util/Map;"); };
    JniMethodBuilder* argSet() { return this->arg("Ljava/util/Set;"); };
    JniMethodBuilder* argArrayList() { return this->arg("Ljava/util/ArrayList;"); };

    JniMethodBuilder* argType(QString const &fullyQualifiedName) { return this->arg(QString("L%1").arg(fullyQualifiedName)); };

    JniMethodBuilder* argArrayTyped(QString const &fullyQualifiedName) { return this->arg(QString("[%1").arg(fullyQualifiedName)); };

    JniMethodBuilder* argArray() { return this->arg("[Ljava/lang/Object;"); };
    JniMethodBuilder* argArrayBoolean() { return this->arg("[Z"); };
    JniMethodBuilder* argArrayByte() { return this->arg("[B"); };
    JniMethodBuilder* argArrayChar() { return this->arg("[C"); };
    JniMethodBuilder* argArrayShort() { return this->arg("[S"); };
    JniMethodBuilder* argArrayInt() { return this->arg("[I"); };
    JniMethodBuilder* argArrayFloat() { return this->arg("[F"); };
    JniMethodBuilder* argArrayDouble() { return this->arg("[D"); };

    JniMethodBuilder* arg(QString const &fullyQualifiedName);

    char* build();
    char* buildConstructor();
    JniMethodBuilder* empty();
    void clear();

    int callMethodJavaUtilCollection_Size(QAndroidJniObject const &obj);
    QAndroidJniObject callMethodJavaUtilMap_EntrySet(QAndroidJniObject const &obj);
    QAndroidJniObject callMethodJavaUtilSet_ToArray(QAndroidJniObject const &obj);
    QAndroidJniObject callMethodJavaUtilList_Get(QAndroidJniObject const &obj);
    QAndroidJniObject callMethodJavaUtil_MapEntry_GetKey(QAndroidJniObject const &obj);
    QAndroidJniObject callMethodJavaUtil_MapEntry_GetValue(QAndroidJniObject const &obj);
};

class Support
{
public:
    Support();
};

#endif // SUPPORT_H
