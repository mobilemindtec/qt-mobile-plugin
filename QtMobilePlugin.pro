TEMPLATE = lib
TARGET = QtMobilePlugin
QT += qml quick androidextras
CONFIG += plugin c++11 qmltypes

QML_IMPORT_NAME = QtMobilePlugin
QML_IMPORT_MAJOR_VERSION = 1.0

DESTDIR = imports/$$QML_IMPORT_NAME

TARGET = $$qtLibraryTarget($$TARGET)
uri = com.qt.plugin

# Input
SOURCES += \
        jni/javalangobject.cpp \
        jni/javautilcollection.cpp \
        jni/javalangthrowable.cpp \
        jni/javautiliterator.cpp \
        jni/javautillist.cpp \
        jni/javautilmapentry.cpp \
        jni/javautilset.cpp \
        jni/javautilmap.cpp \
        jni/jniutil/jnimethodbuilder.cpp \
        jni/qtchannelmessage.cpp \
        jni/qtchannel.cpp \
        firebasefirestoremodel.cpp \
        qtmobile_plugin.cpp

HEADERS += \
        jni/javalangobject.h \
        jni/javautilcollection.h \
        jni/javalangthrowable.h \
        jni/javautiliterator.h \
        jni/javautillist.h \
        jni/javautilmapentry.h \
        jni/javautilset.h \
        jni/javautilmap.h \
        jni/jniutil/jnimethodbuilder.h \
        jni/qtchannelmessage.h \
        jni/qtchannel.h \
        firebasefirestoremodel.h \
        qtmobile_plugin.h

PLUGINFILES += \
    imports/$$QML_IMPORT_NAME/plugin.qml \
    imports/$$QML_IMPORT_NAME/qmldir

DISTFILES += $$PLUGINFILES \
    android/src/com/qt/plugin/core/QChannelImpl.java \
    android/src/com/qt/plugin/core/QtChannel.java \
    android/src/com/qt/plugin/core/QtChannelMessage.java


#!equals(_PRO_FILE_PWD_, $$OUT_PWD) {
#    copy_qmldir.target = $$OUT_PWD/qmldir
#    copy_qmldir.depends = $$_PRO_FILE_PWD_/qmldir
#    copy_qmldir.commands = $(COPY_FILE) "$$replace(copy_qmldir.depends, /, $$QMAKE_DIR_SEP)" "$$replace(copy_qmldir.target, /, $$QMAKE_DIR_SEP)"
#    QMAKE_EXTRA_TARGETS += copy_qmldir
#    PRE_TARGETDEPS += $$copy_qmldir.target
#}
#
#qmldir.files = qmldir
#unix {
#    installPath = $$[QT_INSTALL_QML]/$$replace(uri, \., /)
#    qmldir.path = $$installPath
#    target.path = $$installPath
#    INSTALLS += target qmldir
#}

android {
    ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

    DISTFILES += \
        android/build.gradle \
    android/src/com/qt/plugin/firebase/QtFirebaseFirestore.java
        #android/gradle/wrapper/gradle-wrapper.properties \
        #android/AndroidManifest.xml \
        #android/res/values/libs.xml \
}

target.path = $$[QT_INSTALL_QML]/$$QML_IMPORT_NAME

pluginfiles_copy.files = $$PLUGINFILES
pluginfiles_copy.path = $$DESTDIR

pluginfiles_install.files = $$PLUGINFILES $$OUT_PWD/$$DESTDIR/plugins.qmltypes
pluginfiles_install.path = $$[QT_INSTALL_QML]/$$QML_IMPORT_NAME


INSTALLS += target pluginfiles_install
COPIES += pluginfiles_copy

OTHER_FILES += $$PLUGINFILES


CONFIG += install_ok  # Do not cargo-cult this!
