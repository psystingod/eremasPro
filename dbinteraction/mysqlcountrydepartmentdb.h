#ifndef MYSQLCOUNTRYDEPARTMENTDB_H
#define MYSQLCOUNTRYDEPARTMENTDB_H

#include <QList>
#include <QtSql>

#include "dbconnection/mysqlconnection.h"
#include "db/countrydepartmentdb.h"

class MysqlCountryDepartmentDB
{
public:
    MysqlCountryDepartmentDB();
    QList<CountryDepartmentDB> allDepartments ( const QString& );
    void addNewDepartment( const QString& );
};

#endif // MYSQLCOUNTRYDEPARTMENTDB_H
