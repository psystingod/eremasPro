#include "mysqlaccountingcatalogdb.h"

MysqlAccountingCatalogDB::MysqlAccountingCatalogDB()
{

}

QList<AccountingCatalogDB> MysqlAccountingCatalogDB::allCatalog ( QString txtAccountName) {
    MysqlConnection* conn = new MysqlConnection();
    Setting *setting = new Setting ();
    QList<AccountingCatalogDB> list;
    QSqlQuery query;

    if ( conn->open( setting->getDatabasename() ) ) {
        if( txtAccountName.isEmpty() )
            query.prepare( "SELECT * FROM accounting_catalog ORDER BY COALESCE(code, parent), parent" );
        else
            query.prepare( "SELECT * FROM accounting_catalog WHERE name LIKE '" + txtAccountName  + "'" );

        query.exec();

        AccountingCatalogDB catalogDB;
        while (query.next()) {
            int  id= query.value(query.record().indexOf("id")).toInt();
            QString code = query.value(query.record().indexOf("code")).toString();
            QString parent = query.value(query.record().indexOf("parent")).toString();
            QString name = query.value(query.record().indexOf("name")).toString();
            QString classification = query.value(query.record().indexOf("classification")).toString();

            catalogDB.setId(id);
            catalogDB.setCode(code);
            catalogDB.setParent(parent);
            catalogDB.setName(name);
            catalogDB.setClassification(classification);

            list.append(catalogDB);
        }
        query.finish();
        query.clear();
        conn->close();
    }
    return list;
}

void MysqlAccountingCatalogDB::newAccount (QString code, QString parent, QString name, QString classification) {
    MysqlConnection* conn = new MysqlConnection();
    Setting *setting = new Setting ();
    QSqlQuery query;

    if ( conn->open( setting->getDatabasename() ) ) {
        query.prepare( "INSERT INTO accounting_catalog (code, parent, name, classification) VALUES (?, ?, ?, ?)" );
        query.bindValue(0, code);
        query.bindValue(1, parent);
        query.bindValue(2, name);
        query.bindValue(3, classification);
        query.exec();

        query.finish();
        query.clear();
        conn->close();
    }
}

QString MysqlAccountingCatalogDB::getParentAccount(int id) {
  MysqlConnection* conn = new MysqlConnection();
  Setting *setting = new Setting ();
  QString parent;
  QSqlQuery query;

  if ( conn->open( setting->getDatabasename() ) ) {
      query.prepare( "SELECT code FROM accounting_catalog WHERE id = ? " );
      query.bindValue(0, id);
      query.exec();

      while (query.next()) {
        parent = query.value(query.record().indexOf("code")).toString();
      }

      query.finish();
      query.clear();
      conn->close();
  }
  return parent;
}

void MysqlAccountingCatalogDB::updateAccount(int id, QString code, QString parent, QString name, QString classification) {
  MysqlConnection* conn = new MysqlConnection();
  Setting *setting = new Setting ();
  QSqlQuery query;

  if ( conn->open( setting->getDatabasename() ) ) {
      query.prepare( "UPDATE accounting_catalog SET code = ?, parent = ?, name = ?, classification = ? WHERE id = ? " );
      query.bindValue(0, code);
      query.bindValue(1, parent);
      query.bindValue(2, name);
      query.bindValue(3, classification);
      query.bindValue(4, id);
      query.exec();

      query.finish();
      query.clear();
      conn->close();
  }
}
