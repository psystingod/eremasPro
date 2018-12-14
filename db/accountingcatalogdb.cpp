#include "accountingcatalogdb.h"
#include "dbinteraction/mysqlaccountingcatalogdb.h"

AccountingCatalogDB::AccountingCatalogDB()
{
  code = "";
  parent = "";
  name = "";
  classification = "";
}

int AccountingCatalogDB::getId( ) {
  return id;
}

void AccountingCatalogDB::setId (int idLocal) {
  id = idLocal;
}

QString AccountingCatalogDB::getCode ( ) {
  return code;
}

void AccountingCatalogDB::setCode ( QString codeLocal ) {
  code = codeLocal;
}

QString AccountingCatalogDB::getParent ( ) {
  return parent;
}

void AccountingCatalogDB::setParent ( QString parentLocal ) {
  parent = parentLocal;
}

QString AccountingCatalogDB::getName ( ) {
  return name;
}

void AccountingCatalogDB::setName ( QString nameLocal ) {
  name = nameLocal;
}

QString AccountingCatalogDB::getClassification ( ) {
  return classification;
}

void AccountingCatalogDB::setClassification ( QString classificationLocal ) {
  classification = classificationLocal;
}

QList<AccountingCatalogDB> AccountingCatalogDB::allCatalog ( QString name ) {
  MysqlAccountingCatalogDB *mysqlCatalogDB = new MysqlAccountingCatalogDB();
  return mysqlCatalogDB->allCatalog(name);
}

void AccountingCatalogDB::addNewAccount ( QString code, QString parent, QString name, QString classification ) {
  MysqlAccountingCatalogDB *mysqlCatalogDB = new MysqlAccountingCatalogDB();
  mysqlCatalogDB->newAccount (code, parent, name, classification);
}

QString AccountingCatalogDB::getParentAccount ( int id ) {
  MysqlAccountingCatalogDB *mysqlCatalogDB = new MysqlAccountingCatalogDB();
  return mysqlCatalogDB->getParentAccount( id );
}

void AccountingCatalogDB::updateAccount ( int id, QString code, QString parent, QString name, QString classification) {
  MysqlAccountingCatalogDB *mysqlCatalogDB = new MysqlAccountingCatalogDB();
  mysqlCatalogDB->updateAccount(id, code, parent, name, classification);
}
