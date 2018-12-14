#ifndef SALEREQUEST_H
#define SALEREQUEST_H

#include <QWidget>
#include <QStandardItemModel>
#include <QDebug>
#include <QTableWidgetItem>
#include <QDoubleSpinBox>
#include <QMenu>
#include <cmath>

#include "db/inventorydb.h"
#include "common/numbertowords.h"

namespace Ui {
  class SaleRequest;
}

class SaleRequest : public QWidget
{
  Q_OBJECT

public:
  explicit SaleRequest(QWidget *parent = nullptr);
  ~SaleRequest();

private slots:
  void on_rdoCCF_toggled(bool checked);
  void on_cbxCustomers_editTextChanged(const QString &customer);
  void on_cbxProducts_currentIndexChanged(int index);
  void on_txtSearch_textChanged(const QString &search);
  void on_tblProducts_cellChanged(int row, int column);
  void on_tblProducts_customContextMenuRequested(const QPoint &pos);
  void on_DeleteItem ();

private:
  Ui::SaleRequest *ui;
  void setValuesZero();
  void resizeEvent( QResizeEvent*);
  void setTableBilling ();
  void searchedProduct( QString );
  void setTblContextMenu();
  void updateTotal();

  enum tblProducts {
    ID, CODE, DESCRIPTION, UNIT, QUANTITY, UNITPRICE, DISCOUNT, SUBTOTAL
  };
};

#endif // SALEREQUEST_H
