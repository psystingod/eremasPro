#include "departments.h"
#include "ui_departments.h"

Departments::Departments(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Departments)
{
    ui->setupUi(this);

    QRegExp characters("[A-Za-z_ ]+");
    QRegExp strings("[A-Za-z0-9#_ ]+");
    ui->name->setValidator(new QRegExpValidator(characters,this));
    ui->nameMun->setValidator(new QRegExpValidator(characters,this));
    ui->nameCol->setValidator(new QRegExpValidator(strings,this));

    QString searchDepartment = ui->searchDepartment->text();

    if(conn->open("eremasinprel")){
        qry.prepare("select * from departments");
        qry.exec();

        model->setQuery(qry);

        //Set table departments
        ui->tableViewDepartments->setModel(model);
        ui->tableViewDepartments->verticalHeader()->setVisible(false);
        ui->tableViewDepartments->setShowGrid(true);

        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nombre"));
        ui->tableViewDepartments->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
        ui->tableViewDepartments->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
        conn->close();
    }
}

Departments::~Departments()
{
    delete ui;
}

static int action = 0;
static int action2 = 0;
static int action3 = 0;

//Actions for btn add
void Departments::on_btnAdd_clicked()
{
    ui->btnEdit->setDisabled(true);
    ui->btnDelete->setDisabled(true);
    ui->btnSave->setEnabled(true);

    //ui->id->setEnabled(true);
    ui->name->setEnabled(true);
    ui->id->clear();
    ui->name->clear();
    action = 1;

}

//Actions for btn edit
void Departments::on_btnEdit_clicked()
{
    //ui->id->setEnabled(true);
    ui->name->setEnabled(true);
    ui->btnAdd->setDisabled(true);
    ui->btnDelete->setDisabled(true);
    ui->btnSave->setEnabled(true);
    action = 2;

}

//Actions for btn delete
void Departments::on_btnDelete_clicked()
{
    int id = ui->id->text().toInt();
    QString name = ui->name->text();

    QMessageBox msgBox;
    msgBox.setText(tr("¿Realmente quiere eliminar este registro?"));
    QAbstractButton* pButtonYes = msgBox.addButton(tr("Eliminar"), QMessageBox::YesRole);
    msgBox.addButton(tr("Cancelar"), QMessageBox::NoRole);

    msgBox.exec();

    if (msgBox.clickedButton()==pButtonYes) {
        if(conn->open("eremasinprel")){

            qry.prepare("DELETE FROM departments WHERE id=:id");
            qry.bindValue(":id", id);
            qry.exec();

            //Recharge table departments
            qry.prepare("select * from departments");
            qry.exec();
            model->setQuery(qry);
            ui->tableViewDepartments->setModel(model);
            modelMun->clear();

            ui->btnDelete->setDisabled(true);
            ui->id->clear();
            ui->name->clear();
            conn->close();
        }
    }

}

//Actions for btn save
void Departments::on_btnSave_clicked()
{
    int id = ui->id->text().toInt();
    QString name = ui->name->text();

    QMessageBox msgBox;
    msgBox.setText(tr("¿Realmente desea realizar esta acción?"));
    QAbstractButton* pButtonYes = msgBox.addButton(tr("Aceptar"), QMessageBox::YesRole);
    msgBox.addButton(tr("Cancelar"), QMessageBox::NoRole);

    msgBox.exec();

    if (msgBox.clickedButton()==pButtonYes) {
        //qDebug() << action;

        if(conn->open("eremasinprel")){
            switch (action) {
            case 1:
                qry.prepare("INSERT INTO departments(id, nombre) VALUES(:id, :name)");
                qry.bindValue(":id", id);
                qry.bindValue(":name", name);
                qry.exec();

                //Recharge table departments
                qry.prepare("select * from departments");
                qry.exec();
                model->setQuery(qry);
                ui->tableViewDepartments->setModel(model);
                conn->close();
                break;
            case 2:
                qry.prepare("UPDATE departments SET id=:id, nombre=:name WHERE id=:id");
                qry.bindValue(":id", id);
                qry.bindValue(":name", name);
                qry.exec();

                //Recharge table departments
                qry.prepare("select * from departments");
                qry.exec();
                model->setQuery(qry);
                ui->tableViewDepartments->setModel(model);
                conn->close();
                break;
            }

            ui->id->clear();
            ui->name->clear();
            ui->btnSave->setDisabled(true);
        }
    }
    else{
        ui->btnSave->setDisabled(true);
    }
    ui->btnAdd->setEnabled(true);
    ui->btnEdit->setDisabled(true);
    ui->id->setDisabled(true);
    ui->name->setDisabled(true);
}

void Departments::on_tableViewDepartments_clicked(const QModelIndex &index)
{
    ui->name->setDisabled(true);
    ui->nameCol->setDisabled(true);
    ui->nameMun->setDisabled(true);
    ui->searchMunicipie->setEnabled(true);
    ui->btnEditMun->setDisabled(true);
    ui->btnDeleteMun->setDisabled(true);
    ui->idMun->clear();
    ui->nameMun->clear();
    //Reset colonias
    ui->idCol->clear();
    ui->nameCol->clear();
    ui->nameCol->setDisabled(true);
    modelCol->clear();
    ui->btnEditCol->setDisabled(true);
    ui->btnDeleteCol->setDisabled(true);
    ui->btnEdit->setEnabled(true);
    QString valIndex = ui->tableViewDepartments->model()->data(index).toString();
    ui->btnDelete->setEnabled(true);

    if(conn->open("eremasinprel")){
        QSqlQuery qry2;
        QString stsm = "select * from departments where id = '"+ valIndex +"' or nombre = '"+ valIndex +"'";
        qry2.prepare(stsm);
        qry2.exec();

        while(qry2.next()){

            ui->id->setText(qry2.value(0).toString());
            ui->name->setText(qry2.value(1).toString());

        }
        conn->close();

    }

    //db.open();
    //qry.prepare("select idMunicipio, nombre from municipies WHERE id=?");
    //qry.bindValue(0, ui->id->text().toInt());
    //qry.exec();

    //modelMun->setQuery(qry);

    if(conn->open("eremasinprel")){
        qry.prepare("select idMunicipio, nombre from municipies WHERE id=?");
        qry.bindValue(0, ui->id->text().toInt());
        qry.exec();

        modelMun->setQuery(qry);

        //Set table municipies
        ui->tableViewMunicipie->setModel(modelMun);
        ui->tableViewMunicipie->verticalHeader()->setVisible(false);


        modelMun->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
        modelMun->setHeaderData(1, Qt::Horizontal, QObject::tr("Nombre"));
        //modelMun->setHeaderData(2, Qt::Horizontal, QObject::tr("Depto"));
        ui->tableViewMunicipie->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
        ui->tableViewMunicipie->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
        //ui->tableViewMunicipie->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
        QMessageBox::information(this, "Notificación", "Ahora puede ver los municipios del departamento de "+ui->name->text());
        conn->close();
    }
}

/********************MUNICIPIES***********************/

//Actions for btn add on municipies
void Departments::on_btnAddMun_clicked()
{
    ui->nameMun->setEnabled(true);
    ui->btnSaveMun->setEnabled(true);
    if(ui->name->text().isEmpty()){
        QMessageBox msgBox;
        msgBox.setText("Por favor, antes de continuar, seleccione un departamento");
        msgBox.exec();
        ui->nameMun->setDisabled(true);
        ui->btnSaveMun->setDisabled(true);
    }

    ui->btnEditMun->setDisabled(true);
    ui->btnDeleteMun->setDisabled(true);

    //ui->idMun->setEnabled(true);
    ui->idMun->clear();
    ui->nameMun->clear();
    action2 = 1;
}

//Actions for btn edit on municipies
void Departments::on_btnEditMun_clicked()
{
    //ui->idMun->setEnabled(true);
    ui->nameMun->setEnabled(true);
    ui->btnAddMun->setDisabled(true);
    ui->btnDeleteMun->setDisabled(true);
    ui->btnSaveMun->setEnabled(true);
    action2 = 2;
}

//Actions for btn delete on municipies
void Departments::on_btnDeleteMun_clicked()
{
    int id = ui->idMun->text().toInt();
    QString name = ui->nameMun->text();

    QMessageBox msgBox;
    msgBox.setText(tr("¿Realmente quiere eliminar este registro?"));
    QAbstractButton* pButtonYes = msgBox.addButton(tr("Eliminar"), QMessageBox::YesRole);
    msgBox.addButton(tr("Cancelar"), QMessageBox::NoRole);

    msgBox.exec();

    if (msgBox.clickedButton()==pButtonYes) {
        if(conn->open("eremasinprel")){

            qry.prepare("DELETE FROM municipies WHERE idMunicipio=:idMunicipio");
            qry.bindValue(":idMunicipio", id);
            qry.exec();

            //Recharge table municipies
            conn->open("eremasinprel");
            qry.prepare("select idMunicipio, nombre from municipies WHERE id=:id");
            qry.bindValue(":id", ui->id->text().toInt());
            qry.exec();

            modelMun->setQuery(qry);
            ui->tableViewMunicipie->setModel(modelMun);
            modelCol->clear();
            conn->close();

            ui->btnDeleteMun->setDisabled(true);
            ui->btnEditMun->setDisabled(true);
            ui->idMun->clear();
            ui->nameMun->clear();
            conn->close();
        }
    }
}

//Actions for btn save on municipies
void Departments::on_btnSaveMun_clicked()
{
    int id = ui->idMun->text().toInt();
    QString name = ui->nameMun->text();

    QMessageBox msgBox;
    msgBox.setText(tr("¿Desea realmente realizar esta acción?"));
    QAbstractButton* pButtonYes = msgBox.addButton(tr("Aceptar"), QMessageBox::YesRole);
    msgBox.addButton(tr("Cancelar"), QMessageBox::NoRole);

    msgBox.exec();

    if (msgBox.clickedButton()==pButtonYes) {
        //qDebug() << action;

        if(conn->open("eremasinprel")){
            switch (action2) {
            case 1:
                qry.prepare("INSERT INTO municipies(idMunicipio, nombre, id) VALUES(:idMunicipio, :name, :idDepto)");
                qry.bindValue(":id", id);
                qry.bindValue(":name", name);
                qry.bindValue(":idDepto", ui->id->text().toInt());
                qry.exec();

                //Recharge table municipies
                qry.prepare("select idMunicipio, nombre from municipies WHERE id = :id");
                qry.bindValue(":id", ui->id->text().toInt());
                qry.exec();
                modelMun->setQuery(qry);
                ui->tableViewMunicipie->setModel(modelMun);
                conn->close();
                break;
            case 2:
                qry.prepare("UPDATE municipies SET idMunicipio=:idMunicipio, nombre=:name WHERE idMunicipio=:idMunicipio");
                qry.bindValue(":idMunicipio", id);
                qry.bindValue(":name", name);
                qry.exec();

                //Recharge table municipies
                qry.prepare("select idMunicipio, nombre from municipies WHERE id = :id");
                qry.bindValue(":id", ui->id->text().toInt());
                qry.exec();
                modelMun->setQuery(qry);
                ui->tableViewMunicipie->setModel(modelMun);
                conn->close();
                break;

            }

            ui->idMun->clear();
            ui->nameMun->clear();
            ui->btnSaveMun->setDisabled(true);
        }
    }
    else{
        ui->btnSaveMun->setDisabled(true);
    }
    ui->btnAddMun->setEnabled(true);
    ui->btnEditMun->setDisabled(true);
    ui->idMun->setDisabled(true);
    ui->nameMun->setDisabled(true);
    //ui->btnDelete->setEnabled(true);
}

void Departments::on_tableViewMunicipie_clicked(const QModelIndex &index)
{
    ui->nameMun->setDisabled(true);
    ui->searchCol->setEnabled(true);
    ui->btnEdit->setDisabled(true);
    ui->btnDelete->setDisabled(true);

    ui->btnEditCol->setDisabled(true);
    ui->btnDeleteCol->setDisabled(true);

    ui->btnDeleteMun->setEnabled(true);
    ui->btnEditMun->setEnabled(true);
    QString valIndex = ui->tableViewMunicipie->model()->data(index).toString();

    if(conn->open("eremasinprel")){
        QSqlQuery qry2;
        QString stsm = "select * from municipies where idMunicipio = '"+ valIndex +"' or nombre = '"+ valIndex +"'";
        qry2.prepare(stsm);
        qry2.exec();

        while(qry2.next()){

            ui->idMun->setText(qry2.value(0).toString());
            ui->nameMun->setText(qry2.value(1).toString());

        }
        conn->close();

    }

    //db.open();
    //qry.prepare("select idColonia, nombre from neighborhood WHERE idMunicipio=?");
    //qry.bindValue(0, ui->idMun->text().toInt());
    //qry.exec();

    //modelCol->setQuery(qry);

    if(conn->open("eremasinprel")){
        qry.prepare("select idColonia, nombre from neighborhood WHERE idMunicipio=?");
        qry.bindValue(0, ui->idMun->text().toInt());
        qry.exec();
        modelCol->setQuery(qry);

        //Set table neighborhood
        ui->tableViewCol->setModel(modelCol);
        ui->tableViewCol->verticalHeader()->setVisible(false);


        modelCol->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
        modelCol->setHeaderData(1, Qt::Horizontal, QObject::tr("Nombre"));
        //modelCol->setHeaderData(2, Qt::Horizontal, QObject::tr("Mun"));
        ui->tableViewCol->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
        ui->tableViewCol->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
        //ui->tableViewCol->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);

        QMessageBox::information(this, "Notificación", "Ahora puede ver los barrios y colonias de "+ui->nameMun->text());
        conn->close();
    }
}

/********************NEIGHBORHOODS***********************/

//Actions for btn add on neighborhood
void Departments::on_btnAddCol_clicked()
{
    ui->nameCol->setEnabled(true);
    ui->btnSaveCol->setEnabled(true);
    if(ui->nameMun->text().isEmpty()){
        QMessageBox msgBox;
        msgBox.setText("Por favor, antes de continuar, seleccione un municipio");
        msgBox.exec();
        ui->nameCol->setDisabled(true);
        ui->btnSaveCol->setDisabled(true);
    }

    ui->btnEditCol->setDisabled(true);
    ui->btnDeleteCol->setDisabled(true);

    //ui->idCol->setEnabled(true);
    ui->idCol->clear();
    ui->nameCol->clear();
    action3 = 1;
}

//Actions for btn edit on neighborhood
void Departments::on_btnEditCol_clicked()
{
    //ui->idCol->setEnabled(true);
    ui->nameCol->setEnabled(true);
    ui->btnAddCol->setDisabled(true);
    ui->btnDeleteCol->setDisabled(true);
    ui->btnSaveCol->setEnabled(true);
    action3 = 2;
}

//Actions for btn add on neighborhood
void Departments::on_btnDeleteCol_clicked()
{
    int id = ui->idCol->text().toInt();
    QString name = ui->nameCol->text();

    QMessageBox msgBox;
    msgBox.setText(tr("¿Realmente quiere eliminar este registro?"));
    QAbstractButton* pButtonYes = msgBox.addButton(tr("Eliminar"), QMessageBox::YesRole);
    msgBox.addButton(tr("Cancelar"), QMessageBox::NoRole);

    msgBox.exec();

    if (msgBox.clickedButton()==pButtonYes) {
        if(conn->open("eremasinprel")){

            qry.prepare("DELETE FROM neighborhood WHERE idColonia=:idColonia");
            qry.bindValue(":idColonia", id);
            qry.exec();

            //Recharge table neighborhood
            conn->open("eremasinprel");
            qry.prepare("select idColonia, nombre from neighborhood WHERE idMunicipio=:idMunicipio");
            qry.bindValue(":idMunicipio", ui->idMun->text().toInt());
            qry.exec();

            modelCol->setQuery(qry);
            ui->tableViewCol->setModel(modelCol);
            conn->close();

            ui->btnDeleteCol->setDisabled(true);
            ui->btnEditCol->setDisabled(true);
            ui->idCol->clear();
            ui->nameCol->clear();

        }
    }
}

//Actions for btn save on neighborhood
void Departments::on_btnSaveCol_clicked()
{
    int id = ui->idCol->text().toInt();
    QString name = ui->nameCol->text();

    QMessageBox msgBox;
    msgBox.setText(tr("¿Desea realmente realizar esta acción?"));
    QAbstractButton* pButtonYes = msgBox.addButton(tr("Aceptar"), QMessageBox::YesRole);
    msgBox.addButton(tr("Cancelar"), QMessageBox::NoRole);

    msgBox.exec();

    if (msgBox.clickedButton()==pButtonYes) {
        //qDebug() << action;

        if(conn->open("eremasinprel")){
            switch (action3) {
            case 1:
                qry.prepare("INSERT INTO neighborhood(idColonia, nombre, idMunicipio) VALUES(:idColonia, :name, :idMun)");
                qry.bindValue(":id", id);
                qry.bindValue(":name", name);
                qry.bindValue(":idMun", ui->idMun->text().toInt());
                qry.exec();

                //Recharge table neighborhood
                qry.prepare("select idColonia, nombre from neighborhood WHERE idMunicipio=:idMunicipio");
                qry.bindValue(":idMunicipio", ui->idMun->text().toInt());
                qry.exec();
                modelCol->setQuery(qry);
                ui->tableViewCol->setModel(modelCol);
                conn->close();
                break;
            case 2:
                qry.prepare("UPDATE neighborhood SET idColonia=:idColonia, nombre=:name WHERE idColonia=:idColonia");
                qry.bindValue(":idColonia", id);
                qry.bindValue(":name", name);
                qry.exec();

                //Recharge table neighborhood
                qry.prepare("select idColonia, nombre from neighborhood WHERE idMunicipio=:idMunicipio");
                qry.bindValue(":idMunicipio", ui->idMun->text().toInt());
                qry.exec();
                modelCol->setQuery(qry);
                ui->tableViewCol->setModel(modelCol);
                conn->close();
                break;
            }

            ui->idCol->clear();
            ui->nameCol->clear();
            ui->btnSaveCol->setDisabled(true);
        }
    }
    else{
        ui->btnSaveCol->setDisabled(true);
    }
    ui->btnAddCol->setEnabled(true);
    ui->btnEditCol->setDisabled(true);
    ui->idCol->setDisabled(true);
    ui->nameCol->setDisabled(true);
    //ui->btnDelete->setEnabled(true);
}

void Departments::on_tableViewCol_clicked(const QModelIndex &index)
{
    ui->name->setDisabled(true);
    ui->nameCol->setDisabled(true);
    ui->nameMun->setDisabled(true);
    ui->nameCol->setDisabled(true);
    ui->nameMun->setDisabled(true);
    ui->btnEdit->setDisabled(true);
    ui->btnDelete->setDisabled(true);

    ui->btnEditMun->setDisabled(true);
    ui->btnDeleteMun->setDisabled(true);

    ui->btnDeleteCol->setEnabled(true);
    ui->btnEditCol->setEnabled(true);
    QString valIndex = ui->tableViewCol->model()->data(index).toString();

    if(conn->open("eremasinprel")){
        QSqlQuery qry2;
        QString stsm = "select * from neighborhood where idColonia = '"+ valIndex +"' or nombre = '"+ valIndex +"'";
        qry2.prepare(stsm);
        qry2.exec();

        while(qry2.next()){

            ui->idCol->setText(qry2.value(0).toString());
            ui->nameCol->setText(qry2.value(1).toString());

        }
        conn->close();
    }
}

void Departments::on_searchDepartment_textChanged(const QString &arg1)
{
    conn->open("eremasinprel");
    qrySearch.prepare("SELECT id, nombre FROM departments WHERE nombre LIKE '"+arg1+"%'");
    qrySearch.exec();
    qDebug() << arg1;

    model->setQuery(qrySearch);
    conn->close();
    ui->tableViewDepartments->setModel(model);
}

void Departments::on_searchMunicipie_textChanged(const QString &arg1)
{
    conn->open("eremasinprel");
    QString idepto = ui->id->text();
    QString stmt = "SELECT idMunicipio, nombre FROM municipies WHERE id = '"+idepto+"'" + " AND nombre LIKE '"+arg1+"%'";
    qDebug() << stmt;
    qrySearch.prepare(stmt);
    qrySearch.exec();
    qDebug() << arg1;

    modelMun->setQuery(qrySearch);
    conn->close();
    ui->tableViewMunicipie->setModel(modelMun);
}

void Departments::on_searchCol_textChanged(const QString &arg1)
{
    conn->open("eremasinprel");
    QString idMun = ui->idMun->text();
    QString stmt = "SELECT idColonia, nombre FROM neighborhood WHERE idMunicipio = '"+idMun+"'" + " AND nombre LIKE '"+arg1+"%'";
    qDebug() << stmt;
    qrySearch.prepare(stmt);
    qrySearch.exec();
    qDebug() << arg1;

    modelCol->setQuery(qrySearch);
    conn->close();
    ui->tableViewCol->setModel(modelCol);
}
