// EncryptionQByteArray.h
#ifndef ENCRYPTIONQBYTEARRY_H
#define ENCRYPTIONQBYTEARRY_H

#include <QObject>
#include <QCryptographicHash>

class EncryptionQByteArray : public QObject
{
    Q_OBJECT
public:
    explicit EncryptionQByteArray(QObject* parent = nullptr);

    QString encrypt(const QString& plainText);
    QString decrypt(const QString& cipherText);

private:
    QByteArray generateKey();
    QByteArray encryptData(const QByteArray& data);
    QByteArray decryptData(const QByteArray& encryptedData);

private:
    QByteArray m_key;
};

#endif // ENCRYPTIONQBYTEARRY_H

