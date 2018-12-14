#ifndef AVAILABLEDB_H
#define AVAILABLEDB_H

#include <QString>

class AvailableDB
{

public:
    AvailableDB( );
    AvailableDB( const QString& );

    QString databasename;

    QString getDatabaseName( );
    void setDatabaseName( const QString& );
    QList<AvailableDB> allDB();
};

#endif // AVAILABLEDB_H
