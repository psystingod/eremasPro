#ifndef MYSQLTAXESDB_H
#define MYSQLTAXESDB_H

#include <QList>
#include <QtSql>

#include "dbconnection/mysqlconnection.h"
#include "db/taxesdb.h"

class MysqlTaxesDB
{
public:
    MysqlTaxesDB();
    QList<TaxesDB> allTaxes();
    QString getTaxValue ( const QString& );
    void setTaxValue ( const QString&, const QString& );
};

#endif // MYSQLTAXESDB_H
