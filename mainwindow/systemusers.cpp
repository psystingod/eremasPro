#include "systemusers.h"
#include "ui_systemusers.h"
#include "db/userdb.h"
#include <QtDebug>

SystemUsers::SystemUsers(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SystemUsers)
{
    ui->setupUi(this);
    setGroupBoxBorder();
    setTableUsers();
}

SystemUsers::~SystemUsers()
{
    delete ui;
}

void SystemUsers::setGroupBoxBorder() {
    ui->groupBoxNewUser->setStyleSheet( "QGroupBox { border: 1px solid #bababa; border-radius: 3px; }");
}

void SystemUsers::setTableUsers() {

    UserDB *userDB = new UserDB();
    QList<UserDB> list = userDB->allUsers();

    int countRows = list.size();

    QStandardItemModel *model = new QStandardItemModel(countRows, 3, this);
    model->setHorizontalHeaderLabels({ "Nombre", "Usuario", "Area Empresa", "Fecha de Uso"});

    ui->tableUsers->setModel(model);
    ui->tableUsers->verticalHeader()->setVisible(false);
    ui->tableUsers->setShowGrid(false);
    ui->tableUsers->verticalHeader()->setDefaultSectionSize(18);
    //ui->tableUsers->setAlternatingRowColors(true);
    //ui->tableUsers->setStyleSheet("QHeaderView::section { background-color: #e0e0e0; border: 1px solid #fffff8; }");
    //ui->tableUsers->setStyleSheet("alternate-background-color: #e3f2fd; background-color: white; ");

    ui->tableUsers->horizontalHeader()->setSectionResizeMode(NAME, QHeaderView::Stretch);
    ui->tableUsers->horizontalHeader()->setSectionResizeMode(USER, QHeaderView::Stretch);
    ui->tableUsers->horizontalHeader()->setSectionResizeMode(DEPARTMENT, QHeaderView::Stretch);
    ui->tableUsers->horizontalHeader()->setSectionResizeMode(LASTDATE, QHeaderView::Stretch);

    for (int row = 0; row < countRows; row++) {
        model->setData(model->index(row, NAME, QModelIndex()), list.at(row).name);
        model->setData(model->index(row, USER, QModelIndex()), list.at(row).user);
        model->setData(model->index(row, DEPARTMENT, QModelIndex()), list.at(row).department);
        model->setData(model->index(row, LASTDATE, QModelIndex()), list.at(row).lastdate.toString("dd/MM/yyyy"));
    }
    ui->tableUsers->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //ui->tableUsers->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableUsers->setSelectionBehavior(QAbstractItemView::SelectRows);
}

void SystemUsers::on_btnDeleteUser_clicked()
{
    if ( ui->tableUsers->selectionModel()->hasSelection() ) {
        UserDB *userDB = new UserDB();
        QItemSelectionModel *index = ui->tableUsers->selectionModel();

       userDB->deleteUser(ui->tableUsers->model()->data(index->currentIndex().model()->index(index->currentIndex().row(),1)).toString());
       setTableUsers();
    }

    else QMessageBox::information(this, "Eliminar Usuario", "¡Debe seleccionar un usuario de la tabla!");
}

void SystemUsers::on_btnAddUser_clicked()
{

}

void SystemUsers::on_btnUpdateUser_clicked()
{
    if ( ui->tableUsers->selectionModel()->hasSelection() ) {

    }

    else QMessageBox::information(this, "Eliminar Usuario", "¡Debe seleccionar un usuario de la tabla!");
}

void SystemUsers::on_tableUsers_clicked(const QModelIndex &index)
{
    UserDB *userDB = new UserDB();
    //qDebug() << ui->tableUsers->model()->data(index.model()->index(index.row(), 1)).toString();

    QList<UserDB> list = userDB->updateUserView(ui->tableUsers->model()->data(index.model()->index(index.row(), 1)).toString());
    ui->txtName->setText(list.at(0).name);
    ui->txtUsername->setText(list.at(0).user);
    ui->txtPassword->setText(list.at(0).password);
    ui->txtConfirmPass->setText(list.at(0).password);
    qDebug() << list.at(0).department;
    ui->companyDeparment->setCurrentText(list.at(0).department);
}
