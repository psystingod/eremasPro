#ifndef MYSQLINVENTORYDB_H
#define MYSQLINVENTORYDB_H

#include <QList>
#include <QtSql>

#include "dbconnection/mysqlconnection.h"
#include "db/inventorydb.h"

class MysqlInventoryDB
{
public:
  MysqlInventoryDB();
  QList<InventoryDB> allInventory ( QString, int );
  QList<InventoryDB> productById ( int );
  void addNewInventory ( QString, int, QString, QString, QString, QString, double, double, QString, QString );
};

#endif // MYSQLINVENTORYDB_H
