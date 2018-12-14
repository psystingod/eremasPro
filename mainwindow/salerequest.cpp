#include "salerequest.h"
#include "ui_salerequest.h"
//#include "db/inventorydb.h"
//#include "dbinteraction/mysqlinventorydb.h"


SaleRequest::SaleRequest(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::SaleRequest)
{
  ui->setupUi(this);
  setValuesZero();
  setTableBilling();
  setTblContextMenu();
}

SaleRequest::~SaleRequest()
{
  delete ui;
}

void SaleRequest::setValuesZero () {
  ui->lblSubTotal->setAlignment(Qt::AlignRight);
  ui->lblTax->setAlignment(Qt::AlignRight);
  ui->lblCesc->setAlignment(Qt::AlignRight);
  ui->lblRetention->setAlignment(Qt::AlignRight);
  ui->lblTotal->setAlignment(Qt::AlignRight);
  ui->lblTotal->setStyleSheet("QLabel { color: green }");
  ui->lblTotalLetters->setStyleSheet("QLabel { color: green }");

  ui->lblSubTotal->setText("$ 0.00");
  ui->lblTax->setText("$ 0.00");
  ui->lblCesc->setText("$ 0.00");
  ui->lblRetention->setText("$ 0.00");
  ui->lblTotal->setText("$ 0.00");
  ui->lblTotalLetters->setText("Cero con 00/100");
}

void SaleRequest::on_rdoCCF_toggled(bool checked)
{
  if (checked) {
    ui->lblRetention->setHidden(false);
    ui->lblTagRetention->setHidden(false);
  }
  else {
    ui->lblRetention->setHidden(true);
    ui->lblTagRetention->setHidden(true);
  }
}

void SaleRequest::setTableBilling () {
  QStandardItemModel *model = new QStandardItemModel(0, 8, this);
  model->setHorizontalHeaderLabels({"Id", "Código", "Description", "Unidad", "Cantidad", "Precio U. ($)", "Descuento (%)", "SubTotal ($)" });

  //ui->tblProducts->setModel(model);
  ui->tblProducts->setColumnHidden(ID, true);
  ui->tblProducts->verticalHeader()->setVisible(false);
  ui->tblProducts->setShowGrid(true);
  ui->tblProducts->verticalHeader()->setDefaultSectionSize(18);
  ui->tblProducts->horizontalHeader()->setStretchLastSection(QHeaderView::Stretch);
}

void SaleRequest::setTblContextMenu () {
  ui->tblProducts->setContextMenuPolicy(Qt::CustomContextMenu);
}

void SaleRequest::on_cbxCustomers_editTextChanged(const QString &customer) {

}

void SaleRequest::on_txtSearch_textChanged(const QString &search) {
  searchedProduct(search);
}

void SaleRequest::searchedProduct (QString product) {
  ui->cbxProducts->clear();

  InventoryDB *inventory = new InventoryDB();
  QList<InventoryDB> inventoryList = inventory->allInventory(product, 0);
  int rows = inventoryList.size();

  ui->cbxProducts->addItem("", -1);

  for (int row = 0; row < rows; ++row) {
    ui->cbxProducts->addItem(inventoryList.at(row).description, inventoryList.at(row).id);
  }

  if ( ui->cbxProducts->model()->rowCount() < 0 )
    ui->cbxProducts->showPopup();
}

void SaleRequest::on_cbxProducts_currentIndexChanged(int index) {

  InventoryDB *inventory = new InventoryDB();
  QList<InventoryDB> product = inventory->productById(ui->cbxProducts->itemData(index).toInt());

  if ( !product.isEmpty() ) {
    int rows = ui->tblProducts->model()->rowCount();
    ui->tblProducts->insertRow(rows);

    ui->tblProducts->model()->setData(ui->tblProducts->model()->index(rows, ID, QModelIndex()), product.at(0).id);
    ui->tblProducts->model()->setData(ui->tblProducts->model()->index(rows, CODE, QModelIndex()), product.at(0).code);
    ui->tblProducts->model()->setData(ui->tblProducts->model()->index(rows, DESCRIPTION, QModelIndex()), product.at(0).description );
    ui->tblProducts->model()->setData(ui->tblProducts->model()->index(rows, UNIT, QModelIndex()), product.at(0).unit );
    ui->tblProducts->model()->setData(ui->tblProducts->model()->index(rows, QUANTITY, QModelIndex()), uint(product.at(0).qty) );
    ui->tblProducts->model()->setData(ui->tblProducts->model()->index(rows, UNITPRICE, QModelIndex()), product.at(0).price );
    ui->tblProducts->model()->setData(ui->tblProducts->model()->index(rows, DISCOUNT, QModelIndex()), double(0) );
    ui->tblProducts->model()->setData(ui->tblProducts->model()->index(rows, SUBTOTAL, QModelIndex()), double (0) );


    ui->tblProducts->item(rows, CODE)->setFlags(Qt::ItemIsEnabled);
    ui->tblProducts->item(rows, DESCRIPTION)->setFlags(Qt::ItemIsEnabled);
    ui->tblProducts->item(rows, UNIT)->setFlags(Qt::ItemIsEnabled);
    ui->tblProducts->item(rows, UNITPRICE)->setFlags(Qt::ItemIsEnabled);
    ui->tblProducts->item(rows, SUBTOTAL)->setFlags(Qt::ItemIsEnabled);

    ui->tblProducts->model()->setData(ui->tblProducts->model()->index(rows, CODE), Qt::AlignCenter, Qt::TextAlignmentRole);
    ui->tblProducts->model()->setData(ui->tblProducts->model()->index(rows, UNIT), Qt::AlignCenter, Qt::TextAlignmentRole);
    ui->tblProducts->model()->setData(ui->tblProducts->model()->index(rows, QUANTITY), Qt::AlignCenter, Qt::TextAlignmentRole);
    ui->tblProducts->model()->setData(ui->tblProducts->model()->index(rows, UNITPRICE), Qt::AlignRight, Qt::TextAlignmentRole);
    ui->tblProducts->model()->setData(ui->tblProducts->model()->index(rows, DISCOUNT), Qt::AlignRight, Qt::TextAlignmentRole);
    ui->tblProducts->model()->setData(ui->tblProducts->model()->index(rows, SUBTOTAL), Qt::AlignRight, Qt::TextAlignmentRole);
  }
}

void SaleRequest::resizeEvent( QResizeEvent *event ) {
  ui->tblProducts->setColumnWidth(ID, parentWidget()->width()/12);
  ui->tblProducts->setColumnWidth(CODE, parentWidget()->width()/9);
  ui->tblProducts->setColumnWidth(DESCRIPTION, parentWidget()->width()/3);
  ui->tblProducts->setColumnWidth(UNIT, parentWidget()->width()/10);
  ui->tblProducts->setColumnWidth(QUANTITY, parentWidget()->width()/10);
  ui->tblProducts->setColumnWidth(UNITPRICE, parentWidget()->width()/9);
  ui->tblProducts->setColumnWidth(DISCOUNT, parentWidget()->width()/9);
  ui->tblProducts->setColumnWidth(SUBTOTAL, parentWidget()->width()/9);

  QWidget::resizeEvent(event);
}

void SaleRequest::on_tblProducts_cellChanged(int row, int column) {
  if ( ui->tblProducts->item(row, UNITPRICE) != nullptr ) {
    if ( column ==  QUANTITY || column == DISCOUNT) {
      double subtotal = ui->tblProducts->item(row, QUANTITY)->text().toDouble() * ui->tblProducts->item(row, UNITPRICE)->text().toDouble() * (100 - ui->tblProducts->item(row, DISCOUNT)->text().toDouble())/100;
      ui->tblProducts->model()->setData(ui->tblProducts->model()->index(row, SUBTOTAL, QModelIndex()), subtotal );
    }

    if ( column == SUBTOTAL ) {
      updateTotal();
    }
  }
}

void SaleRequest::updateTotal ( ) {
  int rows = ui->tblProducts->rowCount();
  double sbtotal, iva, cesc, retention, total;
  sbtotal = iva = cesc = retention = total = 0.00;

  for ( int rowCount = 0; rowCount < rows; ++rowCount  ) {
    sbtotal += ui->tblProducts->item(rowCount, SUBTOTAL)->text().toDouble();
    iva += ui->tblProducts->item(rowCount, SUBTOTAL)->text().toDouble() * 0.13;
    cesc +=  ui->tblProducts->item(rowCount, SUBTOTAL)->text().toDouble() * 0.05;
    retention += ui->tblProducts->item(rowCount, SUBTOTAL)->text().toDouble() * 0.01;

  }

  if ( sbtotal < 100 ) {
    retention = 0;
    total = sbtotal + iva + cesc;
  }
  else {
    total = sbtotal + iva + cesc - retention;
  }

  if ( abs(total) * 0.001 > 0.0 ) {
    ui->lblSubTotal->setText(QLocale().toCurrencyString(sbtotal));
    ui->lblTax->setText(QLocale().toCurrencyString(iva));
    ui->lblCesc->setText(QLocale().toCurrencyString(cesc));
    ui->lblRetention->setText(QLocale().toCurrencyString(retention));
    ui->lblTotal->setText(QLocale().toCurrencyString(total));

    NumberToWords *number = new NumberToWords();
    ui->lblTotalLetters->setText(number->doubleToWords(total));
  }
  else {
      ui->lblSubTotal->setText(QLocale().toCurrencyString(0));
      ui->lblTax->setText(QLocale().toCurrencyString(0));
      ui->lblCesc->setText(QLocale().toCurrencyString(0));
      ui->lblRetention->setText(QLocale().toCurrencyString(0));
      ui->lblTotal->setText(QLocale().toCurrencyString(0));
      ui->lblTotalLetters->setText("Cero con 00/100");
  }
}

void SaleRequest::on_tblProducts_customContextMenuRequested(const QPoint &pos)
{
  QMenu *menu = new QMenu(this);
  QAction *deleteRow = new QAction(tr("&Elimar"), ui->tblProducts);

  menu->addAction(deleteRow);
  menu->popup(ui->tblProducts->viewport()->mapToGlobal(pos));
  connect(deleteRow, SIGNAL(triggered()), this, SLOT(on_DeleteItem()));
}

void SaleRequest::on_DeleteItem () {
  ui->tblProducts->removeRow(ui->tblProducts->currentRow());
  updateTotal();
}
