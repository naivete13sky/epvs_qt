#include "dms.h"
#include <iostream>
#include <nlohmann/json.hpp>
#include <QTextCodec>




DMS::DMS(QObject* parent) : QObject(parent) {
    
}

json DMS::login(const QString username, const QString password) {
    json jsonData;
    
    QNetworkReply* reply = manager.get(QNetworkRequest(QUrl("http://10.97.80.119/admin/login/")));
    QEventLoop loop;

    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);

    loop.exec();

    if (reply->error() == QNetworkReply::NoError) {
        QByteArray data = reply->readAll();
        // ������Ӧ����
        QTextCodec* codec = QTextCodec::codecForName("UTF-8");
        QString decodedData = codec->toUnicode(data);
        
        qDebug().noquote() << "decodedData:" << decodedData;
        //qDebug() << "qPrintable,decodedData:" << qPrintable(decodedData);
        jsonData["result"] = "true";
        
    }
    else {
        // �������
        qDebug() << "Error: " << reply->errorString();
        jsonData["result"] = "false";
        
    }

    reply->deleteLater();

    return jsonData;
}


