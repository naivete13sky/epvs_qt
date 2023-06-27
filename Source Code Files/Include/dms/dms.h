#ifndef DMS_H
#define DMS_H

#include <QObject>
#include <QCoreApplication>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>
#include <iostream>
#include <nlohmann/json.hpp>
#include <QUrlQuery>


using json = nlohmann::json;

class DMS : public QObject {
    Q_OBJECT

public:
    explicit DMS(QObject* parent = nullptr);

    QNetworkAccessManager manager;




    json login(const QString username, const QString password);


    //void parseHtml(const QString& htmlContent);
    


signals:
    //void responseReceived(const QByteArray& data);
    //void errorOccurred(const QString& errorString);

private slots:
    //void onReplyFinished(QNetworkReply* reply);

private:
    //QNetworkAccessManager* manager;
};

#endif // DMS_H

