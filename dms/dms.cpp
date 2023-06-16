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
        // ������Ӧ����
        QTextCodec* codec = QTextCodec::codecForName("UTF-8");
        QString decodedData = codec->toUnicode(data);
        
        //qDebug().noquote() << "decodedData:" << decodedData;
        //qDebug() << "qPrintable,decodedData:" << qPrintable(decodedData);

        MySoup mySoup;
        
        //mySoup.parseHtml(decodedData, "//input[@name='csrfmiddlewaretoken']");


        std::list<Dictionary> resulut = mySoup.parseHtml(decodedData, "//input[@name='csrfmiddlewaretoken']");
        if (!resulut.empty()) {
            // ʹ�� front() ������ȡ��һ��Ԫ��
            Dictionary firstElement = resulut.front();
            // ����������ʹ�� firstElement ���в���
            std::string csrfmiddlewaretoken = firstElement.value;


            // ���� QNetworkRequest �������� URL
            QNetworkRequest request(QUrl("http://10.97.80.119/admin/login/"));

            // ��������ͷ
            request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

            // ���� POST ���������
            QString postData = QString("csrfmiddlewaretoken=%1&username=cc&password=cc&next=%2Fadmin%2F").arg(QString::fromStdString(csrfmiddlewaretoken));
            // ����� "your_username" �� "your_password" ����Ҫ�ύ��ʵ���û���������


            // ���� POST ����            
            postData1.addQueryItem("csrfmiddlewaretoken", QString::fromStdString(csrfmiddlewaretoken));
            postData1.addQueryItem("username", "cc");
            postData1.addQueryItem("password", "cc");
            postData1.addQueryItem("next", "%2Fadmin%2F");
            // ���� POST ����ģ���¼            
            QNetworkRequest postRequest(QUrl("http://10.97.80.119/admin/login/"));
            postRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

            reply = manager.post(postRequest, postData1.toString(QUrl::FullyEncoded).toUtf8());
            QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
            loop.exec();

            // �����¼��ķ��ؽ��
            data = reply->readAll();
            

            // ���� POST ����
            //QNetworkReply* reply2 = manager.post(request, postData.toUtf8());


            //QEventLoop loop;

            //QObject::connect(reply2, &QNetworkReply::finished, &loop, &QEventLoop::quit);

            //loop.exec();

            if (reply->error() == QNetworkReply::NoError) {
                
                qDebug() << "reply2:" << reply;
                QByteArray data2 = reply->readAll();
                // ������Ӧ����
                QTextCodec* codec2 = QTextCodec::codecForName("UTF-8");
                QString decodedData2 = codec2->toUnicode(data2);

                qDebug().noquote() << "decodedData2:" << decodedData2;

            }


        }
        else {
            // �б�Ϊ�գ�������б�����
        }

        





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

