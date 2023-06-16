#include "dms.h"


DMS::DMS(QObject* parent) : QObject(parent) {
    
}

void DMS::login(const QString username, const QString password) {
    QNetworkAccessManager manager;
    QNetworkReply* reply = manager.get(QNetworkRequest(QUrl("https://www.baidu.com/")));
    QEventLoop loop;

    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);

    loop.exec();

    if (reply->error() == QNetworkReply::NoError) {
        QByteArray data = reply->readAll();
        // 处理响应数据
        qDebug() << "cc:" << data;;
    }
    else {
        // 处理错误
        qDebug() << "Error: " << reply->errorString();
    }

    reply->deleteLater();
}


