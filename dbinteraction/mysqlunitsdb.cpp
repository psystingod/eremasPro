#include "mysqlunitsdb.h"

MysqlUnitsDB::MysqlUnitsDB()
{

}

QList<UnitsDB> MysqlUnitsDB::allUnits ( const QString &txtUnitName) {
    MysqlConnection* conn = new MysqlConnection();
    Setting *setting = new Setting ();
    QList<UnitsDB> list;
    QSqlQuery query;

    if ( conn->open( setting->getDatabasename() ) ) {
        if( txtUnitName.isEmpty() )
            query.prepare("SELECT * FROM system_inventory_units");
        else
            query.prepare( "SELECT * FROM system_inventory_units WHERE name LIKE '" + txtUnitName  + "'");

        query.exec();

        UnitsDB unitsDB;
        while (query.next()) {
            QString name = query.value(query.record().indexOf("name")).toString();
            QString unitName = query.value(query.record().indexOf("unit")).toString();

            unitsDB.setName(name);
            unitsDB.setUnitName(unitName);

            list.append(unitsDB);
        }
        query.finish();
        query.clear();
        conn->close();
    }
    return list;
}

void MysqlUnitsDB::addNewUnit (const QString &name, const QString &unitName) {
    MysqlConnection* conn = new MysqlConnection();
    Setting *setting = new Setting ();
    QSqlQuery query;

    if ( conn->open( setting->getDatabasename() ) ) {
        query.prepare( "INSERT INTO system_inventory_units (name, unit) VALUES (?, ?)" );
        query.bindValue(0, name);
        query.bindValue(1, unitName);
        query.exec();

        query.finish();
        query.clear();
        conn->close();
    }
}
