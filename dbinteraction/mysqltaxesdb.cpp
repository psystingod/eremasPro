#include "mysqltaxesdb.h"

MysqlTaxesDB::MysqlTaxesDB()
{

}

QList<TaxesDB> MysqlTaxesDB::allTaxes() {
    MysqlConnection* conn = new MysqlConnection();
    Setting *setting = new Setting ();
    QList<TaxesDB> list;
    QSqlQuery query;

    if ( conn->open( setting->getDatabasename() ) ) {
        query.prepare("SELECT * FROM system_taxes");
        query.exec();

        TaxesDB taxesDB;
        while (query.next()) {
            double iva = query.value(query.record().indexOf("iva")).toBool();
            double pac = query.value(query.record().indexOf("pac")).toBool();
            double cesc = query.value(query.record().indexOf("cesc")).toBool();

            taxesDB.setIva(iva);
            taxesDB.setPac(pac);
            taxesDB.setCesc(cesc);

            list.append(taxesDB);
        }
        query.finish();
        query.clear();
        conn->close();
    }
    return list;
}

QString MysqlTaxesDB::getTaxValue ( const QString &colValue) {

    QString taxValue = colValue.toLower();
    MysqlConnection* conn = new MysqlConnection();
    Setting *setting = new Setting ();
    QSqlQuery query;

    if ( conn->open( setting->getDatabasename() ) ) {
        query.prepare("SELECT " + taxValue + " FROM system_taxes");
        query.exec();

        while (query.next()) {
             taxValue = query.value(query.record().indexOf(taxValue)).toString();
        }

        query.finish();
        query.clear();
        conn->close();
    }
    return taxValue;
}

void MysqlTaxesDB::setTaxValue ( const QString &colValue, const QString &taxValue) {

    QString taxColumn = colValue.toLower();
    MysqlConnection* conn = new MysqlConnection();
    Setting *setting = new Setting ();
    QSqlQuery query;

    if ( conn->open( setting->getDatabasename() ) ) {
        query.prepare("UPDATE system_taxes SET " + taxColumn + " = ? ");
        query.bindValue(0, taxValue.toDouble());
        query.exec();

        query.finish();
        query.clear();
        conn->close();
    }
}
