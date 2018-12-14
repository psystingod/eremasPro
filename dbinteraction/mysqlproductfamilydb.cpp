#include "mysqlproductfamilydb.h"

MysqlProductFamilyDB::MysqlProductFamilyDB()
{

}

QList<ProductFamilyDB> MysqlProductFamilyDB::allProductFamily ( const QString &productName) {
    MysqlConnection* conn = new MysqlConnection();
    Setting *setting = new Setting ();
    QList<ProductFamilyDB> list;
    QSqlQuery query;

    if ( conn->open( setting->getDatabasename() ) ) {
        if (productName.isEmpty())
            query.prepare("SELECT * FROM system_inventory_product_family");
        else
            query.prepare("SELECT * FROM system_inventory_product_family WHERE name LIKE '" + productName + "'");
        query.exec();

        ProductFamilyDB productFamilyDB;
        while (query.next()) {
            QString name = query.value(query.record().indexOf("name")).toString();
            QString abbreviated = query.value(query.record().indexOf("abbreviated")).toString();
            QString code = query.value(query.record().indexOf("code")).toString();

            productFamilyDB.setName(name);
            productFamilyDB.setAbbreviated(abbreviated);
            productFamilyDB.setCode(code);

            list.append(productFamilyDB);
        }
        query.finish();
        query.clear();
        conn->close();
    }
    return list;
}

void MysqlProductFamilyDB::addNewProductFamily (const QString &name, const QString &abbreviated ) {
    MysqlConnection* conn = new MysqlConnection();
    Setting *setting = new Setting ();
    QSqlQuery query;

    QString code = getProductFamilyCode();

    if ( conn->open( setting->getDatabasename() ) ) {
        query.prepare( "INSERT INTO system_inventory_product_family (name, abbreviated, code) VALUES (?, ?, ?)" );
        query.bindValue(0, name);
        query.bindValue(1, abbreviated);
        query.bindValue(2, code);

        if( query.exec() )
          updateProductFamilyCode(code);

        query.finish();
        query.clear();
        conn->close();
    }
}

QString MysqlProductFamilyDB::getProductFamilyCode ( ) {
    QString code = "";
    MysqlConnection* conn = new MysqlConnection();
    Setting *setting = new Setting ();
    QSqlQuery query;

    if ( conn->open( setting->getDatabasename() ) ) {
        query.prepare("SELECT code FROM system_inventory_family_code WHERE id = 1");
        query.exec();

        while (query.next()) {
            code = query.value(query.record().indexOf("code")).toString();
        }
        query.finish();
        query.clear();
        conn->close();
    }
    return code;
}

void MysqlProductFamilyDB::updateProductFamilyCode ( QString &code ) {
    MysqlConnection* conn = new MysqlConnection();
    Setting *setting = new Setting ();
    QSqlQuery query;

    int counter = code.toInt();
    counter++;

    if (counter < 10)
        code = "0" + QVariant(counter).toString();

    if ( conn->open( setting->getDatabasename() ) ) {
        query.prepare("UPDATE system_inventory_family_code SET code = ? WHERE id = 1");
        query.bindValue(0, code);
        query.exec();

        query.finish();
        query.clear();
        conn->close();
    }
}
