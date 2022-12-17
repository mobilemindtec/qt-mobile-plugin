#ifndef QTMOBILEPLUGINDISPATCHER_H
#define QTMOBILEPLUGINDISPATCHER_H

#include <QJniObject>
#include <QJniEnvironment>
#include <android/log.h>
#include <QtCore>
#include "qtmobilepluginchannelmessage.h"
#include "jniutil/javaclassnames.h"
#include "javalangobject.h"
#include "../util/final_act.h"

class QtMobilePluginDispatcher : public JavaLangObject
{
    Q_OBJECT
private:
    static QtMobilePluginDispatcher* instance_;
    static QtMobilePluginDispatcher* newJavaObject();
    void registerNativeMethods();
public:
    QtMobilePluginDispatcher(){};
    QtMobilePluginDispatcher(QJniObject obj);
    QtMobilePluginDispatcher(const QtMobilePluginDispatcher & obj) : JavaLangObject(obj) {}
    QtMobilePluginDispatcher(const JavaLangObject & obj) : JavaLangObject(obj) {}

    static QtMobilePluginDispatcher* instance();
    static const QString kJavaClassName;
    const QString kTag = "QtMobilePluginDispatcher";

    void dispatch(QtMobilePluginChannelMessage* message);



signals:
    void messageReceived(QtMobilePluginChannelMessage* message);
};

#endif // QTMOBILEPLUGINDISPATCHER_H
