#include "mysqlinventorydb.h"

MysqlInventoryDB::MysqlInventoryDB()
{

}

QList<InventoryDB> MysqlInventoryDB::allInventory( QString searchText, int searchCode ) {
  MysqlConnection* conn = new MysqlConnection();
  Setting *setting = new Setting ();
  QList<InventoryDB> list;
  QSqlQuery query;
//qDebug() << searchText;
//qDebug() << searchCode;

  if ( conn->open( setting->getDatabasename() ) ) {

    switch (searchCode) {
      case 100:
        query.prepare("SELECT * FROM inventory WHERE code = '" + searchText + "'");
        break;
      case 101:
        query.prepare("SELECT * FROM inventory WHERE id = ?");
        qDebug() << searchText.toInt();
        query.bindValue(0, searchText.toInt());
        break;
      case 0:
        query.prepare( "SELECT * FROM inventory WHERE description LIKE '" + searchText  + "'" );
        break;
      case 1:
        query.prepare( "SELECT * FROM inventory WHERE code LIKE '" + searchText  + "'");
        break;

      default:
        query.prepare("SELECT * FROM inventory LIMIT 50");
        break;
      }
      query.exec();

      InventoryDB inventoryDB;
      while (query.next()) {
        int id = query.value(query.record().indexOf("id")).toInt();
        QString description = query.value(query.record().indexOf("description")).toString();
        int qty = query.value(query.record().indexOf("qty")).toInt();
        QString unit = query.value(query.record().indexOf("unit")).toString();
        QString group = query.value(query.record().indexOf("group")).toString();
        QString warehouse = query.value(query.record().indexOf("warehouse")).toString();
        QString code = query.value(query.record().indexOf("code")).toString();
        double price = query.value(query.record().indexOf("price")).toDouble();
        double cost = query.value(query.record().indexOf("cost")).toDouble();
        QString picture_path = query.value(query.record().indexOf("picture_path")).toString();
        int minimum = query.value(query.record().indexOf("minimum")).toInt();
        QDate ingress_date = query.value(query.record().indexOf("ingress_date")).toDate();
        QDate sale_date = query.value(query.record().indexOf("sale_date")).toDate();
        QString accounting_code = query.value(query.record().indexOf("accounting_code")).toString();

        inventoryDB.setId(id);
        inventoryDB.setDescription(description);
        inventoryDB.setQuantity(qty);
        inventoryDB.setUnit(unit);
        inventoryDB.setGroup(group);
        inventoryDB.setWarehouse(warehouse);
        inventoryDB.setCode(code);
        inventoryDB.setPrice(price);
        inventoryDB.setCost(cost);
        inventoryDB.setPicturePath(picture_path);
        inventoryDB.setMinimum(minimum);
        inventoryDB.setIngressDate(ingress_date);
        inventoryDB.setSaleDate(sale_date);
        inventoryDB.setAccountingCode(accounting_code);

        list.append(inventoryDB);
      }
      query.finish();
      query.clear();
      conn->close();
    }
    return list;
}

QList<InventoryDB> MysqlInventoryDB::productById( int localId ) {
  MysqlConnection* conn = new MysqlConnection();
  Setting *setting = new Setting ();
  QList<InventoryDB> list;
  QSqlQuery query;

  if ( conn->open( setting->getDatabasename() ) ) {
    query.prepare("SELECT * FROM inventory WHERE id = ?");
    query.bindValue(0, localId);
    query.exec();

    InventoryDB inventoryDB;
    while (query.next()) {
      int id = query.value(query.record().indexOf("id")).toInt();
      QString description = query.value(query.record().indexOf("description")).toString();
      QString unit = query.value(query.record().indexOf("unit")).toString();
      QString code = query.value(query.record().indexOf("code")).toString();
      double price = query.value(query.record().indexOf("price")).toDouble();

      inventoryDB.setId(id);
      inventoryDB.setDescription(description);
      inventoryDB.setUnit(unit);
      inventoryDB.setCode(code);
      inventoryDB.setPrice(price);
      list.append(inventoryDB);
    }
    query.finish();
    query.clear();
    conn->close();
  }
  return list;
}

void MysqlInventoryDB::addNewInventory ( QString description, int qty, QString unit, QString group, QString warehouse, QString code, double price, double cost, QString picture_path, QString accounting ) {

    MysqlConnection* conn = new MysqlConnection();
    Setting *setting = new Setting ();
    QSqlQuery query;

    if ( conn->open( setting->getDatabasename() ) ) {
        query.prepare( "INSERT INTO inventory (`description`, `qty`, `unit`, `group`, `warehouse`, `code`, `price`, `cost`, `picture_path`, `minimum`, `ingress_date`, `sale_date`, `accounting_code`) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)" );

        query.bindValue(0, description);
        query.bindValue(1, qty);
        query.bindValue(2, unit);
        query.bindValue(3, group);
        query.bindValue(4, warehouse);
        query.bindValue(5, code);
        query.bindValue(6, price);
        query.bindValue(7, cost);
        query.bindValue(8, picture_path);
        query.bindValue(9, 0);
        query.bindValue(10, QDate::currentDate());
        query.bindValue(11, QDate::currentDate());
        query.bindValue(12, accounting);

        query.exec();

        query.finish();
        query.clear();
        conn->close();
    }
}
