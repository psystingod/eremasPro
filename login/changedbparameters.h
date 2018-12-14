#ifndef CHANGEDBPARAMETERS_H
#define CHANGEDBPARAMETERS_H

#include <QWidget>
#include "common/setting.h"
#include "login/loginwindow.h"

namespace Ui {
class ChangeDBParameters;
}

class ChangeDBParameters : public QWidget
{
    Q_OBJECT

public:
    explicit ChangeDBParameters(QWidget *parent = nullptr);

    void setDBParameters (const QString&, const QString&, const QString&, const QString&);
    void loadParameters ();

    ~ChangeDBParameters();

private slots:
    void on_pushButton_clicked();

private:
    Ui::ChangeDBParameters *ui;
};

#endif // CHANGEDBPARAMETERS_H
