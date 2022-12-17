#include "jnimethodbuilder.h"



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
        classFullName = QString("%1%2").arg("L", classFullName);
    }

    if(!fullyQualifiedName.endsWith(";")){
        classFullName = QString("%1%2").arg(classFullName, ";");
    }

    return this->arg(classFullName);
}

JniMethodBuilder* JniMethodBuilder::argTypedArray(QString const &fullyQualifiedName) {

    QString classFullName = fullyQualifiedName;

    if(fullyQualifiedName.startsWith("L")){
        classFullName = QString("%1%2").arg("[", classFullName);
    } else if(!fullyQualifiedName.startsWith("[L")){
        classFullName = QString("%1%2").arg("[L", classFullName);
    }

    if(!fullyQualifiedName.endsWith(";")){
        classFullName = QString("%1%2").arg(classFullName, ";");
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
        classFullName = QString("%1%2").arg("L", classFullName);
    }

    if(!fullyQualifiedName.endsWith(";")){
        classFullName = QString("%1%2").arg(classFullName, ";");
    }

    return this->returnTyped(classFullName);
}

JniMethodBuilder* JniMethodBuilder::returnTypedArray(QString const &fullyQualifiedName) {

    QString classFullName = fullyQualifiedName;

    if(fullyQualifiedName.startsWith("L")){
        classFullName = QString("%1%2").arg("[", classFullName);
    } else if(!fullyQualifiedName.startsWith("[L")){
        classFullName = QString("%1%2").arg("[L", classFullName);
    }

    if(!fullyQualifiedName.endsWith(";")){
        classFullName = QString("%1%2").arg(classFullName, ";");
    }

    return this->returnTyped(classFullName);
}

int JniMethodBuilder::callMethodJavaUtilCollection_Size(QJniObject const &obj){
    return obj.callMethod<jint>("size");
}

QJniObject JniMethodBuilder::callMethodJavaUtilMap_EntrySet(QJniObject const &obj){
    JniMethodBuilder* builer = new JniMethodBuilder();
    auto signature =  builer->returnType<JavaSet>()->build();
    QJniObject javaObj = obj.callObjectMethod("entrySet", signature.toLocal8Bit().constData());
    return javaObj;
}

QJniObject JniMethodBuilder::callMethodJavaUtilSet_ToArray(QJniObject const &obj){
    JniMethodBuilder* builer = new JniMethodBuilder();
    auto signature =  builer->returnType<jarray>()->build();
    QJniObject javaObj = obj.callObjectMethod("toArray", signature.toLocal8Bit().constData());
    return javaObj;
}

QJniObject JniMethodBuilder::callMethodJavaUtilList_Get(QJniObject const &obj){
    QJniObject javaObj = obj.callObjectMethod<jobject>("get");
    return javaObj;
}

QJniObject JniMethodBuilder::callMethodJavaUtil_MapEntry_GetKey(QJniObject const &obj){
    QJniObject javaObj = obj.callObjectMethod<jobject>("getKey");
    return javaObj;
}

QJniObject JniMethodBuilder::callMethodJavaUtil_MapEntry_GetValue(QJniObject const &obj){
    QJniObject javaObj = obj.callObjectMethod<jobject>("getValue");
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

const QString JniMethodBuilder::build(){

    QString value;

    if(this->_qualifiedReturn.isEmpty() || this->_qualifiedReturn.isEmpty()){
        this->returnType<void>();
    }

    if(this->_qualifiedArgs.isEmpty()){
       value = QString("()%1").arg(this->_qualifiedReturn);
    } else {
        QString args;

        for(const QString& it : this->_qualifiedArgs){
            args.append(it);
        }
        qDebug() << "ARGS " << args << ", RETURN " << this->_qualifiedReturn;
        value = QString("(%1)%2").arg(args, this->_qualifiedReturn);
    }


    qDebug() << "VALUE " << value;

    return value;

}

const QString JniMethodBuilder::buildConstructor(){
    QString args;
    for(const QString& it : this->_qualifiedArgs){
        args.append(it);
    }
    return QString("%2").arg(args);
}
