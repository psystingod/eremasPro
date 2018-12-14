#include "mysqluserdb.h"
#include "dbconnection/mysqlconnection.h"

MysqlUserDB::MysqlUserDB ()
{

}

bool MysqlUserDB::checkUserExists ( const QString &user, const QString &password ) {

    MysqlConnection* conn = new MysqlConnection();
    bool returnedValue = false;
    Setting *setting = new Setting();

    if ( conn->open(setting->getDatabasename()) ) {

        QSqlQuery query;
        query.prepare( "SELECT COUNT(*) AS result FROM system_users WHERE username = ? AND password = ? GROUP BY id" );

        query.bindValue( 0, user );
        query.bindValue( 1, getShaPassword(password) );
        query.exec( );

        int counter = 0;
        while ( query.next()) {
            counter = query.value(0).toInt();
        }

        if (counter == 1) {
            returnedValue = true;
        }

        query.finish();
        query.clear();
        conn->close();
    }
    return returnedValue;
}

bool MysqlUserDB::changeUserPassword (const QString &username, const QString &newPassword ) {
    MysqlConnection* conn = new MysqlConnection();
    bool returnedValue = false;
    Setting *setting = new Setting ();

    if ( conn->open( setting->getDatabasename() ) ) {
        QSqlQuery query;
        query.prepare( "UPDATE system_users SET password = ?, accesed = ? WHERE username = ?" );

        query.bindValue( 0, getShaPassword(newPassword) );
        query.bindValue( 1, 1 );
        query.bindValue( 2,  username);
        query.exec( );
        query.finish();
        query.clear();
        conn->close();

        returnedValue = true;
    }
    return returnedValue;
}

bool MysqlUserDB::passwordAlredyChanged ( const QString &username ) {
    MysqlConnection* conn = new MysqlConnection();
    bool returnedValue = true;
    Setting *setting = new Setting ();

    if ( conn->open( setting->getDatabasename() ) ) {
        QSqlQuery query;
        query.prepare( "SELECT COUNT(*) AS result FROM system_users WHERE username = ? AND accesed = 0" );
        query.bindValue( 0, username );
        query.exec( );

        int counter = 0;

        while ( query.next() ) {
            counter = query.value(0).toInt();
        }

        if (counter)
            returnedValue = false;
        query.finish();
        query.clear();
        conn->close();
    }
    return returnedValue;
}

QString MysqlUserDB::getShaPassword (const QString &password) {
    QByteArray hash = QCryptographicHash::hash( password.toUtf8(), QCryptographicHash::Sha256 );
    QString passwordNew = QString( hash.toHex() );

    return passwordNew;
}

QList<UserDB> MysqlUserDB::allUsers() {
    MysqlConnection* conn = new MysqlConnection();
    Setting *setting = new Setting ();
    QList<UserDB> list;
    QSqlQuery query;

    if ( conn->open( setting->getDatabasename() ) ) {
        query.prepare("SELECT * FROM system_users");
        query.exec();

        UserDB userDB;
        while (query.next()) {
            QString name = query.value(query.record().indexOf("name")).toString();
            QString user = query.value(query.record().indexOf("username")).toString();
            QString password = query.value(query.record().indexOf("password")).toString();
            QString department = query.value(query.record().indexOf("department")).toString();
            bool accesed = query.value(query.record().indexOf("accesed")).toBool();
            QDate lastdate = query.value(query.record().indexOf("lastdate")).toDate();

            userDB.setName(name);
            userDB.setUser(user);
            userDB.setPassword(password);
            userDB.setDeparment(department);
            userDB.setAccesed(accesed);
            userDB.setLastDate(lastdate);

            list.append(userDB);
        }
        query.finish();
        query.clear();
        conn->close();
    }
    return list;
}

void MysqlUserDB::setUserLastDate(const QString &username) {
    MysqlConnection* conn = new MysqlConnection();
    Setting *setting = new Setting ();
    QSqlQuery query;

    if ( conn->open( setting->getDatabasename() ) ) {
        query.prepare("UPDATE system_users set lastdate = ? WHERE username = ?");
        query.bindValue( 0, QDate::currentDate());
        query.bindValue( 1, username );
        query.exec();

        query.finish();
        query.clear();
        conn->close();
    }
}

void MysqlUserDB::deleteUser(const QString &username) {
    MysqlConnection* conn = new MysqlConnection();
    Setting *setting = new Setting ();
    QSqlQuery query;

    if ( conn->open( setting->getDatabasename() ) ) {
        query.prepare("DELETE FROM system_users WHERE username = ?");
        query.bindValue( 0, username );
        query.exec();

        query.finish();
        query.clear();
        conn->close();
    }
}

QList<UserDB> MysqlUserDB::updateUserView (const QString &username) {
    MysqlConnection* conn = new MysqlConnection();
    Setting *setting = new Setting ();
    QSqlQuery query;
    QList<UserDB> list;

    UserDB userDB;
    if ( conn->open( setting->getDatabasename() ) ) {
        query.prepare("SELECT * FROM system_users WHERE username = ?");
        query.bindValue( 0, username );
        query.exec();

        while (query.next()) {
            QString name = query.value(query.record().indexOf("name")).toString();
            QString user = query.value(query.record().indexOf("username")).toString();
            QString password = query.value(query.record().indexOf("password")).toString();
            QString department = query.value(query.record().indexOf("department")).toString();
            bool accesed = query.value(query.record().indexOf("accesed")).toBool();
            QDate lastdate = query.value(query.record().indexOf("lastdate")).toDate();

            userDB.setName(name);
            userDB.setUser(user);
            userDB.setPassword(password);
            userDB.setDeparment(department);
            userDB.setAccesed(accesed);
            userDB.setLastDate(lastdate);

            list.append(userDB);
        }

        query.finish();
        query.clear();
        conn->close();
    }
    return list;
}
