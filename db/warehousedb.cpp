#include "warehousedb.h"
#include "dbinteraction/mysqlwarehousedb.h"

WareHouseDB::WareHouseDB()
{
    name = "";
    wareHouseId = "";
    address = "";
}

WareHouseDB::WareHouseDB(QString &nameLocal, QString &wareHouseIdLocal, QString &addressLocal)
{
    name = nameLocal;
    wareHouseId = wareHouseIdLocal;
    address = addressLocal;
}

QString WareHouseDB::getName () {
    return name;
}

void WareHouseDB::setName (QString &nameLocal) {
    name = nameLocal;
}

QString WareHouseDB::getWareHouseId() {
    return wareHouseId;
}

void WareHouseDB::setWareHouseId (QString &wareHouseIdLocal) {
    wareHouseId = wareHouseIdLocal;
}

QString WareHouseDB::getAddress() {
    return address;
}

void WareHouseDB::setAddress( QString &addressLocal) {
    address = addressLocal;
}

QList<WareHouseDB> WareHouseDB::allWarehouses( const QString &name ) {
    MysqlWareHouseDB *mysqlWareHouseDB = new MysqlWareHouseDB();
    return mysqlWareHouseDB->allWareHouses(name);
}

void WareHouseDB::addNewWareHouse( const QString &name, const QString &address ) {
    MysqlWareHouseDB *mysqlWareHouseDB = new MysqlWareHouseDB();
    mysqlWareHouseDB->addNewWareHouse(name, address);
}

