#ifndef QTMOBILEPLUGINCHANNELMESSAGE_H
#define QTMOBILEPLUGINCHANNELMESSAGE_H

#include "javalangobject.h"
#include "javalangthrowable.h"
#include "javautillist.h"
#include "jniutil/javaclassnames.h"
#include <QList>



class QtMobilePluginChannelMessage : public JavaLangObject
{
    Q_OBJECT

public:
    explicit QtMobilePluginChannelMessage() : JavaLangObject() {}
    QtMobilePluginChannelMessage(QJniObject obj) : JavaLangObject(obj){}
    QtMobilePluginChannelMessage(const QString  &errorMessage) : JavaLangObject(errorMessage){};
    QtMobilePluginChannelMessage(jobject obj) : JavaLangObject(obj){};
    QtMobilePluginChannelMessage(const QtMobilePluginChannelMessage & obj) : JavaLangObject(obj) {}
    QtMobilePluginChannelMessage(const JavaLangObject & obj) : JavaLangObject(obj) {}

    static const QString kJavaClassName;

    static QtMobilePluginChannelMessage * newJavaObject();
    static QtMobilePluginChannelMessage * newJavaObject(QString const &channelName, QString const &methodName);

    QList<JavaLangObject> getData();
    JavaLangObject getData(int const &index);
    JavaLangObject getData(int const &index, const QString& methodSignature);
    JavaLangObject getFirstData();

    void setId(QString const &id);
    QString getId();

    void setMethodName(QString const &methodName);
    QString getMethodName();

    void setChannelName(QString const &channelName);
    QString getChannelName();

    JavaLangThrowable getThrowable();
    QString getErrorDescription();

    bool hasError();
    bool hasThrowable();

    void addArg(JavaLangObject &arg);

    QtMobilePluginChannelMessage* withArg(JavaLangObject &arg);
    QtMobilePluginChannelMessage* withArg(const QString &arg);

    QString dump();

};

// need to use signals & slots
Q_DECLARE_METATYPE(QtMobilePluginChannelMessage)
Q_DECLARE_METATYPE(QtMobilePluginChannelMessage*)
//Q_DECLARE_METATYPE(QtMobilePluginChannelMessage&)

#endif // QTMOBILEPLUGINCHANNELMESSAGE_H
