#include "taxesdb.h"
#include "dbinteraction/mysqltaxesdb.h"

TaxesDB::TaxesDB()
{
    iva = 0;
    pac = 0;
    cesc = 0;
}

TaxesDB::TaxesDB(double &ivaLocal, double &pacLocal, double &cescLocal ) {
    iva = ivaLocal;
    pac = pacLocal;
    cesc = cescLocal;
}

double TaxesDB::getIva () {
    return iva;
}

void TaxesDB::setIva (double &ivaLocal) {
    iva = ivaLocal;
}

double TaxesDB::getPac () {
    return pac;
}

void TaxesDB::setPac (double &pacLocal) {
    pac = pacLocal;
}

double TaxesDB::getCesc() {
    return cesc;
}

void TaxesDB::setCesc (double &cescLocal) {
    cesc = cescLocal;
}

QList<TaxesDB> TaxesDB::allTaxes() {
    MysqlTaxesDB *mysqlTaxesDB = new MysqlTaxesDB();
    return mysqlTaxesDB->allTaxes();
}

QString TaxesDB::getTaxValue( const QString &taxColumn ) {
    MysqlTaxesDB *mysqlTaxesDB = new MysqlTaxesDB();
    return mysqlTaxesDB->getTaxValue( taxColumn );
}

void TaxesDB::setTaxValue( const QString &taxColumn, const QString &taxValue ) {
    MysqlTaxesDB *mysqlTaxesDB = new MysqlTaxesDB();
    return mysqlTaxesDB->setTaxValue( taxColumn, taxValue );
}


