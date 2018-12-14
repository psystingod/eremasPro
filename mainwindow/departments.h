#ifndef DEPARTMENTS_H
#define DEPARTMENTS_H

#include <QWidget>
#include <QMainWindow>
#include <QtSql>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QAbstractItemView>
#include <QRegularExpression>
#include "dbconnection/mysqlconnection.h"

namespace Ui {
class Departments;
}

class Departments : public QWidget
{
    Q_OBJECT

public:
    explicit Departments(QWidget *parent = nullptr);
    ~Departments();

    MysqlConnection *conn = new MysqlConnection();
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQueryModel *modelMun = new QSqlQueryModel();
    QSqlQueryModel *modelCol = new QSqlQueryModel();
    QSqlQueryModel *searchDepartment = new QSqlQueryModel();
    QSqlQueryModel *searchMun = new QSqlQueryModel();
    QSqlQuery qry;
    QSqlQuery qrySearch;
    QStringListModel *departmentsList = new QStringListModel();

private slots:
    void on_btnAdd_clicked();

    void on_btnEdit_clicked();

    void on_btnDelete_clicked();

    void on_btnSave_clicked();

    void on_tableViewDepartments_clicked(const QModelIndex &index);

    void on_btnAddMun_clicked();

    void on_btnEditMun_clicked();

    void on_btnDeleteMun_clicked();

    void on_btnSaveMun_clicked();

    void on_tableViewMunicipie_clicked(const QModelIndex &index);

    void on_btnAddCol_clicked();

    void on_btnEditCol_clicked();

    void on_btnDeleteCol_clicked();

    void on_btnSaveCol_clicked();

    void on_tableViewCol_clicked(const QModelIndex &index);

    void on_searchDepartment_textChanged(const QString &arg1);

    void on_searchMunicipie_textChanged(const QString &arg1);

    void on_searchCol_textChanged(const QString &arg1);

private:
    Ui::Departments *ui;
};

#endif // DEPARTMENTS_H
