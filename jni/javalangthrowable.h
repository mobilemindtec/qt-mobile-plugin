#ifndef JAVALANGTHROWABLE_H
#define JAVALANGTHROWABLE_H

#include "javalangobject.h"



class JavaLangThrowable{
private:
    QAndroidJniObject jniObj;
public:    
    JavaLangThrowable(QAndroidJniObject obj);
    QString getMessage();
    QString getStackTrace();  
    QAndroidJniObject object();

    static JavaLangThrowable fromLocalRef(jobject obj);
};


#endif // JAVALANGTHROWABLE_H
