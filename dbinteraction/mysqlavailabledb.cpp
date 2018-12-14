/*
 * Class just for generate the list of DB available schemma
*/

#include "mysqlavailabledb.h"
#include "dbconnection/mysqlconnection.h"

MysqlAvailableDB::MysqlAvailableDB()
{

}

QList<AvailableDB> MysqlAvailableDB::allDB() {
    MysqlConnection* conn = new MysqlConnection();
    conn->open("");

    QList<AvailableDB> list;
    QSqlQuery query("SELECT SCHEMA_NAME AS `databasename` FROM INFORMATION_SCHEMA.SCHEMATA WHERE SCHEMA_NAME LIKE 'eremas%'");
    int fieldNo = query.record().indexOf("databasename");

    while (query.next()) {
        AvailableDB availableDB;
        QString databasename = query.value(fieldNo).toString();
        availableDB.setDatabaseName(databasename);
        list.append(availableDB);
    }

    query.finish();
    query.clear();
    conn->close();
    return list;
}

