#include "productbilling.h"
#include "ui_productbilling.h"

ProductBilling::ProductBilling(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::ProductBilling)
{
  ui->setupUi(this);
}

ProductBilling::~ProductBilling()
{
  delete ui;
}
