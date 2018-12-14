#ifndef MYSQLUNITSDB_H
#define MYSQLUNITSDB_H

#include <QList>
#include <QtSql>

#include "dbconnection/mysqlconnection.h"
#include "db/unitsdb.h"

class MysqlUnitsDB
{
public:
    MysqlUnitsDB();
    QList<UnitsDB> allUnits ( const QString& );
    void addNewUnit ( const QString&, const QString& );
};

#endif // MYSQLUNITSDB_H
