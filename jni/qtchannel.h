#ifndef QTCHANNEL_H
#define QTCHANNEL_H

#include <QAndroidJniObject>
#include <QAndroidJniEnvironment>
#include <android/log.h>
#include <QtCore>
#include "qtchannelmessage.h"
#include "javalangobject.h"
#include "jni/jniutil/jnimethodbuilder.h"

class QtChannel : public JavaLangObject
{
    Q_OBJECT
private:
    static QtChannel* instance_;
    static QtChannel* newJavaObject();
    void registerNativeMethods();
public:
    QtChannel(){};
    QtChannel(QAndroidJniObject obj);
    QtChannel(const QtChannel & obj) : JavaLangObject(obj) {}
    QtChannel(const JavaLangObject & obj) : JavaLangObject(obj) {}

    static QtChannel* instance();
    static const QString kJavaClassName;
    const QString kTag = "QtChannel";

    void callMethod(QtChannelMessage &message);
    void callMethod(QString const &channelName, QString const &methodName, QtChannelMessage &message);



signals:
    void messageReceived(QtChannelMessage &message);
};

#endif // QTCHANNEL_H
