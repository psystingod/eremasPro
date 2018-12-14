#include "paths.h"

Paths::Paths()
{

}

QString Paths::getLockImagePath () {
    // Get image path for Lowin window
    return ":/images/128_Lock.png";
}

QString Paths::getSettingFilePath () {
    // Get image path for settings file
    return QDir::currentPath() + "/settings/settings.plist";
}

QString Paths::getPathTreViewLogo () {
    // Get the image for the treeView trigger
    return ":/images/menu.png";
}


