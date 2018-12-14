#include "changedbparameters.h"
#include "ui_changedbparameters.h"

static QWidget *myparent = nullptr;
ChangeDBParameters::ChangeDBParameters(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChangeDBParameters)
{
    ui->setupUi(this);
    myparent = parent;
    loadParameters();
}

ChangeDBParameters::~ChangeDBParameters()
{
    delete ui;
}

void ChangeDBParameters::on_pushButton_clicked()
{
    Setting *setting = new Setting();
    setting->setParameters(ui->txtServer->text(), ui->txtPort->text(), ui->txtUser->text(), ui->txtPassword->text());

    while ( QWidget* w = findChild<QWidget*>() )
        delete w;

    LoginWindow* loginWindow = new LoginWindow(myparent);
    loginWindow->show();
    //this->close();
}

void ChangeDBParameters::loadParameters()
{
    Setting *setting = new Setting();
    ui->txtServer->setText(setting->getHost());
    ui->txtPort->setText(setting->getPort());
    ui->txtUser->setText(setting->getUser());
    ui->txtPassword->setText(setting->getPassword());
}
