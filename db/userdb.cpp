#include "userdb.h"
#include "dbinteraction/mysqluserdb.h"

UserDB::UserDB ()
{
    name = "";
    user = "";
    password = "";
    department = "";
    accesed = false;
    lastdate = QDate::currentDate();
}

UserDB::UserDB( const QString &nameLocal, const QString &userLocal, const QString &passwordLocal, const QString &departmentLocal, const bool &accesedLocal, const QDate &lastdateLocal ) {
    name = nameLocal;
    user = userLocal;
    password = passwordLocal;
    department = departmentLocal;
    accesed = accesedLocal;
    lastdate = lastdateLocal;
}

QString UserDB::getName( ) {
    return name;
}

void UserDB::setName( const QString &nameLocal ) {
    name = nameLocal;
}

QString UserDB::getUser( ) {
    return user;
}

void UserDB::setUser( const QString &userLocal ) {
    user = userLocal;
}

QString UserDB::getPassword ( )  {
    return password;
}

void UserDB::setPassword ( const QString &passwordLocal ) {
    password = passwordLocal;
}

QString UserDB::getDepartment ( )  {
    return department;
}

void UserDB::setDeparment( const QString &departmentLocal ) {
    department = departmentLocal;
}

bool UserDB::getAccesed ( )  {
    return accesed;
}

void UserDB::setAccesed( const bool &accesedLocal ) {
    accesed = accesedLocal;
}

QDate UserDB::getLastDate ( )  {
    return lastdate;
}

void UserDB::setLastDate( const QDate &lastdateLocal ) {
    lastdate = lastdateLocal;
}


bool UserDB::checkUserExists(const QString &username, const QString &password) {

    MysqlUserDB *mysqlUserDB = new MysqlUserDB();
    bool returnedValue = false;

    if ( mysqlUserDB->checkUserExists(username, password) )
        returnedValue = true;

    return returnedValue;
}

bool UserDB::changeUserPassword (const QString &username, const QString &password) {
    MysqlUserDB *mysqlUserDB = new MysqlUserDB();
    bool returnedValue = false;

    if ( mysqlUserDB->changeUserPassword( username, password )) {
        returnedValue = true;
    }
    return returnedValue;
}

bool UserDB::passwordAlredyChanged ( const QString &username) {
    MysqlUserDB *mysqlUserDB = new MysqlUserDB();
    bool returnedValue = false;

    if ( mysqlUserDB->passwordAlredyChanged( username )) {
        returnedValue = true;
    }
    return returnedValue;
}

QList<UserDB> UserDB::allUsers () {
    MysqlUserDB *mysqlUserDB = new MysqlUserDB();
   return mysqlUserDB->allUsers();
}

void UserDB::setUserLastDate (const QString &username) {
    MysqlUserDB *mysqlUserDB = new MysqlUserDB();
    mysqlUserDB->setUserLastDate(username);
}

void UserDB::deleteUser (const QString &username) {
    MysqlUserDB *mysqlUserDB = new MysqlUserDB();
    mysqlUserDB->deleteUser(username);
}

QList<UserDB> UserDB::updateUserView (const QString &username) {
    MysqlUserDB *mysqlUserDB = new MysqlUserDB();
    return mysqlUserDB->updateUserView(username);
}

