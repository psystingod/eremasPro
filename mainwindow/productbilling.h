#ifndef PRODUCTBILLING_H
#define PRODUCTBILLING_H

#include <QWidget>

namespace Ui {
  class ProductBilling;
}

class ProductBilling : public QWidget
{
  Q_OBJECT

public:
  explicit ProductBilling(QWidget *parent = nullptr);
  ~ProductBilling();

private:
  Ui::ProductBilling *ui;
};

#endif // PRODUCTBILLING_H
