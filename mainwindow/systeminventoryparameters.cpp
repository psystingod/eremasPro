#include "systeminventoryparameters.h"
#include "ui_systeminventoryparameters.h"

#include <QtDebug>

SystemInventoryParameters::SystemInventoryParameters(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SystemInventoryParameters)
{
    ui->setupUi(this);
    setTableUnits ("");
    setTableWarehouses ("");
    setTableProductFamily ("");
}

SystemInventoryParameters::~SystemInventoryParameters()
{
    delete ui;
}

/*
void SystemInventoryParameters::setComboxTaxes () {
    TaxesDB *taxesDB = new TaxesDB ();
    QList<TaxesDB> list = taxesDB->allTaxes();
    int countRows = list.size();

    for (int row = 0; row < countRows; row++ ) {
        ui->cbxTaxes->addItem("Iva", taxesDB->allTaxes().at(row).iva);
        ui->cbxTaxes->addItem("Pac", taxesDB->allTaxes().at(row).iva);
        ui->cbxTaxes->addItem("Cesc", taxesDB->allTaxes().at(row).iva);
    }
    ui->cbxTaxes->setCurrentText("");
}

*/

void SystemInventoryParameters::setTableUnits (const QString &name) {
    UnitsDB *unitsDB = new UnitsDB();
    QList<UnitsDB> list = unitsDB->allUnits(name);

    int countRows = list.size();

    QStandardItemModel *model = new QStandardItemModel(countRows, 2, this);
    model->setHorizontalHeaderLabels({ "Nombre", "Unidad"});

    ui->tblUnitsMeasurement->setModel(model);
    ui->tblUnitsMeasurement->verticalHeader()->setVisible(false);
    ui->tblUnitsMeasurement->setShowGrid(false);
    ui->tblUnitsMeasurement->verticalHeader()->setDefaultSectionSize(18);

    ui->tblUnitsMeasurement->horizontalHeader()->setStretchLastSection(QHeaderView::Stretch);

    for (int row = 0; row < countRows; row++) {
        model->setData(model->index(row, UNITSNAME, QModelIndex()), list.at(row).name);
        model->setData(model->index(row, UNIT, QModelIndex()), list.at(row).unitName);
    }
    ui->tblUnitsMeasurement->setSelectionMode(QAbstractItemView::SingleSelection);
}

void SystemInventoryParameters::setTableWarehouses ( const QString &name) {
    WareHouseDB *wareHouseDB = new WareHouseDB();
    QList<WareHouseDB> list = wareHouseDB->allWarehouses(name);

    int countRows = list.size();

    QStandardItemModel *model = new QStandardItemModel(countRows, 3, this);
    model->setHorizontalHeaderLabels({ "Nombre", "Código", "Dirección"});

    ui->tblWareHouse->setModel(model);
    ui->tblWareHouse->verticalHeader()->setVisible(false);
    ui->tblWareHouse->setShowGrid(false);
    ui->tblWareHouse->verticalHeader()->setDefaultSectionSize(18);

    ui->tblWareHouse->horizontalHeader()->setStretchLastSection(QHeaderView::Stretch);

    for (int row = 0; row < countRows; row++) {
        model->setData(model->index(row, WAREHOUSENAME, QModelIndex()), list.at(row).name);
        model->setData(model->index(row, WAREHOUSECODE, QModelIndex()), list.at(row).wareHouseId);
        model->setData(model->index(row, WAREHOUSECODE, QModelIndex()), Qt::AlignCenter, Qt::TextAlignmentRole);
        model->setData(model->index(row, ADDRESS, QModelIndex()), list.at(row).address);
    }
    ui->tblWareHouse->setSelectionMode(QAbstractItemView::SingleSelection);
}

void SystemInventoryParameters::setTableProductFamily ( const QString &name) {
    ProductFamilyDB *productFamilyDB = new ProductFamilyDB();
    QList<ProductFamilyDB> list = productFamilyDB->allProductFamily(name);

    int countRows = list.size();

    QStandardItemModel *model = new QStandardItemModel(countRows, 3, this);
    model->setHorizontalHeaderLabels({ "Nombre", "Abreviatura", "Código" });

    ui->tblProductGroup->setModel(model);
    ui->tblProductGroup->verticalHeader()->setVisible(false);
    ui->tblProductGroup->setShowGrid(false);
    ui->tblProductGroup->verticalHeader()->setDefaultSectionSize(18);

    ui->tblProductGroup->horizontalHeader()->setStretchLastSection(QHeaderView::Stretch);

    for (int row = 0; row < countRows; row++) {
        model->setData(model->index(row, FAMILYNAME, QModelIndex()), list.at(row).name);
        model->setData(model->index(row, FAMILYABBREVIATED, QModelIndex()), list.at(row).abbreviated);
        model->setData(model->index(row, FAMILYABBREVIATED, QModelIndex()), Qt::AlignCenter, Qt::TextAlignmentRole);
        model->setData(model->index(row, FAMILYCODE, QModelIndex()), list.at(row).code);
        model->setData(model->index(row, FAMILYCODE, QModelIndex()), Qt::AlignCenter, Qt::TextAlignmentRole);
    }
    ui->tblProductGroup->setSelectionMode(QAbstractItemView::SingleSelection);
}

void SystemInventoryParameters::on_btnNewUnit_clicked()
{
    if ( !ui->txtUnitName->text().isEmpty() || !ui->txtUnit->text().isEmpty() ) {
        UnitsDB *unitsDB = new UnitsDB();
        unitsDB->addNew(ui->txtUnitName->text(), ui->txtUnit->text() );

        setTableUnits("");
        ui->txtUnitName->setText("");
        ui->txtUnit->setText("");
    }

    else QMessageBox::information(this, "Agregar Nueva Unidad", "¡El nombre de la unidad y la unidad no pueden ser vacíos!");
}

void SystemInventoryParameters::on_btnNewWareHouse_clicked()
{
    if ( !ui->txtWareHouseName->text().isEmpty() || !ui->txtWareHouseAddress->text().isEmpty() ) {
        WareHouseDB *wareHouseDB = new WareHouseDB();
        wareHouseDB->addNewWareHouse(ui->txtWareHouseName->text(), ui->txtWareHouseAddress->text() );

        setTableWarehouses("");
        ui->txtWareHouseName->setText("");
        ui->txtWareHouseAddress->setText("");
    }

    else QMessageBox::information(this, "Agregar Nueva Bodega", "¡El nombre de la bodega y la dirección no pueden ser vacíos!");
}

void SystemInventoryParameters::on_btnNewProductFamily_clicked()
{
    if ( !ui->txtGroupName->text().isEmpty() ) {
        ProductFamilyDB *productFamilyDB = new ProductFamilyDB();
        productFamilyDB->addNewProductFamily(ui->txtGroupName->text(), ui->txtGroupCode->text() );

        setTableProductFamily("");
    }

    else QMessageBox::information(this, "Agregar Nuevo Departamento", "¡El nombre del departmento no puede ser vacío!");
}

void SystemInventoryParameters::on_txtSearchUnit_textEdited(const QString &txtSearchUnit)
{
    setTableUnits(txtSearchUnit);
}

void SystemInventoryParameters::on_txtSearchWarehouse_textEdited(const QString &txtSearchWarehouse)
{
    setTableWarehouses(txtSearchWarehouse);
}

void SystemInventoryParameters::on_txtSearchFamily_textEdited(const QString &txtSearchFamily)
{
    setTableProductFamily ( txtSearchFamily );
}

void SystemInventoryParameters::resizeEvent( QResizeEvent *event ) {
  ui->tblWareHouse->setColumnWidth(WAREHOUSENAME, parentWidget()->width()/8);
  ui->tblWareHouse->setColumnWidth(WAREHOUSECODE, parentWidget()->width()/8);
  ui->tblWareHouse->setColumnWidth(ADDRESS, parentWidget()->width()/3);

  ui->tblUnitsMeasurement->setColumnWidth(UNITSNAME, parentWidget()->width()/3);
  ui->tblUnitsMeasurement->setColumnWidth(UNIT, parentWidget()->width()/8);

  ui->tblProductGroup->setColumnWidth(FAMILYNAME, parentWidget()->width()/4);
  ui->tblProductGroup->setColumnWidth(FAMILYABBREVIATED, parentWidget()->width()/9);
  ui->tblProductGroup->setColumnWidth(FAMILYCODE, parentWidget()->width()/10);

  QWidget::resizeEvent(event);
}
