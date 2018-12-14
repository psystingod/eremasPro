#ifndef USERDB_H
#define USERDB_H

#include <QString>
#include <QDate>

class UserDB
{

public:
    UserDB( );
    UserDB( const QString&, const QString&, const QString&, const QString&, const bool&, const QDate& );

    QString name, user, password, department;
    bool accesed;
    QDate lastdate;


    QString getName();
    void setName( const QString& );
    QString getUser();
    void setUser( const QString& );
    QString getPassword();
    void setPassword( const QString& );
    QString getDepartment();
    void setDeparment( const QString& );
    bool getAccesed();
    void setAccesed( const bool& );
    QDate getLastDate();
    void setLastDate( const QDate& );

    bool changeUserPassword (const QString&, const QString& );
    bool passwordAlredyChanged ( const QString& );
    bool checkUserExists( const QString&, const QString& );
    QList<UserDB> allUsers();
    void setUserLastDate ( const QString& );
    void deleteUser( const QString& );
    QList<UserDB> updateUserView ( const QString& );

};

#endif // USERDB_H
