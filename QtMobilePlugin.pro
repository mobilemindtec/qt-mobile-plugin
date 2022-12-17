TEMPLATE = lib
TARGET = QtMobilePlugin
QT += core
CONFIG += c++17
DEFINES += QTMOBILEPLUGIN_LIBRARY
TARGET = $$qtLibraryTarget($$TARGET)

# Input
SOURCES += \
        javaiqtvariant.cpp \
        javaqtvariant.cpp \
        javaqtvariantconverter.cpp \
        javaqtvariantlist.cpp \
        javaqtvariantmap.cpp \
        jni/javalangobject.cpp \
        jni/javautilcollection.cpp \
        jni/javalangthrowable.cpp \
        jni/javautiliterator.cpp \
        jni/javautillist.cpp \
        jni/javautilmapentry.cpp \
        jni/javautilset.cpp \
        jni/javautilmap.cpp \
        jni/jniutil/jnimethodbuilder.cpp \
        jni/qtmobilepluginchannelmessage.cpp \
        jni/qtmobileplugindispatcher.cpp

HEADERS += \
        javaiqtvariant.h \
        QtMobilePluginMime \
        javaqtvariantlist.h \
        javaqtvariant.h \
        javaqtvariantconverter.h \
        javaqtvariantmap.h \
        jni/jniutil/javaclassnames.h \
        util/final_act.h \
        jni/javalangobject.h \
        jni/javautilcollection.h \
        jni/javalangthrowable.h \
        jni/javautiliterator.h \
        jni/javautillist.h \
        jni/javautilmapentry.h \
        jni/javautilset.h \
        jni/javautilmap.h \
        jni/jniutil/jnimethodbuilder.h \
        jni/qtmobilepluginchannelmessage.h \
        jni/qtmobileplugindispatcher.h


headers_jni.path += $$[QT_INSTALL_HEADERS]/QtMobilePlugin/jni
headers_jni.files += $$PWD/jni/*.h


headers_util.path += $$[QT_INSTALL_HEADERS]/QtMobilePlugin/util
headers_util.files += $$PWD/util/*.h

headers_jniutil.path += $$[QT_INSTALL_HEADERS]/QtMobilePlugin/jni/jniutil
headers_jniutil.files += $$PWD/jni/jniutil/*.h

headers.path += $$[QT_INSTALL_HEADERS]/QtMobilePlugin
headers.files += $$PWD/*.h $$PWD/QtMobilePluginMime




#headers.files = $$HEADERS
#headers.path = /usr/include/QtMobilePlugin

#unix {
#    target.path = /usr/lib/QtMobilePlugin
#}

INSTALLS += target headers headers_jni headers_util headers_jniutil


#CONFIG += install_ok  # Do not cargo-cult this!
