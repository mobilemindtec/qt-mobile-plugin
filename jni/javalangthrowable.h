#ifndef JAVALANGTHROWABLE_H
#define JAVALANGTHROWABLE_H

#include <QJniObject>
#include "javalangobject.h"

class JavaLangThrowable{
private:
    QJniObject _jniObj;
public:    
    JavaLangThrowable(QJniObject obj);
    JavaLangThrowable(const JavaLangThrowable &o) : _jniObj(o._jniObj) {}
    QString getMessage() const;
    QString getStackTrace() const;
    QJniObject getJniObject();

    static JavaLangThrowable fromLocalRef(jobject obj);

};


#endif // JAVALANGTHROWABLE_H
