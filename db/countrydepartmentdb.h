#ifndef COUNTRYDEPARTMENTDB_H
#define COUNTRYDEPARTMENTDB_H

#include <QList>
#include <QString>

class CountryDepartmentDB
{
public:
    CountryDepartmentDB();
    CountryDepartmentDB( QString& );

    QString name;

    QString getName ( );
    void setName ( QString& );

    QList<CountryDepartmentDB> allDepartments ( const QString& );
    void addNewDepartment ( const QString& );
};

#endif // COUNTRYDEPARTMENTDB_H
