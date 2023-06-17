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
    bool FlagGetLoginUrlResult = false;
    bool FlagGetCsrfmiddlewaretoken = false;
    std::list<Dictionary> resulutMySoup;


    // 创建 QNetworkRequest 对象并设置 URL
    QNetworkRequest requestLogin(QUrl("http://10.97.80.119/admin/login/"));    
    QNetworkReply* reply = manager.get(requestLogin);
    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    //打开登录地址结果处理
    if (reply->error() == QNetworkReply::NoError) {
        //说明get登录地址有正常回应
        FlagGetLoginUrlResult = true;       
    }
    else {
        // 处理错误
        //说明get登录地址没有正常回应
        FlagGetLoginUrlResult = false;
        qDebug() << "Error: " << reply->errorString();
        jsonData["result"] = "false";
        jsonData["info"] = "打开登录地址失败";
        return jsonData;
    }

    //获取csrfmiddlewaretoken
    if (FlagGetLoginUrlResult == true) {
        QByteArray data = reply->readAll();
        // 处理响应数据
        QTextCodec* codec = QTextCodec::codecForName("UTF-8");
        QString decodedData = codec->toUnicode(data);

        //qDebug().noquote() << "decodedData:" << decodedData;
        //qDebug() << "qPrintable,decodedData:" << qPrintable(decodedData);

        MySoup mySoup;
        resulutMySoup = mySoup.parseHtml(decodedData, "//input[@name='csrfmiddlewaretoken']");
        if (!resulutMySoup.empty()) {
            //获取csrf成功
            FlagGetCsrfmiddlewaretoken = true;
        }
        else {
            // 列表为空，处理空列表的情况
        }
    }
    else {
        //获取csrf失败
        FlagGetCsrfmiddlewaretoken = false;
        jsonData["result"] = "false";
        jsonData["info"] = "获取登录地址的csrf失败！";
        return jsonData;
    }
    

    if (FlagGetCsrfmiddlewaretoken == true) {
        // 使用 front() 函数获取第一个元素
        Dictionary firstElement = resulutMySoup.front();
        // 现在您可以使用 firstElement 进行操作
        std::string csrfmiddlewaretoken = firstElement.value;


        // 创建 QNetworkRequest 对象并设置 URL
        QNetworkRequest request2(QUrl("http://10.97.80.119/admin/login/"));

        // 设置请求头
        request2.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
        request2.setRawHeader("User-Agent", "Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/86.0.4240.198 Safari/537.36");
        request2.setRawHeader("Accept", "*/*");


        // 构建 POST 数据            
        postData1.addQueryItem("csrfmiddlewaretoken", QString::fromStdString(csrfmiddlewaretoken));
        postData1.addQueryItem("username", "cc");
        postData1.addQueryItem("password", "cc");
        postData1.addQueryItem("next", "%2Fadmin%2F");
        QNetworkReply* reply2 = manager.post(request2, postData1.toString(QUrl::FullyEncoded).toUtf8());
        //QNetworkReply* reply2 = manager.post(request2, postData);
        QEventLoop loop2;
        QObject::connect(reply2, &QNetworkReply::finished, &loop2, &QEventLoop::quit);
        loop2.exec();


        if (reply2->error() == QNetworkReply::NoError) {

            qDebug() << "reply2:" << reply2;
            QByteArray data2 = reply2->readAll();
            // 处理响应数据
            QTextCodec* codec2 = QTextCodec::codecForName("UTF-8");
            QString decodedData2 = codec2->toUnicode(data2);

            qDebug().noquote() << "decodedData2:" << decodedData2;

        }

        reply2->deleteLater();




        QNetworkReply* reply3 = manager.get(QNetworkRequest(QUrl("http://10.97.80.119/admin/")));
        QEventLoop loop3;

        QObject::connect(reply3, &QNetworkReply::finished, &loop3, &QEventLoop::quit);

        loop3.exec();
        QByteArray data3 = reply3->readAll();
        // 处理响应数据
        QTextCodec* codec3 = QTextCodec::codecForName("UTF-8");
        QString decodedData3 = codec3->toUnicode(data3);
        qDebug().noquote() << "decodedData3:" << decodedData3;

    }


    





    jsonData["result"] = "true";
    
    
    
    reply->deleteLater();
    

    return jsonData;
}

