#ifndef JAVAUTILMAP_H
#define JAVAUTILMAP_H

#include "javalangobject.h"
#include "javautilmapentry.h"
#include "javautilset.h"
#include "jniutil/javaclassnames.h"
#include <QList>


class JavaUtilMap : public JavaLangObject{
public:
    JavaUtilMap() : JavaLangObject(){}
    JavaUtilMap(QJniObject obj) : JavaLangObject(obj){}
    JavaUtilMap(jobject obj): JavaLangObject(obj){}
    JavaUtilMap(const JavaUtilMap &obj) : JavaLangObject(obj){}
    JavaUtilMap(const JavaLangObject &obj) : JavaLangObject(obj){}
    void clear();
    bool isEmpty();
    int size();
    JavaUtilSet keySet();
    QList<JavaUtilMapEntry> entrySet();
    QList<JavaLangObject> values();
    JavaLangObject get(JavaLangObject &key);
    JavaLangObject get(const QString &key);
    JavaLangObject remove(JavaLangObject &key);
    JavaLangObject remove(const QString& key);

    void put(JavaLangObject  &key, JavaLangObject &value);
    void put(JavaLangObject  &key, QString const &value);
    void put(JavaLangObject  &key, int const &value);
    void put(JavaLangObject  &key, long const &value);
    void put(JavaLangObject  &key, bool const &value);
    void put(JavaLangObject  &key, double const &value);
    void put(JavaLangObject  &key, float const &value);

    void put(QString const &key, JavaLangObject &value);
    void put(QString const &key, QString const &value);
    void put(QString const &key, int const &value);
    void put(QString const &key, long const &value);
    void put(QString const &key, bool const &value);
    void put(QString const &key, double const &value);
    void put(QString const &key, float const &value);

    static JavaUtilMap newObject();

};


#endif // JAVAUTILMAP_H
