#include "mysqlcountrydepartmentdb.h"

MysqlCountryDepartmentDB::MysqlCountryDepartmentDB()
{

}

QList<CountryDepartmentDB> MysqlCountryDepartmentDB::allDepartments ( const QString &department ) {
    MysqlConnection* conn = new MysqlConnection();
    Setting *setting = new Setting ();
    QList<CountryDepartmentDB> list;
    QSqlQuery query;

    if ( conn->open( setting->getDatabasename() ) ) {
        if (department.isEmpty())
            query.prepare("SELECT * FROM system_country_departments");
        else
            query.prepare("SELECT * FROM system_country_departments WHERE name LIKE '" + department + "'" );

        query.exec();

        CountryDepartmentDB departmentsDB;
        while (query.next()) {
            QString name = query.value(query.record().indexOf("name")).toString();

            departmentsDB.setName(name);

            list.append(departmentsDB);
        }
        query.finish();
        query.clear();
        conn->close();
    }
    return list;
}

void MysqlCountryDepartmentDB::addNewDepartment (const QString &name ) {
    MysqlConnection* conn = new MysqlConnection();
    Setting *setting = new Setting ();
    QSqlQuery query;

    if ( conn->open( setting->getDatabasename() ) ) {
        query.prepare( "INSERT INTO system_country_departments (name) VALUES (?)" );
        query.bindValue(0, name);
        query.exec();

        query.finish();
        query.clear();
        conn->close();
    }
}
