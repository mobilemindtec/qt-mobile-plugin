#ifndef JAVAOBJECT_H
#define JAVAOBJECT_H

#include <QAndroidJniObject>
#include <QAndroidJniEnvironment>

class JavaLangObject
{

protected:
    bool _error;
    QString _errorMessage;
    QAndroidJniObject *jniObj;
public:
    JavaLangObject();
    JavaLangObject(QString const &errorMessage);
    ~JavaLangObject();
    explicit JavaLangObject(QAndroidJniObject jniObj);
    QAndroidJniObject* object();
    QString errorMessage() { return this->_errorMessage; };
    bool error() { return this->_error; };
    virtual void exceptionCheck();

    template <typename T>
    static T fromLocalRef(jobject obj);

    template <typename T>
    static T fromClass(QString const &clazzName, const char *sig, ...);

    template <typename T>
    static T fromClass(QString const &clazzName);

    QString toString();
};

class JavaLangThrowable : public JavaLangObject{
public:
    JavaLangThrowable() : JavaLangObject() {}
    JavaLangThrowable(QAndroidJniObject obj) : JavaLangObject(obj) {}
    QString getMessage();
    QString getStackTrace();
    void exceptionCheck() override;
};

class JavaUtilIterator : public JavaLangObject{
public:
    JavaUtilIterator() : JavaLangObject() {}
    JavaUtilIterator(QAndroidJniObject obj) : JavaLangObject(obj) {}
    void remove();
    JavaLangObject next();
    bool hasNext();
};

class JavaUtilCollection: public JavaLangObject{
public:
    JavaUtilCollection() : JavaLangObject() {}
    JavaUtilCollection(QAndroidJniObject obj) : JavaLangObject(obj){}
    int size();
    bool remove(JavaLangObject obj);
    bool contains(JavaLangObject obj);
    bool isEmpty();
    void clear();
    void add(JavaLangObject obj);
    JavaUtilIterator iterator();
    JavaLangObject * toArray();
};

class JavaUtilList : public JavaUtilCollection{
public:
    JavaUtilList() : JavaUtilCollection(){}
    JavaUtilList(QAndroidJniObject obj) : JavaUtilCollection(obj){}
    JavaLangObject get();
};

class JavaUtilSet : public JavaUtilCollection{
public:
    JavaUtilSet() : JavaUtilCollection() {}
    JavaUtilSet(QAndroidJniObject obj) : JavaUtilCollection(obj){}
};

class JavaUtilMapEntry : public JavaLangObject {
public:
    JavaUtilMapEntry() : JavaLangObject(){}
    JavaUtilMapEntry(QAndroidJniObject obj) : JavaLangObject(obj){}
    JavaLangObject getKey();
    JavaLangObject getValue();
    void setValue(JavaLangObject obj);
};

class JavaUtilMap : public JavaLangObject{
public:
    JavaUtilMap() : JavaLangObject(){}
    JavaUtilMap(QAndroidJniObject obj) : JavaLangObject(obj){}
    void clear();
    bool isEmpty();
    int size();
    JavaUtilSet keySet();
    JavaUtilSet entrySet();
    JavaUtilCollection values();
    JavaUtilMapEntry * entryArray();
    JavaLangObject * valuesArray();
    JavaLangObject * keyArray();
    JavaLangObject get(JavaLangObject key);
    JavaLangObject remove(JavaLangObject key);
    void put(JavaLangObject key, JavaLangObject value);
    void replace(JavaLangObject key, JavaLangObject value);
};

#endif // JAVAOBJECT_H
