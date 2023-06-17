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
    json jsonData;//��¼������Ϣ
    bool FlagGetLoginUrlResult = false;//�򿪵�¼��ַ�Ƿ�����Ӧ
    bool FlagGetCsrfmiddlewaretoken = false;//�Ƿ����˵�¼��ַ��csrf
    bool FlagLoginResult = false;//�Ƿ�ɹ���¼
    std::list<Dictionary> resulutMySoup;//MySoup����洢�õ�
    QUrlQuery postData;//��¼postdata���ݽṹ

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
    
    //��¼,post
    if (FlagGetCsrfmiddlewaretoken == true) {
        // ʹ�� front() ������ȡ��һ��Ԫ��
        Dictionary firstElement = resulutMySoup.front();        
        std::string csrfmiddlewaretoken = firstElement.value;        

        // ��������ͷ
        requestLogin.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
        requestLogin.setRawHeader("User-Agent", "Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/86.0.4240.198 Safari/537.36");
        requestLogin.setRawHeader("Accept", "*/*");

        // ���� POST ����            
        postData.addQueryItem("csrfmiddlewaretoken", QString::fromStdString(csrfmiddlewaretoken));
        postData.addQueryItem("username", username);
        postData.addQueryItem("password", password);
        postData.addQueryItem("next", "%2Fadmin%2F");
        reply = manager.post(requestLogin, postData.toString(QUrl::FullyEncoded).toUtf8());        
        QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
        loop.exec();

        if (reply->error() == QNetworkReply::NoError) {

            qDebug() << "reply:" << reply;
            QByteArray data2 = reply->readAll();
            // ������Ӧ����
            QTextCodec* codec2 = QTextCodec::codecForName("UTF-8");
            QString decodedData2 = codec2->toUnicode(data2);
            qDebug().noquote() << "decodedData2:" << decodedData2;
            if (decodedData2 == "") {
                FlagLoginResult = true;
                qDebug() << "FlagLoginResult:" << FlagLoginResult;
            }
            else {
                FlagLoginResult = false;
                jsonData["result"] = "false";
                jsonData["info"] = "��¼ʧ�ܣ���������ȷ���û��������룡";
                return jsonData;

            }

        }

        




        

    }


    QNetworkReply* reply3 = manager.get(QNetworkRequest(QUrl("http://10.97.80.119/admin/")));
    QEventLoop loop3;

    QObject::connect(reply3, &QNetworkReply::finished, &loop3, &QEventLoop::quit);

    loop3.exec();
    QByteArray data3 = reply3->readAll();
    // ������Ӧ����
    QTextCodec* codec3 = QTextCodec::codecForName("UTF-8");
    QString decodedData3 = codec3->toUnicode(data3);
    qDebug().noquote() << "decodedData3:" << decodedData3;





    jsonData["result"] = "true";
    
    
    
    reply->deleteLater();
    

    return jsonData;
}

