#ifndef JAVALANGOBJECT_H
#define JAVALANGOBJECT_H

#include <QAndroidJniObject>
#include <QAndroidJniEnvironment>
#include <QString>
#include "jniutil/jnimethodbuilder.h"

class JavaLangObject
{

protected:
    bool _error;
    QString _errorMessage;
    QAndroidJniObject *jniObj;
public:
    JavaLangObject();
    JavaLangObject(QString const &errorMessage);
    ~JavaLangObject();
    explicit JavaLangObject(QAndroidJniObject jniObj);
    QAndroidJniObject* object();
    QString errorMessage() { return this->_errorMessage; };
    bool error() { return this->_error; };
    virtual void exceptionCheck();

    template <typename T>
    static T fromLocalRef(jobject obj);

    template <typename T>
    static T fromClass(QString const &clazzName, const char *sig, ...);

    template <typename T>
    static T fromClass(QString const &clazzName);

    template <typename T>
    T cast();


    QString toString();

    static QString convertJavaString(jstring const &str);
};








#endif // JAVALANGOBJECT_H
