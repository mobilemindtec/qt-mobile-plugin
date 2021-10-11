#ifndef QTMOBILEPLUGIN_PLUGIN_H
#define QTMOBILEPLUGIN_PLUGIN_H

#include <QQmlExtensionPlugin>

class QtMobilePlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)

public:
    void registerTypes(const char *uri) override;
};

#endif // QTMOBILEPLUGIN_PLUGIN_H
