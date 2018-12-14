#include "proveedores.h"
#include "ui_proveedores.h"
#include "dbconnection/mysqlconnection.h"
#include <QApplication>
#include <QRegExp>

Proveedores::Proveedores(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Proveedores)
{
    ui->setupUi(this);
    //QRegExp telephone("[0-9]{1,4}\\-\\.*[0-9]{1,4}");
    //QRegExp chacters("[A-Za-z]+@[0-9]+");
    QRegExp telephone("[0-9]{0,8}");
    QRegExp nit("[0-9]{4}-[0-9]{6}-[0-9]{3}-[0-9]{1}");

    //INPUT MASK
    /*ui->telefonoLineEdit->setInputMask("9999-9999");
    ui->nitLineEdit->setInputMask("9999-999999-999-9");*/

    ui->telefonoLineEdit->setValidator(new QRegExpValidator(telephone,this));
    ui->nitLineEdit->setValidator(new QRegExpValidator(nit,this));
    //ui->nombreDelProveedorLineEdit->setValidator(new QRegExpValidator(chacters, this));
    //ui->direccionLineEdit->setValidator(new QRegExpValidator(chacters, this));
    //ui->giroLineEdit->setValidator(new QRegExpValidator(chacters, this));
    //ui->nacionalidadLineEdit->setValidator(new QRegExpValidator(chacters, this));
    //ui->vendedorLineEdit->setValidator(new QRegExpValidator(chacters, this));
    //ui->categoriaLineEdit->setValidator(new QRegExpValidator(chacters, this));


    if(conn->open("eremasinprel")){
        query.prepare("select id_proveedor, nombre, giro, categoria, nacionalidad, telefono from providers");
        query.exec();

        modelProviders->setQuery(query);
        //Set table providers
        ui->tableViewProviders->setModel(modelProviders);
        ui->tableViewProviders->verticalHeader()->setVisible(false);
        ui->tableViewProviders->setShowGrid(true);

        modelProviders->setHeaderData(0, Qt::Horizontal, QObject::tr("CODIGO"));
        modelProviders->setHeaderData(1, Qt::Horizontal, QObject::tr("NOMBRE"));
        modelProviders->setHeaderData(2, Qt::Horizontal, QObject::tr("GIRO"));
        modelProviders->setHeaderData(3, Qt::Horizontal, QObject::tr("CATEGORIA"));
        modelProviders->setHeaderData(4, Qt::Horizontal, QObject::tr("NACIONALIDAD"));
        modelProviders->setHeaderData(5, Qt::Horizontal, QObject::tr("TELEFONO"));

        ui->tableViewProviders->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->tableViewProviders->setSelectionMode(QAbstractItemView::SingleSelection);
        ui->tableViewProviders->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
        ui->tableViewProviders->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
        ui->tableViewProviders->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
        ui->tableViewProviders->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);
        ui->tableViewProviders->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Stretch);
        ui->tableViewProviders->horizontalHeader()->setSectionResizeMode(5, QHeaderView::Stretch);


        /*modelProviders->setHeaderData(0, Qt::Horizontal, QObject::tr("Código"));
        modelProviders->setHeaderData(1, Qt::Horizontal, QObject::tr("Nombre"));
        modelProviders->setHeaderData(2, Qt::Horizontal, QObject::tr("NIT"));
        modelProviders->setHeaderData(3, Qt::Horizontal, QObject::tr("NRC"));
        modelProviders->setHeaderData(4, Qt::Horizontal, QObject::tr("Dirección"));
        modelProviders->setHeaderData(5, Qt::Horizontal, QObject::tr("Giro"));
        modelProviders->setHeaderData(6, Qt::Horizontal, QObject::tr("Nacionalidad"));
        modelProviders->setHeaderData(7, Qt::Horizontal, QObject::tr("Teléfono"));
        modelProviders->setHeaderData(8, Qt::Horizontal, QObject::tr("Correo electrónico"));
        modelProviders->setHeaderData(9, Qt::Horizontal, QObject::tr("Representante"));
        modelProviders->setHeaderData(10, Qt::Horizontal, QObject::tr("Cuenta en el catálogo"));*/

        conn->close();
    }
}

Proveedores::~Proveedores()
{
    delete ui;
}

void Proveedores::on_btn_new_clicked()
{
    //Setting action = 1 = INSERT INTO
    action = 1;

    //Setting enabled all the form
    ui->idLineEdit->setEnabled(false);
    ui->nitLineEdit->setEnabled(true);
    ui->nrcLineEdit->setEnabled(true);
    ui->nombreDelProveedorLineEdit->setEnabled(true);
    ui->direccionLineEdit->setEnabled(true);
    ui->giroLineEdit->setEnabled(true);
    ui->categoriaLineEdit->setEnabled(true);
    ui->nacionalidadLineEdit->setEnabled(true);
    ui->telefonoLineEdit->setEnabled(true);
    ui->correoElectronicoLineEdit->setEnabled(true);
    ui->vendedorLineEdit->setEnabled(true);
    ui->cuentaEnElCatalogoLineEdit->setEnabled(true);

    // Clean all the form
    ui->idLineEdit->clear();
    ui->nitLineEdit->clear();
    ui->nrcLineEdit->clear();
    ui->nombreDelProveedorLineEdit->clear();
    ui->direccionLineEdit->clear();
    ui->giroLineEdit->clear();
    ui->categoriaLineEdit->clear();
    ui->nacionalidadLineEdit->clear();
    ui->telefonoLineEdit->clear();
    ui->correoElectronicoLineEdit->clear();
    ui->vendedorLineEdit->clear();
    ui->cuentaEnElCatalogoLineEdit->clear();

    ui->btn_edit->setDisabled(true);
    ui->btn_save->setEnabled(true);
}

void Proveedores::on_btn_edit_clicked()
{
    //Setting action = 2 = UPDATE
    action = 2;
    ui->btn_new->setDisabled(true);
    ui->btn_save->setEnabled(true);

    //Setting enabled all the form
    ui->idLineEdit->setEnabled(false);
    ui->nitLineEdit->setEnabled(true);
    ui->nrcLineEdit->setEnabled(true);
    ui->nombreDelProveedorLineEdit->setEnabled(true);
    ui->direccionLineEdit->setEnabled(true);
    ui->giroLineEdit->setEnabled(true);
    ui->categoriaLineEdit->setEnabled(true);
    ui->nacionalidadLineEdit->setEnabled(true);
    ui->telefonoLineEdit->setEnabled(true);
    ui->correoElectronicoLineEdit->setEnabled(true);
    ui->vendedorLineEdit->setEnabled(true);
    ui->cuentaEnElCatalogoLineEdit->setEnabled(true);
}

void Proveedores::on_btn_save_clicked()
{
    // Getting data from form
    int id = ui->idLineEdit->text().toInt();
    QString nombre = ui->nombreDelProveedorLineEdit->text();
    QString nit = ui->nitLineEdit->text();
    QString nrc = ui->nrcLineEdit->text();
    QString direccion = ui->direccionLineEdit->text();
    QString giro = ui->giroLineEdit->text();
    QString categoria = ui->categoriaLineEdit->text();
    QString nacionalidad = ui->nacionalidadLineEdit->text();
    QString telefono = ui->telefonoLineEdit->text();
    QString correo_electronico = ui->correoElectronicoLineEdit->text();
    QString representante = ui->vendedorLineEdit->text();
    QString cuenta_catalogo = ui->cuentaEnElCatalogoLineEdit->text();

    QMessageBox msgBox;
    msgBox.setText(tr("¿Realmente desea realizar esta acción?"));
    QAbstractButton* pButtonYes = msgBox.addButton(tr("Aceptar"), QMessageBox::YesRole);
    msgBox.addButton(tr("Cancelar"), QMessageBox::NoRole);

    msgBox.exec();

    if (msgBox.clickedButton()==pButtonYes) {
        //qDebug() << action;

        if(conn->open("eremasinprel")){
            switch (action) {
            case 1: {
                query.prepare("INSERT INTO providers(nombre, nit, nrc, direccion, giro, categoria, nacionalidad, telefono, correo_electronico, representante, cuenta_catalogo) "
                              "VALUES(:nombre, :nit, :nrc, :direccion, :giro, :categoria, :nacionalidad, :telefono, :correo_electronico, :representante, :cuenta_catalogo)");
                query.bindValue(":nombre", nombre);
                query.bindValue(":nit", nit);
                query.bindValue(":nrc", nrc);
                query.bindValue(":direccion", direccion);
                query.bindValue(":giro", giro);
                query.bindValue(":categoria", categoria);
                query.bindValue(":nacionalidad", nacionalidad);
                query.bindValue(":telefono", telefono);
                query.bindValue(":correo_electronico", correo_electronico);
                query.bindValue(":representante", representante);
                query.bindValue(":cuenta_catalogo", cuenta_catalogo);

                QString nom = ui->nombreDelProveedorLineEdit->text();
                QString ni = ui->nitLineEdit->text();
                QString nr = ui->nrcLineEdit->text();
                QString dir = ui->direccionLineEdit->text();
                QString gir = ui->giroLineEdit->text();
                QString cat = ui->categoriaLineEdit->text();
                QString nac = ui->nacionalidadLineEdit->text();
                QString tel = ui->telefonoLineEdit->text();
                QString cue = ui->cuentaEnElCatalogoLineEdit->text();

                if(nom.isEmpty() or ni.isEmpty() or nr.isEmpty() or dir.isEmpty() or gir.isEmpty() or cat.isEmpty() or nac.isEmpty() or tel.isEmpty() or cue.isEmpty()){
                    QMessageBox verify;
                    verify.setText(tr("Por favor asegurese de llenar todos los campos obligatorios(*)"));
                    verify.exec();

                    //Setting enabled all the form
                    ui->idLineEdit->setEnabled(false);
                    ui->nitLineEdit->setEnabled(true);
                    ui->nrcLineEdit->setEnabled(true);
                    ui->nombreDelProveedorLineEdit->setEnabled(true);
                    ui->direccionLineEdit->setEnabled(true);
                    ui->giroLineEdit->setEnabled(true);
                    ui->categoriaLineEdit->setEnabled(true);
                    ui->nacionalidadLineEdit->setEnabled(true);
                    ui->telefonoLineEdit->setEnabled(true);
                    ui->correoElectronicoLineEdit->setEnabled(true);
                    ui->vendedorLineEdit->setEnabled(true);
                    ui->cuentaEnElCatalogoLineEdit->setEnabled(true);
                } else if(ni.length() < 17){
                    QMessageBox verifyNit;
                    verifyNit.setText(tr("Por favor verifique que el NIT o el NRC cumplan con el formato establecido, respetando guiones"));
                    verifyNit.exec();

                    //Setting enabled all the form
                    ui->idLineEdit->setEnabled(false);
                    ui->nitLineEdit->setEnabled(true);
                    ui->nrcLineEdit->setEnabled(true);
                    ui->nombreDelProveedorLineEdit->setEnabled(true);
                    ui->direccionLineEdit->setEnabled(true);
                    ui->giroLineEdit->setEnabled(true);
                    ui->categoriaLineEdit->setEnabled(true);
                    ui->nacionalidadLineEdit->setEnabled(true);
                    ui->telefonoLineEdit->setEnabled(true);
                    ui->correoElectronicoLineEdit->setEnabled(true);
                    ui->vendedorLineEdit->setEnabled(true);
                    ui->cuentaEnElCatalogoLineEdit->setEnabled(true);
                }
                else {
                    query.exec();
                    //Setting disabled all the form
                    ui->idLineEdit->setDisabled(true);
                    ui->nitLineEdit->setDisabled(true);
                    ui->nrcLineEdit->setDisabled(true);
                    ui->nombreDelProveedorLineEdit->setDisabled(true);
                    ui->direccionLineEdit->setDisabled(true);
                    ui->giroLineEdit->setDisabled(true);
                    ui->categoriaLineEdit->setDisabled(true);
                    ui->nacionalidadLineEdit->setDisabled(true);
                    ui->telefonoLineEdit->setDisabled(true);
                    ui->correoElectronicoLineEdit->setDisabled(true);
                    ui->vendedorLineEdit->setDisabled(true);
                    ui->cuentaEnElCatalogoLineEdit->setDisabled(true);

                    //Setting disabled buttons
                    ui->btn_edit->setDisabled(true);
                    ui->btn_save->setDisabled(true);
                    ui->btn_new->setEnabled(true);
                }
            }

                //Recharge table providers
                query.prepare("select id_proveedor, nombre, giro, categoria, nacionalidad, telefono from providers");
                query.exec();
                modelProviders->setQuery(query);
                ui->tableViewProviders->setModel(modelProviders);

                //Closing database
                conn->close();

                break;
            case 2:
                query.prepare("UPDATE providers SET nombre=:nombre, nit=:nit, nrc=:nrc, direccion=:direccion, giro=:giro, categoria=:categoria, nacionalidad=:nacionalidad, telefono=:telefono, correo_electronico=:correo_electronico, representante=:representante, cuenta_catalogo=:cuenta_catalogo  WHERE id_proveedor=:id_proveedor");
                query.bindValue(":nombre", nombre);
                query.bindValue(":nit", nit);
                query.bindValue(":nrc", nrc);
                query.bindValue(":direccion", direccion);
                query.bindValue(":giro", giro);
                query.bindValue(":categoria", categoria);
                query.bindValue(":nacionalidad", nacionalidad);
                query.bindValue(":telefono", telefono);
                query.bindValue(":correo_electronico", correo_electronico);
                query.bindValue(":representante", representante);
                query.bindValue(":cuenta_catalogo", cuenta_catalogo);
                query.bindValue(":id_proveedor", id);
                query.exec();

                //Recharge table providers
                query.prepare("select id_proveedor, nombre, giro, categoria, nacionalidad, telefono from providers");
                query.exec();
                modelProviders->setQuery(query);
                ui->tableViewProviders->setModel(modelProviders);

                //Closing database
                conn->close();

                //Setting disabled all the form
                ui->idLineEdit->setDisabled(true);
                ui->nitLineEdit->setDisabled(true);
                ui->nrcLineEdit->setDisabled(true);
                ui->nombreDelProveedorLineEdit->setDisabled(true);
                ui->direccionLineEdit->setDisabled(true);
                ui->giroLineEdit->setDisabled(true);
                ui->categoriaLineEdit->setDisabled(true);
                ui->nacionalidadLineEdit->setDisabled(true);
                ui->telefonoLineEdit->setDisabled(true);
                ui->correoElectronicoLineEdit->setDisabled(true);
                ui->vendedorLineEdit->setDisabled(true);
                ui->cuentaEnElCatalogoLineEdit->setDisabled(true);

                //Setting disabled buttons
                ui->btn_edit->setDisabled(true);
                ui->btn_save->setDisabled(true);
                ui->btn_new->setEnabled(true);
                break;
            }
        }
    }

    else{
        ui->idLineEdit->setDisabled(true);
        ui->nitLineEdit->setDisabled(true);
        ui->nrcLineEdit->setDisabled(true);
        ui->nombreDelProveedorLineEdit->setDisabled(true);
        ui->direccionLineEdit->setDisabled(true);
        ui->giroLineEdit->setDisabled(true);
        ui->categoriaLineEdit->setDisabled(true);
        ui->nacionalidadLineEdit->setDisabled(true);
        ui->telefonoLineEdit->setDisabled(true);
        ui->correoElectronicoLineEdit->setDisabled(true);
        ui->vendedorLineEdit->setDisabled(true);
        ui->cuentaEnElCatalogoLineEdit->setDisabled(true);

        //Setting disabled buttons
        ui->btn_edit->setDisabled(true);
        ui->btn_save->setDisabled(true);
        ui->btn_new->setEnabled(true);
    }

}

void Proveedores::on_tableViewProviders_clicked(const QModelIndex &index)
{
    index_value = ui->tableViewProviders->model()->data(index).toString();
    ui->btn_new->setEnabled(true);
    ui->btn_save->setDisabled(true);
    ui->btn_edit->setEnabled(true);

    ui->idLineEdit->setDisabled(true);
    ui->nitLineEdit->setDisabled(true);
    ui->nrcLineEdit->setDisabled(true);
    ui->nombreDelProveedorLineEdit->setDisabled(true);
    ui->direccionLineEdit->setDisabled(true);
    ui->giroLineEdit->setDisabled(true);
    ui->categoriaLineEdit->setDisabled(true);
    ui->nacionalidadLineEdit->setDisabled(true);
    ui->telefonoLineEdit->setDisabled(true);
    ui->correoElectronicoLineEdit->setDisabled(true);
    ui->vendedorLineEdit->setDisabled(true);
    ui->cuentaEnElCatalogoLineEdit->setDisabled(true);

    // Setting data into form
    if(conn->open("eremasinprel")){
        QSqlQuery query2;
        //QString statement = "select * from providers where id_proveedor = '"+ index_value +"' or nombre = '"+ index_value +"' or giro = '"+ index_value +"' or nacionalidad = '"+ index_value +"' or telefono = '"+ index_value +"'";
        QString statement = "select * from providers where id_proveedor = '"+ index_value +"' or nombre = '"+ index_value +"'";
        query2.prepare(statement);
        query2.exec();

        while(query2.next()){

            ui->idLineEdit->setText(query2.value(0).toString());
            ui->nombreDelProveedorLineEdit->setText(query2.value(1).toString());
            ui->nitLineEdit->setText(query2.value(2).toString());
            ui->nrcLineEdit->setText(query2.value(3).toString());
            ui->direccionLineEdit->setText(query2.value(4).toString());
            ui->giroLineEdit->setText(query2.value(5).toString());
            ui->categoriaLineEdit->setText(query2.value(6).toString());
            ui->nacionalidadLineEdit->setText(query2.value(7).toString());
            ui->telefonoLineEdit->setText(query2.value(8).toString());
            ui->correoElectronicoLineEdit->setText(query2.value(9).toString());
            ui->vendedorLineEdit->setText(query2.value(10).toString());
            ui->cuentaEnElCatalogoLineEdit->setText(query2.value(11).toString());

        }
        //Closing database
        conn->close();

    }
}

void Proveedores::on_lineEdit_textChanged(const QString &arg1)
{
    conn->open("eremasinprel");
    searchQuery.prepare("SELECT id_proveedor, nombre, giro, categoria, nacionalidad, telefono from providers WHERE id_proveedor LIKE '"+arg1+"%' or nombre LIKE '"+arg1+"%' or giro LIKE '"+arg1+"%' or categoria LIKE '"+arg1+"%' or nacionalidad LIKE '"+arg1+"%' or telefono LIKE '"+arg1+"%'");
    searchQuery.exec();
    qDebug() << arg1;

    modelProviders->setQuery(searchQuery);

    ui->tableViewProviders->setModel(modelProviders);
    //Closing database
    conn->close();
}
