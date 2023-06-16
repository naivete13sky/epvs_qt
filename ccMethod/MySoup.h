#ifndef MYSOUP_H
#define MYSOUP_H

#include <QJsonObject>
#include <QVariant>
#include <list>


struct Dictionary {
    std::string name;
    std::string value;
};





class MySoup
{
public:
    std::list<Dictionary> parseHtml(const QString& htmlContent, QString xpathText);

};

#endif // MYSOUP_H


//class EncryptionQByteArray : public QObject
//{
//    Q_OBJECT
//public:
//    explicit EncryptionQByteArray(QObject* parent = nullptr);
//
//    QString encrypt(const QString& plainText);
//    QString decrypt(const QString& cipherText);
//
//private:
//    QByteArray generateKey();
//    QByteArray encryptData(const QByteArray& data);
//    QByteArray decryptData(const QByteArray& encryptedData);
//
//private:
//    QByteArray m_key;
//};
