#include "db/availabledb.h"
#include "dbinteraction/mysqlavailabledb.h"

AvailableDB::AvailableDB()
{
    databasename = "";
}

AvailableDB::AvailableDB( const QString &dataBasename ) {
    databasename = dataBasename;
}

QString AvailableDB::getDatabaseName( ) {
    return databasename;
}

void AvailableDB::setDatabaseName(const QString &dataBasename) {
    databasename = dataBasename;
}

QList<AvailableDB> AvailableDB::allDB() {
    MysqlAvailableDB *mysqlAvailableDB = nullptr;

    return mysqlAvailableDB->allDB();
}
