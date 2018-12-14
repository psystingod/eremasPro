#ifndef MYSQLAVAILABLEDB_H
#define MYSQLAVAILABLEDB_H

#include <QList>
#include <QtSql>
#include "db/availabledb.h"

class MysqlAvailableDB
{

public:
    MysqlAvailableDB();
    QList<AvailableDB> allDB();

    ~MysqlAvailableDB();
};

#endif // MYSQLAVAILABLEDB_H
