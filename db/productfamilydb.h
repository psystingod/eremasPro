#ifndef PRODUCTFAMILYDB_H
#define PRODUCTFAMILYDB_H

#include <QList>
#include <QString>

class ProductFamilyDB
{
public:
  ProductFamilyDB();
  ProductFamilyDB( QString&, QString&, QString& );

  QString name, abbreviated, code;

  QString getName ( );
  void setName ( QString& );
  QString getAbbreviated ( );
  void setAbbreviated (QString& );
  QString getCode ( );
  void setCode (QString& );

  QList<ProductFamilyDB> allProductFamily ( const QString& );
  void addNewProductFamily ( const QString&, const QString& );

};

#endif // PRODUCTFAMILYDB_H
