#ifndef MYSQLACCOUNTINGCATALOGDB_H
#define MYSQLACCOUNTINGCATALOGDB_H

#include <QList>
#include <QtSql>

#include "dbconnection/mysqlconnection.h"
#include "db/accountingcatalogdb.h"

class MysqlAccountingCatalogDB
{
public:
  MysqlAccountingCatalogDB();
  QList<AccountingCatalogDB> allCatalog( QString );
  QList<AccountingCatalogDB> catalogParents ( );
  QList<AccountingCatalogDB> catalogByParent( QString );
  void newAccount ( QString, QString, QString, QString );
  QString getParentAccount ( int );
  void updateAccount( int, QString, QString, QString, QString );
};

#endif // MYSQLACCOUNTINGCATALOGDB_H
