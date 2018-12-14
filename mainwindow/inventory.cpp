#include "inventory.h"
#include "ui_inventory.h"

#include <QtDebug>

Inventory::Inventory(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::Inventory)
{
  ui->setupUi(this);
  setProductCostHide(true);
  setNewProductHide(true);
  setProductDetailsHide(true);
  setTblContextMenu();
  setCbxSearchOptions ();
  setLayoutBorder();
  setTableInventory( "", -1 );
}

Inventory::~Inventory()
{
  delete ui;
}

void Inventory::setProductCostHide ( bool status )
{
  ui->wgtProductCost->setHidden( status );
}

void Inventory::setProductDetailsHide ( bool status )
{
  ui->wgtViewProductDetails->setHidden( status );
  ui->pgbDownload->setHidden(status);
}

void Inventory::setNewProductHide ( bool status)
{
  ui->wgtNewProductDetails->setHidden( status );
  ui->wgtBtnNewProduct->setHidden( status );
  ui->pgbUpload->setHidden( status );
}

void Inventory::setTblContextMenu () {
  ui->tblInventory->setContextMenuPolicy(Qt::CustomContextMenu);
}

void Inventory::setCbxSearchOptions ( )
{
  ui->cbxSearchOptions->addItem("Descripción", 1);
  ui->cbxSearchOptions->addItem("Código", 2);
}

void Inventory::setLayoutBorder() {
  ui->gbxGeneralsProduct->setStyleSheet("QGroupBox::title { background-color: transparent; subcontrol-position: top left; padding:2 13px;}");
  ui->gbxGeneralsProduct->setStyleSheet("QGroupBox#gbxGeneralsProduct { border: 1px solid #bfbfbf; border-radius: 3px; }");
  ui->gbxEspecificProduct->setStyleSheet("QGroupBox::title { background-color: transparent; subcontrol-position: top left; padding:2 13px;}");
  ui->gbxEspecificProduct->setStyleSheet("QGroupBox#gbxEspecificProduct { border: 1px solid #bfbfbf; border-radius: 3px; }");
  ui->gbxImageProduct->setStyleSheet("QGroupBox::title { background-color: transparent; subcontrol-position: top left; padding:2 13px;}");
  ui->gbxImageProduct->setStyleSheet("QGroupBox#gbxImageProduct { border: 1px solid #bfbfbf; border-radius: 3px; }");
  ui->gbxNewGeneralsProduct->setStyleSheet("QGroupBox::title { background-color: transparent; subcontrol-position: top left; padding:2 13px;}");
  ui->gbxNewGeneralsProduct->setStyleSheet("QGroupBox#gbxNewGeneralsProduct { border: 1px solid #bfbfbf; border-radius: 3px; }");
  ui->gbxNewEspecificProduct->setStyleSheet("QGroupBox::title { background-color: transparent; subcontrol-position: top left; padding:2 13px;}");
  ui->gbxNewEspecificProduct->setStyleSheet("QGroupBox#gbxNewEspecificProduct { border: 1px solid #bfbfbf; border-radius: 3px; }");
  ui->gbxNewImageProduct->setStyleSheet("QGroupBox::title { background-color: transparent; subcontrol-position: top left; padding:2 13px;}");
  ui->gbxNewImageProduct->setStyleSheet("QGroupBox#gbxNewImageProduct { border: 1px solid #bfbfbf; border-radius: 3px; }");

  ui->lblPrice->setStyleSheet("QLabel { color : blue; }");
}

void Inventory::setSelectionChanged () {
  connect(
    ui->tblInventory->selectionModel(),
    SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),
    SLOT(on_tblSelectionChanged(const QItemSelection &, const QItemSelection &))
   );
}

void Inventory::setTableInventory ( QString searchText, int code)
{
  InventoryDB *inventoryDB = new InventoryDB();
  QList<InventoryDB> list = inventoryDB->allInventory(searchText, code);

  int countRows = list.size();

  QStandardItemModel *model = new QStandardItemModel(countRows, 4, this);
  model->setHorizontalHeaderLabels({ "Código", "Description", "Unidad", "Cantidad", "Costo" });

  ui->tblInventory->setModel(model);
  ui->tblInventory->verticalHeader()->setVisible(false);
  ui->tblInventory->setShowGrid(true);
  ui->tblInventory->verticalHeader()->setDefaultSectionSize(18);
  ui->tblInventory->horizontalHeader()->setStretchLastSection(QHeaderView::Stretch);

  for (int row = 0; row < countRows; row++) {
      model->setData(model->index(row, CODE, QModelIndex()), list.at(row).code);
      model->setData(model->index(row, DESCRIPTION, QModelIndex()), list.at(row).description);
      model->setData(model->index(row, UNIT, QModelIndex()), list.at(row).unit);
      model->setData(model->index(row, QUANTITY, QModelIndex()), list.at(row).qty);
      model->setData(model->index(row, COST, QModelIndex()), list.at(row).cost);

      ui->tblInventory->model()->setData(ui->tblInventory->model()->index(row, CODE), Qt::AlignCenter, Qt::TextAlignmentRole);
      ui->tblInventory->model()->setData(ui->tblInventory->model()->index(row, UNIT), Qt::AlignCenter, Qt::TextAlignmentRole);
      ui->tblInventory->model()->setData(ui->tblInventory->model()->index(row, QUANTITY), Qt::AlignRight, Qt::TextAlignmentRole);
      ui->tblInventory->model()->setData(ui->tblInventory->model()->index(row, COST), Qt::AlignRight, Qt::TextAlignmentRole);
  }
  ui->tblInventory->setSelectionBehavior(QAbstractItemView::SelectRows);
  ui->tblInventory->setEditTriggers(QAbstractItemView::NoEditTriggers);
  setSelectionChanged ();
  //ui->tblInventory->selectRow(0);
  //ui->tblInventory->setFocus();
}

void Inventory::resizeEvent( QResizeEvent *event ) {
  ui->tblInventory->setColumnWidth(CODE, parentWidget()->width()/8);
  ui->tblInventory->setColumnWidth(DESCRIPTION, parentWidget()->width()/2);
  ui->tblInventory->setColumnWidth(UNIT, parentWidget()->width()/9);
  ui->tblInventory->setColumnWidth(QUANTITY, parentWidget()->width()/8);
  ui->tblInventory->setColumnWidth(COST, parentWidget()->width()/8);

  QWidget::resizeEvent(event);
}

void Inventory::on_tblInventory_customContextMenuRequested(const QPoint &pos)
{
  QMenu *menu = new QMenu(this);
  QAction *newProduct = new QAction(tr("&Nuevo Producto"), ui->tblInventory);
  QAction *editProduct = new QAction(tr("&Editar"), ui->tblInventory);
  QAction *viewCost = new QAction(tr("&Costos"), ui->tblInventory);
  QAction *hideAll = new QAction(tr("&Ocultar detalles"), ui->tblInventory);

  menu->addAction(newProduct);
  menu->addAction(editProduct);
  menu->addSeparator();
  menu->addAction(viewCost);
  menu->addSeparator();
  menu->addAction(hideAll);
  menu->popup(ui->tblInventory->viewport()->mapToGlobal(pos));
  connect(newProduct, SIGNAL(triggered()), this, SLOT(on_newProduct()));
  connect(editProduct, SIGNAL(triggered()), this, SLOT(on_editProduct()));
  connect(viewCost, SIGNAL(triggered()), this, SLOT(on_viewCost()));
  connect(hideAll, SIGNAL(triggered()), this, SLOT(on_hideAll()));
}

void Inventory::on_newProduct () {
  ui->cbxNewWarehouse->clear();
  ui->cbxNewGroup->clear();
  ui->cbxNewUnit->clear();
  setProductDetailsHide(true);
  setNewProductHide(false);
  setProductCostHide(true);
  setAcceptDrops(true);

  WareHouseDB *warehouse = new WareHouseDB();
  QList<WareHouseDB> list = warehouse->allWarehouses("");

  if ( !list.isEmpty() ) {
    int rows = list.size();
    ui->cbxNewWarehouse->insertItem(0, "");
    for (int row = 0; row < rows; ++row) {
      ui->cbxNewWarehouse->insertItem (list.at(row).wareHouseId.toInt(), list.at(row).name );
    }
  }

  ProductFamilyDB *group = new ProductFamilyDB();
  QList<ProductFamilyDB> groupList = group->allProductFamily("");
  if (!groupList.isEmpty()) {
    int rows = groupList.size();
    ui->cbxNewGroup->insertItem(0, "");
    for ( int row = 0; row < rows; ++row ) {
      ui->cbxNewGroup->insertItem ( groupList.at(row).code.toInt(), groupList.at(row).name );
    }
  }

  UnitsDB *units = new UnitsDB();
  QList<UnitsDB> unitsList = units->allUnits("");

  if ( !unitsList.isEmpty() ) {
    int rows = unitsList.size();
    ui->cbxNewUnit->insertItem(0, "");
    for ( int row = 0; row < rows; ++row ) {
      ui->cbxNewUnit->insertItem( row, unitsList.at(row).unitName );
    }
  }
}

void Inventory::on_editProduct () {
  /// TO DO
}

void Inventory::on_viewCost () {
  setProductCostHide(false);
  setNewProductHide(true);
  setProductDetailsHide(true);
}

void Inventory::on_hideAll ()
{
  setProductDetailsHide(true);
  setNewProductHide(true);
  setProductCostHide(true);
}
void Inventory::on_btnAddProduct_clicked() { // Agregar al inventario un nuevo producto
  if (!ui->cbxNewWarehouse->currentText().isEmpty()) {
      if ( !ui->cbxNewGroup->currentText().isEmpty()) {
          if ( !ui->txtNewAccount->text().isEmpty() ) {
              if ( !ui->txtNewInventoryCode->text().isEmpty() ) {
                  if ( !ui->txtNewDescription->text().isEmpty() ) {
                      if ( !ui->cbxNewUnit->currentText().isEmpty() ) {
                          if ( !ui->txtNewQty->text().isEmpty() ) {
                              if ( !ui->txtNewCost->text().isEmpty() ) {
                                  if ( !ui->txtNewPrice->text().isEmpty() ) {
                                    addNewProduct();
                                  }

                                  else
                                    QMessageBox::warning(this, "Agregar producto", "¡Debe ingresar precio del producto!");
                              }
                              else
                                QMessageBox::warning(this, "Agregar producto", "¡Debe ingresar el costo del producto!");
                          }
                          else
                            QMessageBox::warning(this, "Agregar producto", "¡Debe ingresar la cantidad del producto!");
                      }
                      else
                        QMessageBox::warning(this, "Agregar producto", "¡Debe seleccionar una unidad de medida para el producto!");
                  }
                  else
                    QMessageBox::warning(this, "Agregar producto", "¡Debe ingresar la descripción del producto!");
              }
              else
                QMessageBox::warning(this, "Agregar producto", "¡Debe ingresar el código de inventario del producto!");
          }
          else
            QMessageBox::warning(this, "Agregar producto", "¡Debe ingrear la cuenta contable a la que pertenece el inventario!");
      }
      else
        QMessageBox::warning(this, "Agregar producto", "¡Debe seleccionar un grupo al cual pertenece el producto!");
  }
  else
    QMessageBox::warning(this, "Agregar producto", "¡Debe seleccionar bodega donde se encuentra el producto!");
}

void Inventory::addNewProduct ( ) {
  InventoryDB *inventory = new InventoryDB();
  QList<QString> list;

  if ( fname != nullptr) {
      uploadImageByHttp();
      inventory->addNewProduct(
        ui->txtNewDescription->text(),
        ui->txtNewQty->text().toInt(),
        ui->cbxNewUnit->currentText(),
        ui->cbxNewGroup->currentText(),
        ui->cbxNewWarehouse->currentText(),
        ui->txtNewInventoryCode->text(),
        ui->txtNewPrice->text().toDouble(),
        ui->txtNewCost->text().toDouble(),
        ui->txtNewInventoryCode->text() + "." + fnamelist[1],
        ui->txtNewAccount->text()
        );

      clearAllControls();
      connect(
        ui->tblInventory->selectionModel(),
        SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),
        SLOT(on_tblSelectionChanged(const QItemSelection &, const QItemSelection &))
       );

      setProductDetailsHide(false);
      setNewProductHide(true);
      setAcceptDrops(false);
      setTableInventory("", 100);

  }
  else
    QMessageBox::warning(this, "Agregar producto", "¡Debe agregar una imágen relativa al producto!");

}

void Inventory::dragEnterEvent( QDragEnterEvent *event ) {

  if (event->mimeData()->hasUrls()) {
      event->acceptProposedAction();
    }
}

void Inventory::dropEvent ( QDropEvent *event ) {

  QStringList accepted_types;
  accepted_types << "jpeg" << "jpg" << "png";
  foreach ( const QUrl &url, event->mimeData()->urls()) {
      fname = url.toLocalFile();

      QFileInfo info(fname);
      if ( info.exists() ) {
          if ( accepted_types.contains( info.suffix().trimmed(), Qt::CaseInsensitive)) {
              QPixmap pixmap(fname);
              ui->imgNewPicture->setScaledContents(true);
              ui->imgNewPicture->setPixmap(pixmap);
              fnamelist = fname.split(".");
          }
      }
  }
}

void Inventory::uploadImageByHttp () {
  QByteArray postData;
      //Look below for buildUploadString() function
  postData = buildUploadString();

  QUrl mResultsURL = QUrl("http://192.168.20.1/eremas/upload.php");
  QNetworkAccessManager* manager = new QNetworkAccessManager(this);

  QString bound="margin"; //name of the boundary

  QNetworkRequest request(mResultsURL); //our server with php-script
  request.setRawHeader(QString("Content-Type").toUtf8(), QString("multipart/form-data; boundary=" + bound).toUtf8());
  request.setRawHeader(QString("Content-Length").toUtf8(), QString::number(postData.length()).toUtf8());

  connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*))); //This slot is used to debug the output of the server script
  QNetworkReply *reply = manager->post(request,postData);
  connect(reply, &QNetworkReply::uploadProgress, this, &Inventory::uploadProgressBar);
}

QByteArray Inventory::buildUploadString() {
  QString path = "";
  path.append(fname);

  QString bound="margin";
  QByteArray data(QString("--" + bound + "\r\n").toUtf8());
  data.append("Content-Disposition: form-data; name=\"action\"\r\n\r\n");
  data.append("uploadFile.php\r\n");
  data.append(QString("--" + bound + "\r\n").toUtf8());
  data.append("Content-Disposition: form-data; name=\"uploaded\"; filename=\"");

  QFile file(path);
  QFileInfo info(file.fileName());
  QString filepath (info.filePath());
  path = info.absolutePath() + "/" + ui->txtNewInventoryCode->text() + "." + fnamelist[1];

  data.append(path);
  data.append("\"\r\n");
  data.append("Content-Type: text/xml\r\n\r\n"); //data type

  if (!file.open(QIODevice::ReadOnly)){
    qDebug() << "QFile Error: File not found!";
    return data;
  }
  else {
    data.append(file.readAll());
    data.append("\r\n");
    data.append("--" + bound + "--\r\n");  //closing boundary according to rfc 1867
  }
  return data;
}

void Inventory::replyFinished( QNetworkReply* reply) {

  if( reply->error() ) {
    QMessageBox::critical(this, "Agregar producto", "Existe un error de comunicación: " + reply->errorString());
  }
  else {
      if ( reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() != 200 )
        QMessageBox::critical(this, "Agregar producto", "Se generó un error: " + reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toString());
  }

  reply->deleteLater();
}

void Inventory::clearAllControls() {
  ui->txtNewDescription->clear();
  ui->cbxNewWarehouse->clear();
  ui->cbxNewGroup->clear();
  ui->txtNewAccount->clear();
  ui->txtNewInventoryCode->clear();
  ui->cbxNewUnit->clear();
  ui->txtNewQty->clear();
  ui->txtNewPrice->clear();
  ui->txtNewCost->clear();
  ui->txtNewPrice->clear();
  ui->pgbDownload->hide();
}

void Inventory::on_tblSelectionChanged ( const QItemSelection &selected, const QItemSelection &unselected ) {
  if ( !selected.isEmpty() ) {
    setNewProductHide(true);
    setProductCostHide(true);
    setProductDetailsHide(false);
    QItemSelectionModel *index = ui->tblInventory->selectionModel();
    QString code = selected.at(CODE).model()->data(index->currentIndex().model()->index(index->currentIndex().row(), CODE)).toString();

    InventoryDB *inventory = new InventoryDB();
    QList<InventoryDB> list = inventory->allInventory (code, 100);

    ui->lblWarehouse->setText(list.at(0).warehouse);
    ui->lblGroup->setText(list.at(0).group);
    ui->lblAccounting->setText(list.at(0).accounting_code);
    ui->lblPrice->setText("$ " + QString::number(list.at(0).price));
    ui->lblMinimum->setText(QString::number(list.at(0).minimum));
    ui->lblIngressDate->setText(list.at(0).ingress_date.toString("dd/MM/yyyy"));
    ui->lblSaleDate->setText(list.at(0).sale_date.toString("dd/MM/yyyy"));

    QNetworkAccessManager *nam = new QNetworkAccessManager(this);
    connect(nam, &QNetworkAccessManager::finished, this, &Inventory::downloadFinished);

    const QUrl url = QUrl( "http://192.168.20.1/eremas/" + list.at(0).picture_path );
    QNetworkRequest request(url);
    QNetworkReply *reply = nam->get(request);
    connect(reply, &QNetworkReply::downloadProgress, this, &Inventory::downloadProgressBar);
  }
}

void Inventory::downloadFinished ( QNetworkReply *reply ) {
  QPixmap pm;
  pm.loadFromData(reply->readAll());

  if( reply->error() ) {
    ui->imgProductPicture->clear();
    QMessageBox::warning(this, "Ver producto", "Existe un error de comunicación: " + reply->errorString());
  }
  else {
      if ( reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() == 200 ) {
        ui->imgProductPicture->setScaledContents(true);
        ui->imgProductPicture->setPixmap(pm);
      }
      else
        QMessageBox::warning(this, "Agregar producto", "Se generó un error: " + reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toString());
  }
}

void Inventory::on_btnNewCancel_clicked()
{
    setNewProductHide(true);
    setProductDetailsHide(false);
}

void Inventory::downloadProgressBar( qint64 ist, qint64 max ) {
  ui->pgbDownload->setRange ( 0, int(max) );
  ui->pgbDownload->setValue ( int(ist) );
  if ( ist ==  max) ui->pgbDownload->hide();
}

void Inventory::uploadProgressBar( qint64 ist, qint64 max ) {
  ui->pgbUpload->setHidden(false);
  ui->pgbUpload->setRange ( 0, int(max) );
  ui->pgbUpload->setValue ( int(ist) );
  if ( ist ==  max) ui->pgbDownload->hide();
}

void Inventory::on_txtSearchOptions_textEdited(const QString &arg1) {
  if ( arg1.isEmpty() )
    setTableInventory("", -1);
  else {
    setTableInventory( arg1, ui->cbxSearchOptions->currentIndex());
    setSelectionChanged();
  }
}

void Inventory::on_txtNewProductCost_cursorPositionChanged(int arg1, int arg2)
{

}
