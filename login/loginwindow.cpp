#include "loginwindow.h"
#include "login/changepasswordwindow.h"
#include "appwindow/appwindow.h"
#include "ui_loginwindow.h"
#include "ui_userfieldempty.h"
#include "ui_changedbparameters.h"
#include "dialogs/userfieldempty.h"
#include "db/userdb.h"


static QWidget* myparent;

LoginWindow::LoginWindow(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::LoginWindow)
{
    myparent = parent;
    ui->setupUi(this);
    availableDB = new AvailableDB();
    setLogo();
    setTableCompanies();
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::setLogo()
{
    path = new Paths();
    ui->lblImage->setScaledContents(true);
    ui->lblImage->setPixmap(QPixmap(path->getLockImagePath()));
    ui->groupBox->setStyleSheet("font-weight: 100; color: #484848;");
}

void LoginWindow::verifyFields()
{
    if(ui->txtUser->text().isEmpty()) {
        QMessageBox::information(this, "Meesage test", "¡Por favor ingrese un usuario!");
    }
    else {
        if(ui->txtPassword->text().isEmpty()) {
            QMessageBox::information(this, "Meesage test", "¡Por favor ingrese una contraseña!");
        }

        else {
            if ( ui->tableView->selectionModel()->hasSelection() ) {

                UserDB *userdb = new UserDB();
                Setting *setting = new Setting();
                setting->setAppUser(ui->txtUser->text());
                setting->setDatabasename("eremas" + ui->tableView->currentIndex().data().toString());

                if ( userdb->checkUserExists(ui->txtUser->text(), ui->txtPassword->text())) {
                    userdb->setUserLastDate(ui->txtUser->text());

                    openMainWindow();
                }

                else {
                    QMessageBox::information( this, "Datos incorrectos", "Ingrese usuario y contaseña válidos.");
                }
            }
            else QMessageBox::information(this, "Meesage test", "¡Debe seleccionar una empresa!");
        }

    }
}

void LoginWindow::on_pushButton_clicked()
{
    verifyFields();
}

void LoginWindow::setTextSlot(const QString &text) {
    ui->label->setText(text);
}

void LoginWindow::setTableCompanies() {

    list = availableDB->allDB();
    int countRows = list.size();

    QStandardItemModel *model = new QStandardItemModel(countRows, 1, this);
    ui->tableView->setModel(model);
    ui->tableView->horizontalHeader()->hide();
    ui->tableView->verticalHeader()->setVisible(false);
    ui->tableView->verticalHeader()->setDefaultSectionSize(20);
    ui->tableView->setShowGrid(false);

    for (int row = 0; row < countRows; row++) {
        QModelIndex index = model->index(row, DATABASE, QModelIndex());
        ui->tableView->setColumnWidth(DATABASE, 140);
        QString data = list.at(row).databasename;
        model->setData(index, data.remove(0,6));
    }

    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
}

void LoginWindow::openMainWindow () {

    if ( !passwordAlredyChanged(ui->txtUser->text()) )
        changePassword();

   else
        myparent->close();

    while ( QWidget* w = findChild<QWidget*>() )
        delete w;

    AppWindow *appWindow = new AppWindow();
    QTimer::singleShot(10, appWindow, SLOT(showMaximized()));
    appWindow->show();

}

void LoginWindow::changePassword() {

    //myparent->close();
    ChangePasswordWindow *c = new ChangePasswordWindow();
    c->show();
    myparent->close();
}

bool LoginWindow::passwordAlredyChanged(const QString &username) {
    bool returnedVal = false;
    UserDB *userDB = new UserDB();

    if (userDB->passwordAlredyChanged(username)) {
        returnedVal = true;
    }
    return returnedVal;
}

void LoginWindow::checkSettingFile () {

}
