#include "mysqlconnection.h"

using namespace std;
static QSqlDatabase db;

MysqlConnection::MysqlConnection()
{

}

bool MysqlConnection::open(QString dataBasename)
{

    if ( dataBasename.isEmpty() ) {
        Setting *setting = new Setting();
        QString hostname, username, password;
        int port = 0;

        hostname = setting->getHost();
        port = setting->getPort().toInt();
        username = setting->getUser();
        password = setting->getPassword();

        db = QSqlDatabase::addDatabase("QMYSQL");
        db.setHostName(hostname);
        db.setPort(port);
        db.setUserName(username);
        db.setPassword(password);
        db.setDatabaseName("");
    }
    else {
        db.setDatabaseName(dataBasename);
    }

    if(!db.open())
    {
        qDebug()<<("Failed to open Database");
        return false;
    }

    else
    {
        qDebug()<<("Connected.....");
        return true;
    }
}

void MysqlConnection::close()
{
    QString databaseName;
    databaseName = db.databaseName();
    db.removeDatabase(databaseName);
    db.close();
    qDebug()<<("Disc.....");
}
