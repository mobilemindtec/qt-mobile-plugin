#include "firebaseplugin_plugin.h"

#include "firebasemodel.h"

#include <qqml.h>

void FirebasePluginPlugin::registerTypes(const char *uri)
{
    // @uri br.com.mobilemind.qt.firebase
    qmlRegisterType<FirebaseModel>(uri, 1, 0, "FirebasePlugin");
}

