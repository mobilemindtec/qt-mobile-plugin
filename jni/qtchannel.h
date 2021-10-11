#ifndef QTCHANNEL_H
#define QTCHANNEL_H

#include <QAndroidJniObject>
#include <QAndroidJniEnvironment>
#include <android/log.h>
#include <QtCore>
#include "qtchannelmessage.h"
#include "javalangobject.h"

class QtChannel : public JavaLangObject
{
private:
    static QtChannel * _instance;
    void registerNativeMethods() const;
public:
    QtChannel();
    QtChannel(QAndroidJniObject obj);

    static QtChannel * instance() { return QtChannel::_instance; }
    static const QString JavaClassName;

    void callMethod(QtChannelMessage &message) const;
    void callMethod(QString const &channelName, QString const &methodName, QtChannelMessage &message) const;

    static QtChannel newJavaObject();

signals:
    void messageReceived(QtChannelMessage &message);
};

#endif // QTCHANNEL_H
