#ifndef UNITSDB_H
#define UNITSDB_H

#include <QList>
#include <QString>

class UnitsDB
{
public:
    UnitsDB();
    UnitsDB( const QString&, const QString& );

    QString name, unitName;

    QString getName ( );
    void setName ( QString );
    QString getUnitName ( );
    void setUnitName ( QString );

    QList<UnitsDB> allUnits ( QString );
    void addNew ( QString, QString );
};

#endif // UNITSDB_H
