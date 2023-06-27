// EncryptionQByteArray.cpp
#include "../../Include/ccMethod/EncryptionQByteArray.h"

EncryptionQByteArray::EncryptionQByteArray(QObject* parent) : QObject(parent)
{
    // Generate a random encryption key
    m_key = generateKey();
}

QString EncryptionQByteArray::encrypt(const QString& plainText)
{
    QByteArray plainBytes = plainText.toUtf8();

    // Encrypt the data
    QByteArray encryptedBytes = encryptData(plainBytes);

    // Convert the encrypted data to a hex string
    QString cipherText = QString::fromLatin1(encryptedBytes.toHex());

    return cipherText;
}

QString EncryptionQByteArray::decrypt(const QString& cipherText)
{
    // Convert the hex string to encrypted bytes
    QByteArray encryptedBytes = QByteArray::fromHex(cipherText.toLatin1());

    // Decrypt the data
    QByteArray decryptedBytes = decryptData(encryptedBytes);

    // Convert the decrypted bytes to plaintext
    QString plainText = QString::fromUtf8(decryptedBytes);

    return plainText;
}

QByteArray EncryptionQByteArray::generateKey()
{
    // Generate a random key using cryptographic hash function
    QCryptographicHash hash(QCryptographicHash::Sha256);
    QByteArray seed = "This is a random seed for key generation";
    hash.addData(seed);

    return hash.result();
}

QByteArray EncryptionQByteArray::encryptData(const QByteArray& data)
{
    // Perform encryption algorithm here
    // Replace this placeholder implementation with your own encryption algorithm
    QByteArray encryptedData = data.toBase64();

    return encryptedData;
}

QByteArray EncryptionQByteArray::decryptData(const QByteArray& encryptedData)
{
    // Perform decryption algorithm here
    // Replace this placeholder implementation with your own decryption algorithm
    QByteArray decryptedData = QByteArray::fromBase64(encryptedData);

    return decryptedData;
}
