#ifndef JAVALANGTHROWABLE_H
#define JAVALANGTHROWABLE_H

#include "javalangobject.h"



class JavaLangThrowable{
private:
    QAndroidJniObject _jniObj;
public:    
    JavaLangThrowable(QAndroidJniObject obj);
    JavaLangThrowable(const JavaLangThrowable &o) : _jniObj(o._jniObj) {}
    QString getMessage();
    QString getStackTrace();  
    QAndroidJniObject getJniObject();

    static JavaLangThrowable fromLocalRef(jobject obj);
};


#endif // JAVALANGTHROWABLE_H
