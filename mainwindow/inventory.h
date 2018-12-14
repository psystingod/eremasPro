#ifndef INVENTORY_H
#define INVENTORY_H

#include <QWidget>
#include <QStandardItemModel>
#include <QMenu>
#include <QMessageBox>
#include <QDate>
#include <QMimeData>
#include <QFileInfo>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QItemSelection>
#include <QLocale>

#include "db/inventorydb.h"
#include "db/warehousedb.h"
#include "db/productfamilydb.h"
#include "db/unitsdb.h"

namespace Ui {
  class Inventory;
}

class Inventory : public QWidget
{
  Q_OBJECT

public:
  explicit Inventory(QWidget *parent = nullptr);
  ~Inventory();

private slots:
  void on_newProduct ();
  void on_editProduct();
  void on_viewCost();
  void on_hideAll();
  void on_tblInventory_customContextMenuRequested(const QPoint &pos);
  void replyFinished( QNetworkReply* );
  void on_btnAddProduct_clicked();
  void on_tblSelectionChanged(const QItemSelection & selected, const QItemSelection &unselected);
  void downloadFinished ( QNetworkReply* );
  void on_btnNewCancel_clicked();
  void downloadProgressBar ( qint64, qint64 );
  void uploadProgressBar ( qint64, qint64 );

  void on_txtSearchOptions_textEdited(const QString &arg1);

  void on_txtNewProductCost_cursorPositionChanged(int arg1, int arg2);

private:
  Ui::Inventory *ui;
  QStringList fnamelist;
  QString fname;
  bool imageSaved;
  void setProductCostHide ( bool );
  void setNewProductHide( bool );
  void setProductDetailsHide( bool );
  void setTblContextMenu();
  void setCbxSearchOptions ();
  void setSelectionChanged ();
  void setLayoutBorder();
  void setTableInventory ( QString, int );
  void clearAllControls();
  void addNewProduct ();
  void resizeEvent ( QResizeEvent* );
  void dragEnterEvent (QDragEnterEvent *event );
  void dropEvent ( QDropEvent *event );
  void uploadImageByHttp();
  QByteArray buildUploadString();

  enum inventoryrows {
    CODE, DESCRIPTION, UNIT, QUANTITY, COST
  };
};

#endif // INVENTORY_H
