#ifndef JAVALANGOBJECT_H
#define JAVALANGOBJECT_H

#include <QJniObject>
#include <QJniEnvironment>
#include <QString>
#include "jniutil/jnimethodbuilder.h"

class JavaLangObject : public QObject
{

private:
    bool _error;
    QString _errorMessage;
    QJniObject _jniObject;
public:
    explicit JavaLangObject();
    JavaLangObject(QString const &errorMessage);
    JavaLangObject(QJniObject jniObj);
    JavaLangObject(jobject obj);
    JavaLangObject(const JavaLangObject &o)
        : _error(o._error), _errorMessage(o._errorMessage), _jniObject(o._jniObject) {}
    virtual ~JavaLangObject();

    QJniObject getJniObject();
    void setJniObject(QJniObject);
    jobject getJavaObject();
    QString getErrorMessage() const;
    bool error() const;

    void exceptionCheck();

    JavaLangObject operator=(const JavaLangObject &obj){
        return JavaLangObject(obj);
    }

    QString toString();
    QString getJavaClassName();
    bool isValidJavaInstace();

    int hashCode();

    static JavaLangObject fromString(QString const &str);
    static JavaLangObject fromLocalRef(jobject obj);
    static JavaLangObject fromClass(QString const &clazzName, const char *sig, ...);
    static JavaLangObject fromClass(QString const &clazzName);
    static QString toQString(jstring const &str);
    //static char* toChar(QString const &str);
};







#endif // JAVALANGOBJECT_H
