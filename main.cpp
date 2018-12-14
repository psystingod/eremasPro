#include "login/loginwindow.h"
#include "login/changedbparameters.h"
#include "common/setting.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QGuiApplication::setAttribute(Qt::AA_ShareOpenGLContexts);
    QApplication a(argc, argv);

    Setting *setting = new Setting();

    QWidget *widget = new QWidget();
    widget->setFixedSize(350, 200);

    LoginWindow* loginWindow = new LoginWindow(widget);
    ChangeDBParameters* parametersWindow = new ChangeDBParameters();

    if(setting->getDatabasename().isEmpty() && setting->getHost().isEmpty() && setting->getPassword().isEmpty()) {
        loginWindow->close();
        //delete setting;
        parametersWindow->setParent(widget);
    }

    widget->show();

    return a.exec();
}
