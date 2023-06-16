#ifndef DMS_H
#define DMS_H

#include <QObject>
#include <QCoreApplication>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>

class DMS : public QObject {
    Q_OBJECT

public:
    explicit DMS(QObject* parent = nullptr);

    void login(const QString username, const QString password);

signals:
    //void responseReceived(const QByteArray& data);
    //void errorOccurred(const QString& errorString);

private slots:
    //void onReplyFinished(QNetworkReply* reply);

private:
    //QNetworkAccessManager* manager;
};

#endif // DMS_H

