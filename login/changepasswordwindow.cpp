#include "changepasswordwindow.h"
#include "ui_changepasswordwindow.h"

ChangePasswordWindow::ChangePasswordWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChangePasswordWindow)
{
    ui->setupUi(this);
    this->setWindowModality(Qt::WindowModality(true));
}

ChangePasswordWindow::~ChangePasswordWindow()
{
    delete ui;
}

void ChangePasswordWindow::on_btnChangePass_clicked()
{
    UserDB *userDB = new UserDB();

    if (ui->txtNewPassword->text().isEmpty()) {
        QMessageBox::warning(this, "Compruebe Contraseña", "¡La contraseña no puede ser vacío!");
    }

    else {
        if(ui->txtNewPassword2->text().isEmpty()) {
            QMessageBox::warning(this, "Compruebe Contraseña", "¡Favor digite la contraseña de comprobación!");
        }

        else {
            if(!ui->txtNewPassword->text().compare(ui->txtNewPassword2->text())) {
                Setting *setting = new Setting ();
                userDB->changeUserPassword(setting->getAppUser(), ui->txtNewPassword->text());
                this->close();
            }
            else
                QMessageBox::warning(this, "Compruebe Contraseña", "¡Las contraseñas deben ser iguales!");
        }


    }
}
