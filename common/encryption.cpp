#include "encryption.h"

static QString M_KEY = "8789DCADDC90CB65DC56";
static QString M_VEC = "BC7BC98ASDC5643098CB";

Encryption::Encryption()
{

}

QString Encryption::setEncryptedPass (const QString &textPass) {

    QAESEncryption encryption(QAESEncryption::AES_256, QAESEncryption::CBC);

    QString key(M_KEY);
    QString iv(M_VEC);

    QByteArray hashKey = QCryptographicHash::hash(key.toLocal8Bit(), QCryptographicHash::Sha256);
    QByteArray hashIV = QCryptographicHash::hash(iv.toLocal8Bit(), QCryptographicHash::Md5);

    QByteArray encodeText = encryption.encode(textPass.toLocal8Bit(), hashKey, hashIV);

    return QString(encodeText.toHex());
}


QString Encryption::getDecryptedPass( const QString &textPass ) {
    QAESEncryption encryption(QAESEncryption::AES_256, QAESEncryption::CBC);

    QString key(M_KEY);
    QString iv(M_VEC);

    QByteArray hashKey = QCryptographicHash::hash(key.toLocal8Bit(), QCryptographicHash::Sha256);
    QByteArray hashIV = QCryptographicHash::hash(iv.toLocal8Bit(), QCryptographicHash::Md5);
    QByteArray decodeText = encryption.decode(QByteArray::fromHex(textPass.toUtf8()), hashKey, hashIV);

    QString decodedString = QString(encryption.removePadding(decodeText));

    return decodedString;
}
