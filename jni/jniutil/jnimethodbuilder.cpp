#include "jnimethodbuilder.h"

const QString JniMethodBuilder::kJavaClassNameObject = "java/lang/Object";
const QString JniMethodBuilder::kJavaClassNameString = "java/lang/String";
const QString JniMethodBuilder::kJavaClassNameList= "java/util/List";
const QString JniMethodBuilder::kJavaClassNameMap= "java/util/Map";
const QString JniMethodBuilder::kJavaClassNameSet = "java/util/Set";
const QString JniMethodBuilder::kJavaClassNameArrayList = "java/util/ArrayList";
const QString JniMethodBuilder::kJavaClassNameIterator = "java/util/Iterator";
const QString JniMethodBuilder::kJavaClassNameCollection= "java/util/Collection";

JniMethodBuilder* JniMethodBuilder::builder(){
     return new JniMethodBuilder();
}

JniMethodBuilder::JniMethodBuilder(){

}

JniMethodBuilder::~JniMethodBuilder(){
    //delete this->qualifiedArgs;
    //delete this->qualifiedReturn;
}

template<>
JniMethodBuilder* JniMethodBuilder::arg<void>() { return this->arg(""); };

template<>
JniMethodBuilder* JniMethodBuilder::arg<bool>() { return this->arg("Z"); };

template<>
JniMethodBuilder* JniMethodBuilder::arg<int>() { return this->arg("I"); };

template<>
JniMethodBuilder* JniMethodBuilder::arg<char>() { return this->arg("C"); };

template<>
JniMethodBuilder* JniMethodBuilder::arg<short>() { return this->arg("S"); };

template<>
JniMethodBuilder* JniMethodBuilder::arg<long>() { return this->arg("J"); };

template<>
JniMethodBuilder* JniMethodBuilder::arg<float>() { return this->arg("F"); };

template<>
JniMethodBuilder* JniMethodBuilder::arg<double>() { return this->arg("D"); };

template<>
JniMethodBuilder* JniMethodBuilder::arg<jobject>() { return this->arg("Ljava/lang/Object;"); };

template<>
JniMethodBuilder* JniMethodBuilder::arg<jclass>() { return this->arg("Ljava/lang/Class;"); };

template<>
JniMethodBuilder* JniMethodBuilder::arg<jstring>() { return this->arg("Ljava/lang/String;"); };

template<>
JniMethodBuilder* JniMethodBuilder::arg<jthrowable>() { return this->arg("Ljava/lang/Throwable;"); };

template<>
JniMethodBuilder* JniMethodBuilder::arg<JavaList>() { return this->arg("Ljava/util/List;"); };

template<>
JniMethodBuilder* JniMethodBuilder::arg<JavaMap>() { return this->arg("Ljava/util/Map;"); };

template<>
JniMethodBuilder* JniMethodBuilder::arg<JavaSet>() { return this->arg("Ljava/util/Set;"); };

template<>
JniMethodBuilder* JniMethodBuilder::arg<JavaArrayList>() { return this->arg("Ljava/util/ArrayList;"); };


template<>
JniMethodBuilder* JniMethodBuilder::arg<jarray>() {
    return this->arg("[Ljava/lang/Object;");
}

template<>
JniMethodBuilder* JniMethodBuilder::arg<jbooleanArray>() {
    return this->arg("[Z");
}

template<>
JniMethodBuilder* JniMethodBuilder::arg<jbyteArray>() {
    return this->arg("[B");
};

template<>
JniMethodBuilder* JniMethodBuilder::arg<jcharArray>() {
    return this->arg("[C");
};

template<>
JniMethodBuilder* JniMethodBuilder::arg<jshortArray>() {
    return this->arg("[S");
};

template<>
JniMethodBuilder* JniMethodBuilder::arg<jintArray>() {
    return this->arg("[I");
};

template<>
JniMethodBuilder* JniMethodBuilder::arg<jfloatArray>() {
    return this->arg("[F");
};

template<>
JniMethodBuilder* JniMethodBuilder::arg<jdoubleArray>() {
    return this->arg("[D");
};

template<>
JniMethodBuilder* JniMethodBuilder::returnType<void>() { return this->returnTyped("V"); };
template<>
JniMethodBuilder* JniMethodBuilder::returnType<bool>() { return this->returnTyped("Z"); };
template<>
JniMethodBuilder* JniMethodBuilder::returnType<int>() { return this->returnTyped("I"); };
template<>
JniMethodBuilder* JniMethodBuilder::returnType<char>() { return this->returnTyped("C"); };
template<>
JniMethodBuilder* JniMethodBuilder::returnType<short>() { return this->returnTyped("S"); };
template<>
JniMethodBuilder* JniMethodBuilder::returnType<long>() { return this->returnTyped("J"); };
template<>
JniMethodBuilder* JniMethodBuilder::returnType<float>() { return this->returnTyped("F"); };
template<>
JniMethodBuilder* JniMethodBuilder::returnType<double>() { return this->returnTyped("D"); };
template<>
JniMethodBuilder* JniMethodBuilder::returnType<jobject>() { return this->returnTyped("Ljava/lang/Object;"); };
template<>
JniMethodBuilder* JniMethodBuilder::returnType<jclass>() { return this->returnTyped("Ljava/lang/Class;"); };
template<>
JniMethodBuilder* JniMethodBuilder::returnType<jstring>() { return this->returnTyped("Ljava/lang/String;"); };
template<>
JniMethodBuilder* JniMethodBuilder::returnType<jthrowable>() { return this->returnTyped("Ljava/lang/Throwable;"); };
template<>
JniMethodBuilder* JniMethodBuilder::returnType<JavaList>() { return this->returnTyped("Ljava/util/List;"); };
template<>
JniMethodBuilder* JniMethodBuilder::returnType<JavaMap>() { return this->returnTyped("Ljava/util/Map;"); };
template<>
JniMethodBuilder* JniMethodBuilder::returnType<JavaSet>() { return this->returnTyped("Ljava/util/Set;"); };
template<>
JniMethodBuilder* JniMethodBuilder::returnType<JavaArrayList>() { return this->returnTyped("Ljava/util/ArrayList;"); };
template<>
JniMethodBuilder* JniMethodBuilder::returnType<jarray>() { return this->returnTyped("[Ljava/lang/Object;"); };
template<>
JniMethodBuilder* JniMethodBuilder::returnType<jbooleanArray>() { return this->returnTyped("[Z"); };
template<>
JniMethodBuilder* JniMethodBuilder::returnType<jbyteArray>() { return this->returnTyped("[B"); };
template<>
JniMethodBuilder* JniMethodBuilder::returnType<jcharArray>() { return this->returnTyped("[C"); };
template<>
JniMethodBuilder* JniMethodBuilder::returnType<jshortArray>() { return this->returnTyped("[S"); };
template<>
JniMethodBuilder* JniMethodBuilder::returnType<jintArray>() { return this->returnTyped("[I"); };
template<>
JniMethodBuilder* JniMethodBuilder::returnType<jfloatArray>() { return this->returnTyped("[F"); };
template<>
JniMethodBuilder* JniMethodBuilder::returnType<jdoubleArray>() { return this->returnTyped("[D"); };


JniMethodBuilder* JniMethodBuilder::arg(QString const &fullyQualifiedName){
    this->_qualifiedArgs << fullyQualifiedName;
    return this;
}

JniMethodBuilder* JniMethodBuilder::argTypedObject(QString const &fullyQualifiedName) {

    QString classFullName = fullyQualifiedName;
    if(!fullyQualifiedName.startsWith("L")){
        classFullName = QString("%1%2").arg("L").arg(classFullName);
    }

    if(!fullyQualifiedName.endsWith(";")){
        classFullName = QString("%1%2").arg(classFullName).arg(";");
    }

    return this->arg(classFullName);
}

JniMethodBuilder* JniMethodBuilder::argTypedArray(QString const &fullyQualifiedName) {

    QString classFullName = fullyQualifiedName;

    if(fullyQualifiedName.startsWith("L")){
        classFullName = QString("%1%2").arg("[").arg(classFullName);
    } else if(!fullyQualifiedName.startsWith("[L")){
        classFullName = QString("%1%2").arg("[L").arg(classFullName);
    }

    if(!fullyQualifiedName.endsWith(";")){
        classFullName = QString("%1%2").arg(classFullName).arg(";");
    }

    return this->arg(classFullName);
}

JniMethodBuilder* JniMethodBuilder::returnTyped(QString const &fullyQualifiedName){
    this->_qualifiedReturn = fullyQualifiedName;
    return this;
}

JniMethodBuilder* JniMethodBuilder::returnTypedObject(QString const &fullyQualifiedName) {
    QString classFullName = fullyQualifiedName;
    if(!fullyQualifiedName.startsWith("L")){
        classFullName = QString("%1%2").arg("L").arg(classFullName);
    }

    if(!fullyQualifiedName.endsWith(";")){
        classFullName = QString("%1%2").arg(classFullName).arg(";");
    }

    return this->returnTyped(classFullName);
}

JniMethodBuilder* JniMethodBuilder::returnTypedArray(QString const &fullyQualifiedName) {

    QString classFullName = fullyQualifiedName;

    if(fullyQualifiedName.startsWith("L")){
        classFullName = QString("%1%2").arg("[").arg(classFullName);
    } else if(!fullyQualifiedName.startsWith("[L")){
        classFullName = QString("%1%2").arg("[L").arg(classFullName);
    }

    if(!fullyQualifiedName.endsWith(";")){
        classFullName = QString("%1%2").arg(classFullName).arg(";");
    }

    return this->returnTyped(classFullName);
}

int JniMethodBuilder::callMethodJavaUtilCollection_Size(QAndroidJniObject const &obj){
    return obj.callMethod<jint>("size");
}

QAndroidJniObject JniMethodBuilder::callMethodJavaUtilMap_EntrySet(QAndroidJniObject const &obj){
    JniMethodBuilder* builer = new JniMethodBuilder();
    const char* signature =  builer->returnType<JavaSet>()->build();
    QAndroidJniObject javaObj = obj.callObjectMethod("entrySet", signature);
    return javaObj;
}

QAndroidJniObject JniMethodBuilder::callMethodJavaUtilSet_ToArray(QAndroidJniObject const &obj){
    JniMethodBuilder* builer = new JniMethodBuilder();
    const char* signature =  builer->returnType<jarray>()->build();
    QAndroidJniObject javaObj = obj.callObjectMethod("toArray", signature);
    return javaObj;
}

QAndroidJniObject JniMethodBuilder::callMethodJavaUtilList_Get(QAndroidJniObject const &obj){
    QAndroidJniObject javaObj = obj.callObjectMethod<jobject>("get");
    return javaObj;
}

QAndroidJniObject JniMethodBuilder::callMethodJavaUtil_MapEntry_GetKey(QAndroidJniObject const &obj){
    QAndroidJniObject javaObj = obj.callObjectMethod<jobject>("getKey");
    return javaObj;
}

QAndroidJniObject JniMethodBuilder::callMethodJavaUtil_MapEntry_GetValue(QAndroidJniObject const &obj){
    QAndroidJniObject javaObj = obj.callObjectMethod<jobject>("getValue");
    return javaObj;
}

void JniMethodBuilder::clear(){
    this->_qualifiedReturn = "";
    this->_qualifiedArgs.clear();
}

JniMethodBuilder* JniMethodBuilder::empty(){
    this->clear();
    return this;
}

const char* JniMethodBuilder::build(){

    const char* methodAsign;

    if(this->_qualifiedReturn.isEmpty() || this->_qualifiedReturn.isEmpty()){
        this->returnType<void>();
    }

    if(this->_qualifiedArgs.isEmpty()){
       QString value = QString("()%1").arg(this->_qualifiedReturn);
       methodAsign = value.toLocal8Bit().constData();
    } else {

        QString args;

        for(QString it : this->_qualifiedArgs){
            args.append(it);
        }

        qDebug() << "ARGS " << args << ", RETURN " << this->_qualifiedReturn;

        QString value = QString("(%1)%2").arg(args).arg(this->_qualifiedReturn);
        qDebug() << "VALUE " << value;
        methodAsign = value.toLocal8Bit().constData();
    }

    qDebug() << "methodAsign " << methodAsign;

    return methodAsign;
}

const char* JniMethodBuilder::buildConstructor(){

    QString args;

    for(QString it : this->_qualifiedArgs){
        args.append(it);
    }

    QString value = QString("%2").arg(args);
    return value.toLocal8Bit().constData();
}
