

#include <QtCore>
#include <QTest>

#include <QtMobilePlugin/QtMobilePluginMime>

class MyTest : public QObject {
    Q_OBJECT

public:

public slots:
    void testJavaObject();
};

void MyTest::testJavaObject() {
    auto obj = JavaLangObject::fromClass(kJavaLangObject);
    QVERIFY(obj.getJavaClassName() == "java.lang.Object");
}


QTEST_MAIN(MyTest)
#include "mytest.moc"
