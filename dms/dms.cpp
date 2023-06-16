#include "dms.h"
#include <iostream>
#include <nlohmann/json.hpp>
#include <QTextCodec>
#include <gumbo.h>
#include <libxml/HTMLparser.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>
#include "../ccMethod/MySoup.h"
#include <list>







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
        // 处理响应数据
        QTextCodec* codec = QTextCodec::codecForName("UTF-8");
        QString decodedData = codec->toUnicode(data);
        
        qDebug().noquote() << "decodedData:" << decodedData;
        //qDebug() << "qPrintable,decodedData:" << qPrintable(decodedData);

        MySoup mySoup;
        
        //mySoup.parseHtml(decodedData, "//input[@name='csrfmiddlewaretoken']");


        std::list<Dictionary> resulut = mySoup.parseHtml(decodedData, "//input[@name='csrfmiddlewaretoken']");







        jsonData["result"] = "true";
        
    }
    else {
        // 处理错误
        qDebug() << "Error: " << reply->errorString();
        jsonData["result"] = "false";
        
    }

    reply->deleteLater();

    return jsonData;
}

