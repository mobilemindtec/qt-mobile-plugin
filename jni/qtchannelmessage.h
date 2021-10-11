#ifndef QTCHANNELMESSAGE_H
#define QTCHANNELMESSAGE_H

#include "javalangobject.h"
#include "javalangthrowable.h"
#include "javautillist.h"
#include <QList>



class QtChannelMessage : public JavaLangObject
{
public:
    QtChannelMessage() : JavaLangObject() {}
    QtChannelMessage(QAndroidJniObject obj) : JavaLangObject(obj){}

    static const QString JavaClassName;

    static QtChannelMessage newJavaObject();
    static QtChannelMessage newJavaObject(QString const &channelName, QString const &methodName);

    QList<JavaLangObject> getData() const;
    JavaLangObject getFirstData() const;
    JavaLangObject getData(int const &index) const;
    void setId(QString const &id) const;
    QString getId() const;
    void setMethodName(QString const &methodName) const;
    QString getMethodName() const;
    void setChannelName(QString const &channelName) const;
    QString getChannelName() const;
    bool hasError() const;
    bool hasThrowable() const;
    JavaLangThrowable getThrowable() const;
    QString getErrorDescription() const;
    void addArg(JavaLangObject &arg) const;
    QtChannelMessage * withArg(JavaLangObject &arg);
     QString dump() const;
};

#endif // QTCHANNELMESSAGE_H
