#ifndef CHANGEPASSWORDWINDOW_H
#define CHANGEPASSWORDWINDOW_H

#include <QWidget>
#include <QMessageBox>

#include "common/setting.h"
#include "db/userdb.h"

namespace Ui {
class ChangePasswordWindow;
}

class ChangePasswordWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ChangePasswordWindow(QWidget *parent = nullptr);
    ~ChangePasswordWindow();

private slots:
    void on_btnChangePass_clicked();

private:
    Ui::ChangePasswordWindow *ui;
};

#endif // CHANGEPASSWORDWINDOW_H
