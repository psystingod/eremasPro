#ifndef ACCOUNTINGCATALOGDB_H
#define ACCOUNTINGCATALOGDB_H

#include <QList>
#include <QString>

class AccountingCatalogDB
{
public:
  AccountingCatalogDB ();

  int id;
  QString code, parent, name, classification;

  int getId ( );
  void setId ( int);
  QString getCode ( );
  void setCode ( QString );
  QString getParent ( );
  void setParent ( QString );
  QString getName ( );
  void setName ( QString );
  QString getClassification ( );
  void setClassification ( QString );

  QList<AccountingCatalogDB> allCatalog ( QString );
  void addNewAccount ( QString, QString, QString, QString );
  QString getParentAccount ( int id );
  void updateAccount (int, QString, QString, QString, QString );
};

#endif // ACCOUNTINGCATALOGDB_H
