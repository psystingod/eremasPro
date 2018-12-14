#include "countrydepartmentdb.h"
#include "dbinteraction/mysqlcountrydepartmentdb.h"

CountryDepartmentDB::CountryDepartmentDB()
{
    name = "";
}

CountryDepartmentDB::CountryDepartmentDB(QString &nameLocal )
{
    name = nameLocal;
}

QString CountryDepartmentDB::getName () {
    return name;
}

void CountryDepartmentDB::setName (QString &nameLocal) {
    name = nameLocal;
}

QList<CountryDepartmentDB> CountryDepartmentDB::allDepartments( const QString &name ) {
    MysqlCountryDepartmentDB *mysqlCountryDepartmentDB = new MysqlCountryDepartmentDB();
    return mysqlCountryDepartmentDB->allDepartments(name);
}

void CountryDepartmentDB::addNewDepartment ( const QString &name ) {
    MysqlCountryDepartmentDB *mysqlCountryDepartmentDB = new MysqlCountryDepartmentDB();
    mysqlCountryDepartmentDB->addNewDepartment(name);
}
