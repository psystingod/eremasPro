#ifndef CATALOGOFACCOUNTS_H
#define CATALOGOFACCOUNTS_H

#include <QWidget>
#include <QStandardItemModel>
#include <QTreeWidget>
#include <QMessageBox>
#include <QMenu>

#include "db/accountingcatalogdb.h"

namespace Ui {
  class CatalogOfAccounts;
}

class CatalogOfAccounts : public QWidget
{
  Q_OBJECT

public:
  explicit CatalogOfAccounts(QWidget *parent = nullptr);
  ~CatalogOfAccounts();

private slots:
  void on_btnEditAccount_clicked();
  void on_btnNewAccount_clicked();
  void on_tvwCatalog_customContextMenuRequested(const QPoint &pos);
  void on_editRow ();
  void on_newAccount ();

private:
  Ui::CatalogOfAccounts *ui;
  void loadTreeViewCatalog();
  void setAccountClassification();
  void setGroupBorder ();
  void setBtnsDisabled ();
  void clearAll();
  void resizeEvent( QResizeEvent *);
  void loadRootCatalog( AccountingCatalogDB );
  void addTreeViewChild( QTreeWidgetItem *parent, AccountingCatalogDB );


  enum treeview {
    ACCOUNTCODE, ACCOUNTID, ACCOUNTPARENT, ACCOUNTNAME, CLASIFICATION
  };
};

#endif // CATALOGOFACCOUNTS_H
