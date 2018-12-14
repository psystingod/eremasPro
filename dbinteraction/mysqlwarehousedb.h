#ifndef MYSQLWAREHOUSEDB_H
#define MYSQLWAREHOUSEDB_H

#include <QList>
#include <QtSql>

#include "dbconnection/mysqlconnection.h"
#include "db/warehousedb.h"

class MysqlWareHouseDB
{
public:
    MysqlWareHouseDB();
    QList<WareHouseDB> allWareHouses ( QString );
    void addNewWareHouse( const QString&, const QString& );
    QString getWareHouseCode ( );
    void updateWareHouseCode ( QString& );
};

#endif // MYSQLWAREHOUSEDB_H
