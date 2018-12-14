#include "setting.h"

Setting::Setting()
{

}

void Setting::setDatabasename(const QString &databaseName ){
    path = new Paths();
    QSettings settings( path->getSettingFilePath(), QSettings::IniFormat );
    settings.beginGroup("SystemSettings");
    settings.setValue("DatabaseName", databaseName);
}

QString Setting::getDatabasename( ) {
    path = new Paths();
    QString m_strWorkingPath = path->getSettingFilePath(), databasename;
    QSettings settings( m_strWorkingPath, QSettings::IniFormat );
    settings.beginGroup("SystemSettings");
    databasename = settings.value("DatabaseName").toString();

    return databasename;
}

void Setting::setHost (const QString &host ){
    path = new Paths ();
    QSettings settings ( path->getSettingFilePath(), QSettings::IniFormat );
    settings.beginGroup ("SystemSettings");
    settings.setValue ("Hostname", host);
}

QString Setting::getHost ( ) {
    path = new Paths();
    QString m_strWorkingPath = path->getSettingFilePath(), host;
    QSettings settings( m_strWorkingPath, QSettings::IniFormat );
    settings.beginGroup("SystemSettings");
    host = settings.value("Hostname").toString();

    return host;
}

void Setting::setPort (const QString &port ){
    path = new Paths ();
    QSettings settings ( path->getSettingFilePath(), QSettings::IniFormat );
    settings.beginGroup ("SystemSettings");
    settings.setValue ("Port", port);
}

QString Setting::getPort ( ) {
    path = new Paths();
    QString m_strWorkingPath = path->getSettingFilePath(), port;
    QSettings settings( m_strWorkingPath, QSettings::IniFormat );
    settings.beginGroup("SystemSettings");
    port = settings.value("Port").toString();

    return port;
}

void Setting::setUser (const QString &user ){
    path = new Paths();
    QSettings settings( path->getSettingFilePath(), QSettings::IniFormat );
    settings.beginGroup("SystemSettings");
    settings.setValue("Username", user);
}

QString Setting::getUser( ) {
    path = new Paths();
    QString m_strWorkingPath = path->getSettingFilePath(), user;
    QSettings settings( m_strWorkingPath, QSettings::IniFormat );
    settings.beginGroup("SystemSettings");
    user = settings.value("Username").toString();

    return user;
}

void Setting::setPassword(const QString &password ){
    path = new Paths();
    QSettings settings( path->getSettingFilePath(), QSettings::IniFormat );
    settings.beginGroup("SystemSettings");
    settings.setValue("Password", password);
}

QString Setting::getPassword ( )  {
    path = new Paths();
    QString m_strWorkingPath = path->getSettingFilePath(), password;
    QSettings settings( m_strWorkingPath, QSettings::IniFormat );
    settings.beginGroup("SystemSettings");
    password = settings.value("Password").toString();

    password = Encryption::getDecryptedPass(password);

    return password;
}

void Setting::setAppUser(const QString &username ){
    path = new Paths();
    QSettings settings( path->getSettingFilePath(), QSettings::IniFormat );
    settings.beginGroup("UserDetails");
    settings.setValue("User", username);
}

QString Setting::getAppUser ( )  {
    path = new Paths();
    QString m_strWorkingPath = path->getSettingFilePath(), username;
    QSettings settings( m_strWorkingPath, QSettings::IniFormat );
    settings.beginGroup("UserDetails");
    username = settings.value("User").toString();

    return username;
}

void Setting::setParameters(const QString &server, const QString &port, const QString &user, const QString &password ) {
    path = new Paths();
    QSettings settings( path->getSettingFilePath(), QSettings::IniFormat );
    settings.beginGroup("SystemSettings");
    settings.setValue("DatabaseName", "");
    settings.setValue("Hostname", server);
    settings.setValue("Port", port);
    settings.setValue("Username", user);
    settings.setValue("Password", Encryption::setEncryptedPass(password));
    settings.endGroup();
}

