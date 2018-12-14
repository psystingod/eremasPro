#ifndef SETTING_H
#define SETTING_H

#include "common/paths.h"
#include "common/encryption.h"

#include <QString>
#include <QSettings>

class Setting
{
public:
    Setting();

    void setDatabasename ( const QString& );
    QString getDatabasename ( );
    void setHost ( const QString& );
    QString getHost ( );
    void setUser ( const QString& );
    QString getPort ( );
    void setPort ( const QString& );
    QString getUser ( );
    void setPassword ( const QString& );
    QString getPassword ( );
    void setAppUser ( const QString& );
    QString getAppUser ( );

    void setParameters(const QString&, const QString&, const QString&, const QString&);

    ~Setting();

private:
    Paths *path;

};

#endif // SETTING_H
