#include "appwindow.h"
#include "ui_appwindow.h"
#include <QtDebug>

static bool strechedSplitter = false;
static QWidget* myparent;

AppWindow::AppWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AppWindow)

{
    myparent = parent;
    ui->setupUi(this);
    showAppWindow();
    setUsername();
    loadTreeViewMenu();

}

AppWindow::~AppWindow()
{
    delete ui;
}

void AppWindow::showAppWindow( ) {
    ui->mainSplitter->setHandleWidth(1);
    ui->leftSplitter->setHandleWidth(1);
    ui->treeWidget->setStyleSheet("QTreeWidget { background: solid #ffffff; border: none; }");
    ui->parentLayout->setMargin(0);
    ui->parentLayout->setSpacing(0);
    ui->toolWidget->setStyleSheet("#toolWidget { border: 1px solid #bababa; border-top: none; border-right: none; border-left: none; }");

}

void AppWindow::setUsername() {
    Setting *setting = new Setting();
    ui->lblUsername->setText(setting->getAppUser());
}

void AppWindow::loadTreeViewMenu () {
    QList<QString> rootMenuItems ({ "Configuración", "Planillas", "Bancos", "Presupuestos", "Activo Fijo", "Gestión Administrativa", "Gestión Comercial", "Facturación", "Inventario", "Contabilidad", "IVA", "Cuentas por pagar",
                                    "Cuentas por Cobrar", "Reportes"});

    foreach ( QString str, rootMenuItems) {
        addTreeViewRoot(str, rootMenuItems.indexOf(str));
    }
}

void AppWindow::addTreeViewRoot (QString name, int index) {
    QTreeWidgetItem *root = new QTreeWidgetItem(ui->treeWidget);
    root->setText(0, name);
    ui->treeWidget->addTopLevelItem(root);

    QList<QString> childMenuItems;
    switch (index) {
    case 0:
        childMenuItems = {"Usuarios", "Zonas", "Empresas", "Inventario", "Bancos", "Contabilidad" };
        break;

    case 1:
        childMenuItems = {"Empleados", "AFPs", "Seguro Social", "Cálculo de planillas"};
        break;

    case 2:
        childMenuItems = {"Bancos", "Cheques", "Transacciones Bancarias", "Libro de bancos"};
        break;

    case 3:
        childMenuItems = {"Divisiones", "Presupuestos", "Presupuesto Departamento", "Presupestos Consolidado"};
        break;

    case 4:
        childMenuItems = {"Cotizaciones", "Ventas"};
        break;

    case 5:
        childMenuItems = {"Clientes", "Proveedores", "Toma de pedido" };
        break;

    case 6:
        childMenuItems = {"Clasificaciones", "Ubicaciones", "Activos", "Departamento Individual", "Departamento General" };
        break;

    case 7:
        childMenuItems = {"Manual", "Productos", "Servicios", "Grupos", "Compras", "Información de costos", "Clientes"};
        break;

    case 8:
        childMenuItems = {"Solicitud de Compra", "Importaciones", "Inventario", "Cardex", "Información de costos", "Clientes"};
        break;

    case 9:
        childMenuItems = {"Catálogo de cuentas", "Partidas", "Libro mayor", "Libro diario", "Libro auxiliar", "Estdo de resultados", "Balance de comprobación", "Balance General"};
        break;

    case 10:
        childMenuItems = {"Compras", "Comprobante de retención", "Libro de ventas", "Libro de compras"};
        break;

    case 11:
      childMenuItems = {"Clientes", "Abonos", "Análisis de cuentas por cobrar"};
      break;

    case 12:
      childMenuItems = {"Proveedores", "Quedan", "Abonos", "Análisis de cuentas por pagar", "Auxiliar de cuentas por pagar"};
      break;

    case 13:
      childMenuItems = {"Clientes", "Cobros", "Ventas", "Flujo de caja", "Planilla", "Costo proyectos"};
      break;
    }

    foreach (QString str, childMenuItems) {
        addTreeViewChild(root, str);
    }
}

void AppWindow::addTreeViewChild (QTreeWidgetItem *parent, QString name ) {
    QTreeWidgetItem *itm = new QTreeWidgetItem();
    itm->setText(0, name);
    parent->addChild(itm);
}

void AppWindow::on_btnShowMenu_clicked()
{
    if(!strechedSplitter) {
        ui->mainSplitter->setSizes({0,16777215});
        strechedSplitter = true;

    }

    else {
        ui->mainSplitter->setSizes({250, 400});
        strechedSplitter = false;
    }

}

void AppWindow::on_treeWidget_itemClicked(QTreeWidgetItem *item)
{
    QModelIndex index = item->treeWidget()->currentIndex();

    switch (index.parent().row()) {
    case 0:
        switch(index.row()){
          case 0:
          {
            SystemUsers *systemUsers = new SystemUsers(ui->childWidget);
            ui->childWidget->close();
            ui->childLayout->addWidget(systemUsers);
            ui->childWidget = systemUsers;
            break;
          }

          case 3:
          {
            SystemInventoryParameters *systemInventoryParameters = new SystemInventoryParameters(ui->childWidget);
            ui->childWidget->close();
            ui->childLayout->addWidget(systemInventoryParameters);
            ui->childWidget = systemInventoryParameters;
            break;
          }

          default:
            break;
        }
        break;

    case 5:
        switch (index.row()) {
          case 0:
          {
            Customers *customers = new Customers();
            ui->childWidget->close();
            ui->childLayout->addWidget(customers);
            ui->childWidget = customers;
            break;
          }
           case 1:
          {
            Proveedores *providers = new Proveedores();
            ui->childWidget->close();
            ui->childLayout->addWidget(providers);
            ui->childWidget = providers;
            break;
          }

          case 2:
          {
            SaleRequest *saleRequest = new SaleRequest();
            ui->childWidget->close();
            ui->childLayout->addWidget(saleRequest);
            ui->childWidget = saleRequest;
            break;
          }
          default:
            break;
        }
        break;

    case 6:
      switch (index.row()) {
        case 1:
        {
          Departments *departments = new Departments();
          ui->childWidget->close();
          ui->childLayout->addWidget(departments);
          ui->childWidget = departments;
          break;
        }
        default:
          break;
      }
      break;


      case 7:
        switch (index.row()) {
          case 1:
          {
            ProductBilling *productBilling = new ProductBilling();
            ui->childWidget->close();
            ui->childLayout->addWidget(productBilling);
            ui->childWidget = productBilling;
            break;
          }
          default:
            break;
        }
        break;

    case 8:
        switch(index.row()){
            case 2:
            {
                Inventory *inventory = new Inventory(ui->childWidget);
                ui->childWidget->close();
                ui->childLayout->addWidget(inventory);
                ui->childWidget = inventory;
                break;
            }

            default:
                break;
        }
        break;

      case 9:
        switch(index.row()){
            case 0:
            {
                CatalogOfAccounts *catalog = new CatalogOfAccounts(ui->childWidget);
                ui->childWidget->close();
                ui->childLayout->addWidget(catalog);
                ui->childWidget = catalog;
                break;
            }

            default:
                break;
        }
        break;

    default:
        break;
    }
}
