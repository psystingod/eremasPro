#ifndef SYSTEMPARAMETERS_H
#define SYSTEMPARAMETERS_H

#include <QWidget>
#include <QStandardItemModel>
#include <QMessageBox>

#include "db/unitsdb.h"
#include "db/warehousedb.h"
#include "db/productfamilydb.h"

namespace Ui {
class SystemInventoryParameters;
}

class SystemInventoryParameters : public QWidget
{
    Q_OBJECT

public:
    explicit SystemInventoryParameters(QWidget *parent = nullptr);
    ~SystemInventoryParameters();

private slots:
    void on_btnNewUnit_clicked();
    void on_btnNewWareHouse_clicked();
    void on_btnNewProductFamily_clicked();
    void on_txtSearchUnit_textEdited(const QString&);
    void on_txtSearchWarehouse_textEdited(const QString&);
    void on_txtSearchFamily_textEdited(const QString&);

private:
    Ui::SystemInventoryParameters *ui;
    void setTableUnits ( const QString& );
    void setTableWarehouses ( const QString& );
    void setTableProductFamily ( const QString& );
    void resizeEvent ( QResizeEvent* );

    enum units {
        UNITSNAME, UNIT
    };

    enum warehouse {
        WAREHOUSENAME, WAREHOUSECODE, ADDRESS
    };

    enum productfamily {
        FAMILYNAME, FAMILYABBREVIATED, FAMILYCODE
    };
};

#endif // SYSTEMPARAMETERS_H
