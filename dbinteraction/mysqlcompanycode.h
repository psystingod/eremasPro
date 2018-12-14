#ifndef MYSQLCOMPANYCODE_H
#define MYSQLCOMPANYCODE_H

#include <QList>
#include <QString>

class MysqlCompanyCode
{
public:
    MysqlCompanyCode();
    QString name;

    QString getName ( );
    void setName ( QString& );
    QString getCode ( );
    void setCode ( QString& );

    //QString getName();
};

#endif // MYSQLCOMPANYCODE_H
