#ifndef MYSQLUSERDB_H
#define MYSQLUSERDB_H

#include <QList>
#include <QCryptographicHash>
#include <QByteArray>
#include <QtSql>

#include "db/userdb.h"

class MysqlUserDB
{

public:
    MysqlUserDB();
    QList<UserDB> allUsers();
    bool checkUserExists (const QString&, const QString& );
    bool changeUserPassword ( const QString&, const QString& );
    bool passwordAlredyChanged ( const QString&);
    void setUserLastDate( const QString& );
    void deleteUser ( const QString& );
    QList<UserDB> updateUserView ( const QString& );

private:
    QString getShaPassword (const QString&);

    ~MysqlUserDB();
};

#endif //MYSQLUSERDB_H
