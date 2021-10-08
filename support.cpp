#include "support.h"

JniMethodBuilder::JniMethodBuilder(){

}

JniMethodBuilder::~JniMethodBuilder(){
    //delete this->qualifiedArgs;
    //delete this->qualifiedReturn;
}

JniMethodBuilder* JniMethodBuilder::arg(QString const &fullyQualifiedName){
    this->qualifiedArgs << fullyQualifiedName;
}

JniMethodBuilder* JniMethodBuilder::addReturn(QString const &fullyQualifiedName){
    this->qualifiedReturn = fullyQualifiedName;
    return this;
}

char* JniMethodBuilder::build(){

    if(this->qualifiedReturn.isEmpty() || this->qualifiedReturn.isEmpty()){
        this->returnVoid();
    }

    if(this->qualifiedArgs.isEmpty()){
       QString value = QString("()%1").arg(this->qualifiedReturn);
       return value.toLatin1().data();
    }

    QString args;

    for(QString it : this->qualifiedArgs){
        args.append(it);
    }

    QString value = QString("(%1)%2").arg(args).arg(this->qualifiedReturn);
    return value.toLatin1().data();
}

char* JniMethodBuilder::buildConstructor(){

    QString args;

    for(QString it : this->qualifiedArgs){
        args.append(it);
    }

    QString value = QString("%2").arg(args);
    return value.toLatin1().data();
}

void JniMethodBuilder::clear(){
    this->qualifiedReturn = "";
    this->qualifiedArgs.clear();
}

JniMethodBuilder* JniMethodBuilder::empty(){
    this->clear();
    return this;
}

int JniMethodBuilder::callMethodJavaUtilCollection_Size(QAndroidJniObject const &obj){
    return obj.callMethod<jint>("size");
}

QAndroidJniObject JniMethodBuilder::callMethodJavaUtilMap_EntrySet(QAndroidJniObject const &obj){
    JniMethodBuilder* builer = new JniMethodBuilder();
    char* signature =  builer->returnSet()->noArgs()->build();
    QAndroidJniObject javaObj = obj.callObjectMethod("entrySet", signature);
    return javaObj;
}

QAndroidJniObject JniMethodBuilder::callMethodJavaUtilSet_ToArray(QAndroidJniObject const &obj){
    JniMethodBuilder* builer = new JniMethodBuilder();
    char* signature =  builer->returnArrayObject()->noArgs()->build();
    QAndroidJniObject javaObj = obj.callObjectMethod("toArray", signature);
    return javaObj;
}

QAndroidJniObject JniMethodBuilder::callMethodJavaUtilList_Get(QAndroidJniObject const &obj){
    JniMethodBuilder* builer = new JniMethodBuilder();
    char* signature =  builer->returnObject()->noArgs()->build();
    QAndroidJniObject javaObj = obj.callObjectMethod("get", signature);
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

Support::Support()
{

}
