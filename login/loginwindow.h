#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>
#include <QtDebug>
#include <QMessageBox>
#include <QTableView>
#include <QStandardItemModel>
#include <QStyle>
#include <QDesktopWidget>
#include "dbinteraction/mysqlavailabledb.h"
#include "common/paths.h"
#include "common/setting.h"

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

public slots:
    void setTextSlot(const QString &text);

private slots:
    void on_pushButton_clicked();

private:
    Ui::LoginWindow *ui;
    enum Colum {
        DATABASE
    };

    void checkSettingFile();
    void setLogo ();
    void verifyFields ();
    void setTableCompanies ();
    void openMainWindow ();
    void changePassword ( );
    bool passwordAlredyChanged( const QString& );
    QList<AvailableDB> list;
    AvailableDB *availableDB;
    Paths *path;
    Setting *setting;
};

#endif // LOGINWINDOW_H
