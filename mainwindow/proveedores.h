#ifndef PROVEEDORES_H
#define PROVEEDORES_H

#include <QWidget>
#include <QSqlQuery>
#include <QtSql>
#include <QSqlDatabase>
#include <QMessageBox>
#include "dbconnection/mysqlconnection.h"

namespace Ui {
class Proveedores;
}

class Proveedores : public QWidget
{
    Q_OBJECT

public:
    explicit Proveedores(QWidget *parent = nullptr);
    ~Proveedores();
    // Setting variable for get index of tableViewProviders
    QString index_value = "";
    int action = 0;
    // Setting variables

    MysqlConnection *conn = new MysqlConnection();
    QSqlQueryModel *modelProviders = new QSqlQueryModel();
    QSqlQuery query;
    QSqlQuery searchQuery;

private slots:
    void on_btn_new_clicked();

    void on_btn_edit_clicked();

    void on_btn_save_clicked();

    void on_tableViewProviders_clicked(const QModelIndex &index);

    void on_lineEdit_textChanged(const QString &arg1);

private:
    Ui::Proveedores *ui;
};

#endif // PROVEEDORES_H
