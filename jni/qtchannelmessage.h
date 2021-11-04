#ifndef QTCHANNELMESSAGE_H
#define QTCHANNELMESSAGE_H

#include "javalangobject.h"
#include "javalangthrowable.h"
#include "javautillist.h"
#include <QList>



class QtChannelMessage : public JavaLangObject
{
    Q_OBJECT


public:
    explicit QtChannelMessage() : JavaLangObject() {}
    QtChannelMessage(QAndroidJniObject obj) : JavaLangObject(obj){}
    QtChannelMessage(QString const &errorMessage) : JavaLangObject(errorMessage){};
    QtChannelMessage(jobject obj) : JavaLangObject(obj){};
    QtChannelMessage(const QtChannelMessage & obj) : JavaLangObject(obj) {}
    QtChannelMessage(const JavaLangObject & obj) : JavaLangObject(obj) {}

    static const QString kJavaClassName;

    static QtChannelMessage * newJavaObject();
    static QtChannelMessage * newJavaObject(QString const &channelName, QString const &methodName);

    QList<JavaLangObject> getData();
    JavaLangObject getFirstData();
    JavaLangObject getData(int const &index);
    JavaLangObject getData(int const &index, const char* methodSignature);
    void setId(QString const &id);
    QString getId();
    void setMethodName(QString const &methodName);
    QString getMethodName();
    void setChannelName(QString const &channelName);
    QString getChannelName();
    bool hasError();
    bool hasThrowable();
    JavaLangThrowable getThrowable();
    QString getErrorDescription();
    void addArg(JavaLangObject &arg);
    QtChannelMessage* withArg(JavaLangObject &arg);
    QtChannelMessage* withArg(QString const &arg);
    QString dump();
};

 Q_DECLARE_METATYPE(QtChannelMessage)

#endif // QTCHANNELMESSAGE_H
