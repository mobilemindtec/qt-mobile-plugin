#include "qtmobile_plugin.h"

#include "firebasefirestoremodel.h"

#include <qqml.h>

void QtMobilePlugin::registerTypes(const char *uri)
{
    // @uri br.com.mobilemind.qt.firebase
    qmlRegisterType<FirebaseFirestoreModel>(uri, 1, 0, "FirebasePlugin");
}

