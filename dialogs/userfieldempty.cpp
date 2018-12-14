#include "userfieldempty.h"
#include "ui_userfieldempty.h"

UserFieldEmpty::UserFieldEmpty(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserFieldEmpty)
{
    ui->setupUi(this);
}

UserFieldEmpty::~UserFieldEmpty()
{
    delete ui;
}

void UserFieldEmpty::on_pushButton_clicked()
{
    emit setTextSignal("HOLA");
}
