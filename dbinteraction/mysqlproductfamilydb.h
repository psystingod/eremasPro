#ifndef MYSQLPRODUCTFAMILYDB_H
#define MYSQLPRODUCTFAMILYDB_H

#include <QList>
#include <QtSql>

#include "dbconnection/mysqlconnection.h"
#include "db/productfamilydb.h"

class MysqlProductFamilyDB
{
public:
  MysqlProductFamilyDB();
  QList<ProductFamilyDB> allProductFamily ( const QString& );
  void addNewProductFamily ( const QString&, const QString& );
  QString getProductFamilyCode ( );
  void updateProductFamilyCode ( QString& );
};

#endif // MYSQLPRODUCTFAMILYDB_H
