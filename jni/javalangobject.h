#ifndef JAVALANGOBJECT_H
#define JAVALANGOBJECT_H

#include <QAndroidJniObject>
#include <QAndroidJniEnvironment>
#include <QString>
#include "jniutil/jnimethodbuilder.h"

class JavaLangObject : public QObject
{

private:
    bool _error;
    QString _errorMessage;
    QAndroidJniObject _jniObject;
public:
    explicit JavaLangObject();
    JavaLangObject(QString const &errorMessage);
    JavaLangObject(QAndroidJniObject jniObj);
    JavaLangObject(jobject obj);
    JavaLangObject(const JavaLangObject &o)
        : _error(o._error), _errorMessage(o._errorMessage), _jniObject(o._jniObject) {}
    virtual ~JavaLangObject();

    QAndroidJniObject getJniObject();
    void setJniObject(QAndroidJniObject);
    jobject getJavaObject();
    QString getErrorMessage();
    bool error();

    void exceptionCheck();

    static JavaLangObject fromLocalRef(jobject obj);
    static JavaLangObject fromClass(QString const &clazzName, const char *sig, ...);
    static JavaLangObject fromClass(QString const &clazzName);
    static QString toQString(jstring const &str);
    static char* toChar(QString const &str);


    JavaLangObject operator=(const JavaLangObject &obj){
        return JavaLangObject(obj);
    }

    QString toString();
    int hashCode();
};







#endif // JAVALANGOBJECT_H
