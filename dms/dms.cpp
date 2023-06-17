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
        
        //qDebug().noquote() << "decodedData:" << decodedData;
        //qDebug() << "qPrintable,decodedData:" << qPrintable(decodedData);

        MySoup mySoup;
        
        //mySoup.parseHtml(decodedData, "//input[@name='csrfmiddlewaretoken']");


        std::list<Dictionary> resulut = mySoup.parseHtml(decodedData, "//input[@name='csrfmiddlewaretoken']");
        if (!resulut.empty()) {
            // 使用 front() 函数获取第一个元素
            Dictionary firstElement = resulut.front();
            // 现在您可以使用 firstElement 进行操作
            std::string csrfmiddlewaretoken = firstElement.value;


            // 创建 QNetworkRequest 对象并设置 URL
            QNetworkRequest request2(QUrl("http://10.97.80.119/admin/login/"));

            // 设置请求头
            request2.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
            request2.setRawHeader("User-Agent", "python-requests/2.30.0");
            request2.setRawHeader("Accept", "*/*");
            // 构建 POST 请求的数据
            //QString postData = QString("csrfmiddlewaretoken=%1&username=cc&password=cc&next=%2Fadmin%2F").arg(QString::fromStdString(csrfmiddlewaretoken));
            

            QByteArray postData;
            postData.append("csrfmiddlewaretoken=");
            postData.append(csrfmiddlewaretoken.c_str());
            postData.append("&username=cc&password=cc&next=%2Fadmin%2F");
            QNetworkReply* reply2 = manager.post(request2, postData);
            QEventLoop loop2;
            QObject::connect(reply2, &QNetworkReply::finished, &loop2, &QEventLoop::quit);
            loop2.exec();
            
            
            //// 构建 POST 数据            
            //postData1.addQueryItem("csrfmiddlewaretoken", QString::fromStdString(csrfmiddlewaretoken));
            //postData1.addQueryItem("username", "cc");
            //postData1.addQueryItem("password", "cc");
            //postData1.addQueryItem("next", "%2Fadmin%2F");
            // 发送 POST 请求，模拟登录            
            //QNetworkRequest postRequest(QUrl("http://10.97.80.119/admin/login/"));
            //postRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

            //reply = manager.post(postRequest, postData1.toString(QUrl::FullyEncoded).toUtf8());
            //QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
            //loop.exec();

            // 处理登录后的返回结果
            //data = reply->readAll();
            

            // 发送 POST 请求
            //QNetworkReply* reply2 = manager.post(request, postData.toUtf8());


            //QEventLoop loop;

            //QObject::connect(reply2, &QNetworkReply::finished, &loop, &QEventLoop::quit);

            //loop.exec();

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
        else {
            // 列表为空，处理空列表的情况
        }

        





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

