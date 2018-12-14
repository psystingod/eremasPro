#include "inventorydb.h"
#include "dbinteraction/mysqlinventorydb.h"

InventoryDB::InventoryDB()
{
  id = 0;
  description = "";
  qty = 0;
  unit = "";
  group = "";
  warehouse = "";
  code = "";
  price = 0;
  cost = 0;
  picture_path = "";
  minimum = 0;
  QDate ingress_date (0000,00,00);
  QDate sale_date (0000,00,00);
  accounting_code = "";
}

int InventoryDB::getId () {
  return id;
}

void InventoryDB::setId (int &idLocal) {
  id = idLocal;
}

QString InventoryDB::getDescription () {
  return description;
}

void InventoryDB::setDescription ( QString &descriptionLocal ) {
  description = descriptionLocal;
}

int InventoryDB::getQuantity () {
  return qty;
}

void InventoryDB::setQuantity( int &quantityLocal) {
  qty = quantityLocal;
}

QString InventoryDB::getUnit () {
  return unit;
}

void InventoryDB::setUnit ( QString &unitLocal ) {
  unit = unitLocal;
}

QString InventoryDB::getGroup () {
  return group;
}

void InventoryDB::setGroup (QString &groupLocal) {
  group = groupLocal;
}

QString InventoryDB::getWarehouse () {
  return warehouse;
}

void InventoryDB::setWarehouse ( QString &warehouseLocal ) {
  warehouse = warehouseLocal;
}

QString InventoryDB::getCode () {
  return code;
}

void InventoryDB::setCode (QString &codeLocal) {
  code = codeLocal;
}

double InventoryDB::getPrice () {
  return price;
}

void InventoryDB::setPrice ( double &priceLocal) {
  price = priceLocal;
}

double InventoryDB::getCost () {
  return cost;
}

void InventoryDB::setCost ( double &costLocal) {
  price = costLocal;
}

QString InventoryDB::getPicturePath () {
  return picture_path;
}

void InventoryDB::setPicturePath( QString &picture_pathLocal) {
  picture_path = picture_pathLocal;
}

int InventoryDB::getMinimum () {
  return minimum;
}

void InventoryDB::setMinimum ( int &minimumLocal) {
  minimum = minimumLocal;
}

QDate InventoryDB::getIngressDate () {
  return ingress_date;
}

void InventoryDB::setIngressDate ( QDate &ingress_dateLocal ) {
  ingress_date = ingress_dateLocal;
}

QDate InventoryDB::getSaleDate () {
  return sale_date;
}

void InventoryDB::setSaleDate ( QDate &sale_dateLocal ) {
  sale_date = sale_dateLocal;
}

QString InventoryDB::getAccountingCode () {
  return accounting_code;
}

void InventoryDB::setAccountingCode ( QString &accounting_codeLocal ) {
  accounting_code = accounting_codeLocal;
}

QList<InventoryDB> InventoryDB::allInventory(const QString &searchText, const int &searchCode) {
  MysqlInventoryDB *mysqlInventoryDB = new MysqlInventoryDB ();
  return mysqlInventoryDB->allInventory(searchText, searchCode);
}

QList<InventoryDB> InventoryDB::productById ( const int &id ) {
  MysqlInventoryDB *mysqlInventoryDB = new MysqlInventoryDB ();
  return mysqlInventoryDB->productById( id );
}

void InventoryDB::addNewProduct( QString description, int qty, QString unit, QString group, QString warehouse, QString code, double price, double cost, QString picture_path, QString accounting) {
  MysqlInventoryDB *mysqlInventoryDB = new MysqlInventoryDB ();
  mysqlInventoryDB->addNewInventory( description, qty, unit, group, warehouse, code, price, cost, picture_path, accounting );
}

