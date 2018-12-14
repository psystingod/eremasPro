#include "mysqlwarehousedb.h"

MysqlWareHouseDB::MysqlWareHouseDB()
{

}

QList<WareHouseDB> MysqlWareHouseDB::allWareHouses ( QString warehouseName) {
    MysqlConnection* conn = new MysqlConnection();
    Setting *setting = new Setting ();
    QList<WareHouseDB> list;
    QSqlQuery query;

    if ( conn->open( setting->getDatabasename() ) ) {
        if (warehouseName.isEmpty())
            query.prepare("SELECT * FROM system_inventory_warehouses");
        else
            query.prepare("SELECT * FROM system_inventory_warehouses WHERE name LIKE '" + warehouseName + "'");
        query.exec();

        WareHouseDB wareHouseDB;
        while (query.next()) {
            QString name = query.value(query.record().indexOf("name")).toString();
            QString code = query.value(query.record().indexOf("code")).toString();
            QString address = query.value(query.record().indexOf("address")).toString();

            wareHouseDB.setName(name);
            wareHouseDB.setWareHouseId(code);
            wareHouseDB.setAddress(address);

            list.append(wareHouseDB);
        }
        query.finish();
        query.clear();
        conn->close();
    }
    return list;
}

void MysqlWareHouseDB::addNewWareHouse (const QString &name, const QString &address) {
    MysqlConnection* conn = new MysqlConnection();
    Setting *setting = new Setting ();
    QSqlQuery query;

    QString code = getWareHouseCode();

    if ( conn->open( setting->getDatabasename() ) ) {
        query.prepare( "INSERT INTO system_inventory_warehouses (name, code, address) VALUES (?, ?, ?)" );
        query.bindValue(0, name);
        query.bindValue(1, code);
        query.bindValue(2, address);

        if ( query.exec() )
          updateWareHouseCode(code);
        query.finish();
        query.clear();
        conn->close();
    }
}

  QString MysqlWareHouseDB::getWareHouseCode ( ) {
      QString code = "";
      MysqlConnection* conn = new MysqlConnection();
      Setting *setting = new Setting ();
      QSqlQuery query;

      if ( conn->open( setting->getDatabasename() ) ) {
          query.prepare("SELECT code FROM system_inventory_warehouse_code WHERE id = 1");
          query.exec();

          WareHouseDB wareHouseDB;
          while (query.next()) {
              code = query.value(query.record().indexOf("code")).toString();
          }
          query.finish();
          query.clear();
          conn->close();
      }

      return code;
  }

  void MysqlWareHouseDB::updateWareHouseCode ( QString &code ) {
      MysqlConnection* conn = new MysqlConnection();
      Setting *setting = new Setting ();
      QSqlQuery query;

      int counter = code.toInt();
      counter++;

      if (counter < 10)
          code = "0" + QVariant(counter).toString();

      if ( conn->open( setting->getDatabasename() ) ) {
          query.prepare("UPDATE system_inventory_warehouse_code SET code = ? WHERE id = 1");
          query.bindValue(0, code);
          query.exec();

          query.finish();
          query.clear();
          conn->close();
      }
  }
