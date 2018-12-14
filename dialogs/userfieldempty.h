#ifndef USERFIELDEMPTY_H
#define USERFIELDEMPTY_H

#include <QDialog>

namespace Ui {
class UserFieldEmpty;
}

class UserFieldEmpty : public QDialog
{
    Q_OBJECT
signals:
 void setTextSignal(QString text);

public:
    explicit UserFieldEmpty(QWidget *parent = nullptr);
    ~UserFieldEmpty();

private slots:
    void on_pushButton_clicked();

private:
    Ui::UserFieldEmpty *ui;
};

#endif // USERFIELDEMPTY_H
