#include "unitsdb.h"
#include "dbinteraction/mysqlunitsdb.h"

UnitsDB::UnitsDB()
{
    name = "";
    unitName = "";
}

UnitsDB::UnitsDB( const QString &nameLocal, const QString &unitNameLocal )
{
    name = nameLocal;
    unitName = unitNameLocal;
}

QString UnitsDB::getName () {
    return name;
}

void UnitsDB::setName (QString nameLocal) {
    name = nameLocal;
}

QString UnitsDB::getUnitName () {
    return unitName;
}

void UnitsDB::setUnitName (QString unitNameLocal) {
    unitName = unitNameLocal;
}

QList<UnitsDB> UnitsDB::allUnits ( QString name) {
    MysqlUnitsDB *mysqlUnitsDB = new MysqlUnitsDB();
    return mysqlUnitsDB->allUnits(name);
}

void UnitsDB::addNew( QString name, QString unitName ) {
    MysqlUnitsDB *mysqlUnitsDB = new MysqlUnitsDB();
    mysqlUnitsDB->addNewUnit(name, unitName);
}
