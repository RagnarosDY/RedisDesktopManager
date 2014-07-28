#include "test_databaseitem.h"
#include "items/databaseitem.h"
#include "itemoperationsmock.h"

#include <QtCore>
#include <QTest>
#include <QSignalSpy>

using namespace ConnectionsTree;

TestDatabaseItem::TestDatabaseItem(QObject *parent) :
    QObject(parent)
{
}

void TestDatabaseItem::testLoadKeys()
{
    //given
    ItemOperationsMock* operations = new ItemOperationsMock();
    operations->keys.append("test-1-key");
    operations->keys.append("test-2-key");
    operations->keys.append("test-2-key:subkey");
    operations->keys.append("test-2-key:namespace:subkey2");
    DatabaseItem item("test", 0, 300,
                      QSharedPointer<Operations>(dynamic_cast<Operations*>(operations)),
                      nullptr);    
    QSignalSpy spy(&item, SIGNAL(keysLoaded()));

    //when
    item.loadKeys();

    //then
    QCOMPARE(spy.wait(), true);
    QCOMPARE(spy.count(), 1);
    QCOMPARE(item.childCount(), (unsigned int)3);
}