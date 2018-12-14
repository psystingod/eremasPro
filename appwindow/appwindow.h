#ifndef APPWINDOW_H
#define APPWINDOW_H

#include <QWidget>
#include <QSplitter>
#include <QTreeWidgetItem>
#include <QTreeWidget>
#include <QUiLoader>
#include <QFile>
#include "common/paths.h"
#include "common/setting.h"
#include "mainwindow/systemusers.h"
#include "mainwindow/systeminventoryparameters.h"
#include "mainwindow/inventory.h"
#include "mainwindow/catalogofaccounts.h"
#include "mainwindow/productbilling.h"
#include "mainwindow/salerequest.h"
#include "mainwindow/customers.h"
#include "mainwindow/proveedores.h"
#include "mainwindow/departments.h"

namespace Ui {
class AppWindow;
}

class AppWindow : public QWidget
{
    Q_OBJECT

public:
    explicit AppWindow(QWidget *parent = nullptr);
    ~AppWindow();

private slots:
    void on_btnShowMenu_clicked();

    void on_treeWidget_itemClicked(QTreeWidgetItem *item);

private:
    Ui::AppWindow *ui;
    void showAppWindow( );
    void setUsername();
    void loadTreeViewMenu ( );
    void addTreeViewRoot (QString name, int index);
    void addTreeViewChild (QTreeWidgetItem *parent, QString name );
    void createWidget();
};

#endif // APPWINDOW_H
