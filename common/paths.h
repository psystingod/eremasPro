#ifndef PATHS_H
#define PATHS_H

#include <QString>
#include <QDir>

class Paths
{
public:
    Paths();

    QString getLockImagePath ();
    QString getSettingFilePath ();
    QString getPathTreViewLogo ();

    ~Paths();
};

#endif // Paths_H
