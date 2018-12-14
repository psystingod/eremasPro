#include "catalogofaccounts.h"
#include "ui_catalogofaccounts.h"

#include <QtDebug>

static QString editId = "";

CatalogOfAccounts::CatalogOfAccounts(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::CatalogOfAccounts)
{
  ui->setupUi(this);
  setGroupBorder ();
  setBtnsDisabled ();
  setAccountClassification ();
  loadTreeViewCatalog ();
}

CatalogOfAccounts::~CatalogOfAccounts()
{
  delete ui;
}

void CatalogOfAccounts::setGroupBorder () {
  ui->gbxNewAccount->setStyleSheet("QGroupBox::title { background-color: transparent; subcontrol-position: top left; padding:2 13px;}");
  ui->gbxNewAccount->setStyleSheet("QGroupBox#gbxNewAccount { border: 1px solid #bfbfbf; border-radius: 3px; }");
  ui->tvwCatalog->setContextMenuPolicy(Qt::CustomContextMenu);
}

void CatalogOfAccounts::setBtnsDisabled() {
  ui->btnEditAccount->setEnabled(false);
  ui->btnNewAccount->setEnabled(false);
  ui->gbxNewAccount->setDisabled(true);
}

void CatalogOfAccounts::setAccountClassification () {
  ui->cbxClassification->addItems({"Activo", "Pasivo", "Patrimonio", "Ingresos" "Gastos", "Cuentas de cierre"});
}

void CatalogOfAccounts::loadTreeViewCatalog () {

  AccountingCatalogDB *catalog = new AccountingCatalogDB();

  QList<AccountingCatalogDB> list = catalog->allCatalog("");
  int countRows = list.size();

  for (int row = 0; row < countRows; ++row) {

    if (list.at(row).parent.isEmpty()) {
      loadRootCatalog(list.at(row));
    }

    else {
      QList<QTreeWidgetItem*> clist = ui->tvwCatalog->findItems(list.at(row).parent, Qt::MatchExactly|Qt::MatchRecursive, ACCOUNTCODE);
      addTreeViewChild (clist.at(0), list.at(row));
    }
  }
  ui->tvwCatalog->setColumnHidden(ACCOUNTID, true);
  ui->tvwCatalog->setColumnHidden(ACCOUNTPARENT, true);
}

void CatalogOfAccounts::loadRootCatalog ( AccountingCatalogDB list ) {
  QTreeWidgetItem *root = new QTreeWidgetItem(ui->tvwCatalog);
  ui->tvwCatalog->addTopLevelItem(root);

  root->setText(ACCOUNTCODE, list.getCode());
  root->setText(ACCOUNTID, QVariant(list.getId()).toString());
  root->setText(ACCOUNTPARENT, list.getParent());
  root->setText(ACCOUNTNAME, list.getName());
  root->setText(CLASIFICATION, list.getClassification());
}

void CatalogOfAccounts::addTreeViewChild (QTreeWidgetItem *parent, AccountingCatalogDB list ) {
    QTreeWidgetItem *itm = new QTreeWidgetItem();
    itm->setText(ACCOUNTCODE, list.getCode());
    itm->setText(ACCOUNTID, QVariant(list.getId()).toString());
    itm->setText(ACCOUNTPARENT, list.getParent());
    itm->setText(ACCOUNTNAME, list.getName());
    itm->setText(CLASIFICATION, list.getClassification());
    parent->addChild(itm);
}

void CatalogOfAccounts::resizeEvent( QResizeEvent *event ) {
  ui->tvwCatalog->setColumnWidth(ACCOUNTCODE, parentWidget()->width()/3);
  ui->tvwCatalog->setColumnWidth(ACCOUNTID, parentWidget()->width()/30);
  ui->tvwCatalog->setColumnWidth(ACCOUNTPARENT, parentWidget()->width()/3);
  ui->tvwCatalog->setColumnWidth(ACCOUNTNAME, parentWidget()->width()/2);
  ui->tvwCatalog->setColumnWidth(CLASIFICATION, parentWidget()->width()/9);

  QWidget::resizeEvent(event);
}

void CatalogOfAccounts::on_btnEditAccount_clicked()
{
  if (ui->tvwCatalog->selectionModel()->hasSelection()) {
    QList<QTreeWidgetItem*> itms = ui->tvwCatalog->selectedItems();

    if ( itms.at(0)->data(ACCOUNTID, Qt::DisplayRole).toString().compare(editId) == 0) {
        AccountingCatalogDB *catalog = new AccountingCatalogDB();
        catalog->updateAccount( editId.toInt(), ui->txtAccountCode->text(), ui->txtAccountParent->text(), ui->txtAccountName->text(), ui->cbxClassification->currentText());
        clearAll();
      }
    else
      QMessageBox::warning(this, "Editar cuenta", "¡Los datos editados no coinciden con la cuenta seleccionada!");
  }

  else
    QMessageBox::warning(this, "Editar cuenta", "¡Debe seleccionar una cuenta para editar el nombre!");
}

void CatalogOfAccounts::on_btnNewAccount_clicked()
{
  AccountingCatalogDB *catalog = new AccountingCatalogDB();
  QString parent = "";
  QString combo = ui->cbxClassification->currentText();

  if ( ui->chkSubAccount->isChecked() ) {
      ui->txtAccountParent->setDisabled(false);

      if ( ui->tvwCatalog->selectionModel()->hasSelection() ) {
          parent = ui->tvwCatalog->currentItem()->data(ACCOUNTCODE, ACCOUNTCODE).toString();

          if ( !ui->txtAccountCode->text().isEmpty() && !ui->txtAccountName->text().isEmpty() ) {

              if ( !combo.isEmpty() ) {
                catalog->addNewAccount(ui->txtAccountCode->text(), parent, ui->txtAccountName->text(), combo );
                clearAll();
              }

              else
                QMessageBox::warning(this, "Agregar cuenta", "¡Debe elegir la clasificación de la cuenta!");
            }

          else
            QMessageBox::warning(this, "Agregar cuenta", "¡Debe ingresar los campos de código y nombre de la cuenta!");
      }
      else
        QMessageBox::warning(this, "Agregar cuenta", "¡Debe seleccionar una cuenta padre!");
    }

  else {
      ui->txtAccountParent->setDisabled(true);

      if ( !ui->txtAccountName->text().isEmpty() ) {
          if ( !ui->cbxClassification->itemData(ui->cbxClassification->currentIndex()).toString().isEmpty() ) {
            catalog->addNewAccount( ui->txtAccountCode->text(), parent, ui->txtAccountName->text(), combo );
            clearAll();
          }
          else
            QMessageBox::warning(this, "Agregar cuenta", "¡Debe elegir la clasificación de la cuenta!");
        }
      else
        QMessageBox::warning(this, "Agregar cuenta", "¡Debe ingrear el nombre de la cuenta!");
  }
}

void CatalogOfAccounts::clearAll () {
  ui->txtAccountParent->clear();
  ui->txtAccountCode->clear();
  ui->txtAccountName->clear();
  ui->cbxClassification->setItemText(0, "");
  ui->tvwCatalog->clear();
  setBtnsDisabled();
  loadTreeViewCatalog();
}

void CatalogOfAccounts::on_tvwCatalog_customContextMenuRequested(const QPoint &pos)
{
  QMenu *menu = new QMenu(this);
  QAction *newAccount = new QAction(tr("&Nueva Cuenta"), ui->tvwCatalog);
  QAction *editRow = new QAction(tr("&Editar"), ui->tvwCatalog);

  menu->addAction(newAccount);
  menu->addAction(editRow);
  menu->popup(ui->tvwCatalog->viewport()->mapToGlobal(pos));
  connect(newAccount, SIGNAL(triggered()), this, SLOT(on_newAccount()));
  connect(editRow, SIGNAL(triggered()), this, SLOT(on_editRow()));
}

void CatalogOfAccounts::on_editRow() {
  QList<QTreeWidgetItem*> itms = ui->tvwCatalog->selectedItems();
  ui->gbxNewAccount->setDisabled(false);
  ui->btnEditAccount->setEnabled(true);
  ui->btnNewAccount->setEnabled(false);

  if ( ui->tvwCatalog->selectionModel()->hasSelection() ) {
      editId = itms.at(0)->data(ACCOUNTID, Qt::DisplayRole).toString();

    if (itms.at(0)->data(ACCOUNTPARENT, Qt::DisplayRole).toString().isEmpty()) {
      ui->txtAccountParent->setDisabled(true);
      ui->chkSubAccount->setChecked(false);
    }
    else {
        ui->txtAccountParent->setDisabled(false);
        ui->chkSubAccount->setChecked(true);
      }

  ui->txtAccountCode->setText(itms.at(0)->data(ACCOUNTCODE, Qt::DisplayRole).toString());
  ui->txtAccountName->setText(itms.at(0)->data(ACCOUNTNAME, Qt::DisplayRole).toString());
  ui->txtAccountParent->setText(itms.at(0)->data(ACCOUNTPARENT, Qt::DisplayRole).toString());
  ui->cbxClassification->setItemText(0, itms.at(0)->data(CLASIFICATION, Qt::DisplayRole).toString());
  }
  else {
     QMessageBox::warning(this, "Editar cuenta", "¡Debe ingrear el nombre de la cuenta!");
  }
}

void CatalogOfAccounts::on_newAccount() {
  ui->txtAccountCode->clear();
  ui->txtAccountName->clear();
  ui->txtAccountParent->clear();
  ui->cbxClassification->setItemText(0, "");
  ui->gbxNewAccount->setDisabled(false);
  ui->btnEditAccount->setEnabled(false);
  ui->btnNewAccount->setEnabled(true);
  if (ui->tvwCatalog->selectionModel()->hasSelection()) {
    if (!ui->tvwCatalog->selectedItems().at(0)->data(ACCOUNTCODE, Qt::DisplayRole).toString().isEmpty()) {
      ui->txtAccountParent->setText(ui->tvwCatalog->selectedItems().at(0)->data(ACCOUNTCODE, Qt::DisplayRole).toString());
      ui->txtAccountParent->setEnabled(true);
    }
    else {
      ui->txtAccountParent->setEnabled(true);
    }
  }
}
