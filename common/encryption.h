#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <QString>
#include <QCryptographicHash>
#include <QtDebug>
#include <QTextCodec>

#include "qaesencryption.h"

class Encryption
{
public:
    Encryption();

    static QString setEncryptedPass ( const QString& );
    static QString getDecryptedPass ( const QString& );

    ~Encryption();
};

#endif // ENCRYPTION_H
