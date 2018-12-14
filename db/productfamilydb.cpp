#include "productfamilydb.h"
#include "dbinteraction/mysqlproductfamilydb.h"

ProductFamilyDB::ProductFamilyDB()
{
  name = "";
  abbreviated = "";
  code = "";
}

ProductFamilyDB::ProductFamilyDB( QString &nameLocal, QString &abbreviatedLocal, QString &codeLocal)
{
  name = nameLocal;
  abbreviated = abbreviatedLocal;
  code = codeLocal;
}

QString ProductFamilyDB::getName () {
    return name;
}

void ProductFamilyDB::setName (QString &nameLocal) {
    name = nameLocal;
}

QString ProductFamilyDB::getAbbreviated () {
    return abbreviated;
}

void ProductFamilyDB::setAbbreviated( QString &abbreviatedLocal) {
    abbreviated = abbreviatedLocal;
}

QString ProductFamilyDB::getCode () {
    return code;
}

void ProductFamilyDB::setCode (QString &codeLocal) {
    code = codeLocal;
}

QList<ProductFamilyDB> ProductFamilyDB::allProductFamily ( const QString &name ) {
    MysqlProductFamilyDB *mysqlProductFamilyDB = new MysqlProductFamilyDB();
    return mysqlProductFamilyDB->allProductFamily (name);
}

void ProductFamilyDB::addNewProductFamily ( const QString &name, const QString &code ) {
    MysqlProductFamilyDB *mysqlProductFamilyDB = new MysqlProductFamilyDB();
    mysqlProductFamilyDB->addNewProductFamily (name, code);
}
