#ifndef FIREBASEPLUGIN_PLUGIN_H
#define FIREBASEPLUGIN_PLUGIN_H

#include <QQmlExtensionPlugin>

class FirebasePluginPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)

public:
    void registerTypes(const char *uri) override;
};

#endif // FIREBASEPLUGIN_PLUGIN_H
