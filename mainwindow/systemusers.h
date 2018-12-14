#ifndef SYSTEMUSERS_H
#define SYSTEMUSERS_H

#include "db/userdb.h"

#include <QWidget>
#include <QTableView>
#include <QStandardItemModel>
#include <QMessageBox>

namespace Ui {
class SystemUsers;
}

class SystemUsers : public QWidget
{
    Q_OBJECT

public:
    explicit SystemUsers(QWidget *parent = nullptr);
    ~SystemUsers();

private slots:


    void on_btnDeleteUser_clicked();

    void on_btnAddUser_clicked();

    void on_btnUpdateUser_clicked();

    void on_tableUsers_clicked( const QModelIndex& );

private:
    Ui::SystemUsers *ui;
    enum Column {
        NAME, USER, DEPARTMENT, LASTDATE
    };

    void setGroupBoxBorder();
    void setTableUsers();
};

#endif // SYSTEMUSERS_H
