#ifndef TAXESDB_H
#define TAXESDB_H

#include <QList>

class TaxesDB
{
public:
    TaxesDB();
    TaxesDB( double&, double&, double& );

    double iva, pac, cesc;

    double getIva ();
    void setIva ( double& );
    double getPac ();
    void setPac ( double& );
    double getCesc ();
    void setCesc (double& );

    QList<TaxesDB> allTaxes();
    QString getTaxValue ( const QString& );
    void setTaxValue ( const QString&, const QString& );
};

#endif // TAXESDB_H
