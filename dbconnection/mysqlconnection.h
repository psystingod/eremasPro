#ifndef MYSQLCONNECTION_H
#define MYSQLCONNECTION_H

#include <QSqlQuery>
#include <QSqlDatabase>
#include <QtDebug>
#include <QSettings>

#include "common/paths.h"
#include "common/setting.h"

class MysqlConnection
{
public:
    MysqlConnection();

    bool open(QString databasename);
    void close();
};

#endif // MYSQLCONNECTION_H
