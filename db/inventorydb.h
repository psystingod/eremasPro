#ifndef INVENTORYDB_H
#define INVENTORYDB_H

#include <QList>
#include <QString>
#include <QDate>

class InventoryDB
{
public:
  InventoryDB ();

  QString description, unit, group, warehouse, family, code, picture_path, accounting_code;
  int id, qty, minimum;
  double price, cost;
  QDate ingress_date, sale_date;

  int getId ( );
  void setId ( int& );
  QString getDescription ( );
  void setDescription ( QString& );
  int getQuantity ( );
  void setQuantity ( int& );
  QString getUnit ( );
  void setUnit ( QString& );
  QString getCompany ( );
  void setCompany ( QString& );
  QString getGroup ( );
  void setGroup ( QString& );
  QString getWarehouse ( );
  void setWarehouse ( QString& );
  QString getFamily ( );
  void setFamily ( QString& );
  QString getCode ( );
  void setCode ( QString& );
  double getPrice ( );
  void setPrice ( double& );
  double getCost ( );
  void setCost ( double& );
  QString getPicturePath ( );
  void setPicturePath ( QString& );
  int getMinimum ( );
  void setMinimum ( int& );
  QDate getIngressDate ( );
  void setIngressDate ( QDate& );
  QDate getSaleDate ( );
  void setSaleDate ( QDate& );
  QString getAccountingCode ( );
  void setAccountingCode ( QString& );

  QList<InventoryDB> allInventory ( const QString&, const int& );
  QList<InventoryDB> productById ( const int& );
  void addNewProduct ( QString, int, QString, QString, QString, QString, double, double, QString, QString );
};

#endif // INVENTORYDB_H
