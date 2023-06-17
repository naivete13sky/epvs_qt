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


    // ���� QNetworkRequest �������� URL
    QNetworkRequest requestLogin(QUrl("http://10.97.80.119/admin/login/"));    
    QNetworkReply* reply = manager.get(requestLogin);
    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    //�򿪵�¼��ַ�������
    if (reply->error() == QNetworkReply::NoError) {
        //˵��get��¼��ַ��������Ӧ
        FlagGetLoginUrlResult = true;       
    }
    else {
        // �������
        //˵��get��¼��ַû��������Ӧ
        FlagGetLoginUrlResult = false;
        qDebug() << "Error: " << reply->errorString();
        jsonData["result"] = "false";
        jsonData["info"] = "�򿪵�¼��ַʧ��";
        return jsonData;
    }

    //��ȡcsrfmiddlewaretoken
    if (FlagGetLoginUrlResult == true) {
        QByteArray data = reply->readAll();
        // ������Ӧ����
        QTextCodec* codec = QTextCodec::codecForName("UTF-8");
        QString decodedData = codec->toUnicode(data);

        //qDebug().noquote() << "decodedData:" << decodedData;
        //qDebug() << "qPrintable,decodedData:" << qPrintable(decodedData);

        MySoup mySoup;
        resulutMySoup = mySoup.parseHtml(decodedData, "//input[@name='csrfmiddlewaretoken']");
        if (!resulutMySoup.empty()) {
            //��ȡcsrf�ɹ�
            FlagGetCsrfmiddlewaretoken = true;
        }
        else {
            // �б�Ϊ�գ�������б�����
        }
    }
    else {
        //��ȡcsrfʧ��
        FlagGetCsrfmiddlewaretoken = false;
        jsonData["result"] = "false";
        jsonData["info"] = "��ȡ��¼��ַ��csrfʧ�ܣ�";
        return jsonData;
    }
    

    if (FlagGetCsrfmiddlewaretoken == true) {
        // ʹ�� front() ������ȡ��һ��Ԫ��
        Dictionary firstElement = resulutMySoup.front();
        // ����������ʹ�� firstElement ���в���
        std::string csrfmiddlewaretoken = firstElement.value;


        // ���� QNetworkRequest �������� URL
        QNetworkRequest request2(QUrl("http://10.97.80.119/admin/login/"));

        // ��������ͷ
        request2.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
        request2.setRawHeader("User-Agent", "Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/86.0.4240.198 Safari/537.36");
        request2.setRawHeader("Accept", "*/*");


        // ���� POST ����            
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
            // ������Ӧ����
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
        // ������Ӧ����
        QTextCodec* codec3 = QTextCodec::codecForName("UTF-8");
        QString decodedData3 = codec3->toUnicode(data3);
        qDebug().noquote() << "decodedData3:" << decodedData3;

    }


    





    jsonData["result"] = "true";
    
    
    
    reply->deleteLater();
    

    return jsonData;
}

