#ifndef WAREHOUSEDB_H
#define WAREHOUSEDB_H

#include <QList>
#include <QString>

class WareHouseDB
{
public:
    WareHouseDB();
    WareHouseDB( QString&, QString&, QString& );

    QString name, wareHouseId, address;

    QString getName ( );
    void setName ( QString& );
    QString getWareHouseId ( );
    void setWareHouseId (QString& );
    QString getAddress ( );
    void setAddress (QString& );

    QList<WareHouseDB> allWarehouses ( const QString& );
    void addNewWareHouse ( const QString&, const QString& );

};

#endif // WAREHOUSEDB_H
