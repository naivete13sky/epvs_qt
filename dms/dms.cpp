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
        // �������˵��get��¼��ַû��������Ӧ
        FlagGetLoginUrlResult = false;
        qDebug() << "Error: " << reply->errorString();
        jsonData["result"] = "false";
        jsonData["info"] = "�򿪵�¼��ַʧ��";
        return jsonData;
    }

    //��ȡcsrfmiddlewaretoken
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
        // �б�Ϊ�գ�������б���������ȡcsrfʧ��        
        FlagGetCsrfmiddlewaretoken = false;
        jsonData["result"] = "false";
        jsonData["info"] = "��ȡ��¼��ַ��csrfʧ�ܣ�";
        return jsonData;
    }


    
    
    //��¼,post    
    Dictionary firstElement = resulutMySoup.front();// ʹ�� front() ������ȡ��һ��Ԫ��
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
        data = reply->readAll();
        // ������Ӧ����
        codec = QTextCodec::codecForName("UTF-8");
        QString decodedData = codec->toUnicode(data);
        qDebug().noquote() << "decodedData post result:" << decodedData;
        if (decodedData == "") {
            //FlagLoginResult = true;
            
        }
        else {
            FlagLoginResult = false;
            jsonData["result"] = "false";
            jsonData["info"] = "��¼ʧ�ܣ���������ȷ���û��������룡";
            return jsonData;
        }
        qDebug() << "FlagLoginResult:" << FlagLoginResult;

    }
    else {
        // �������˵��post¼��ַû��������Ӧ
        FlagLoginResult = false;
        qDebug() << "Error: " << reply->errorString();
        jsonData["result"] = "false";
        jsonData["info"] = "��¼ʱδ��������Ӧ��";
        return jsonData;
    }
    
    // �ٴ�һ��admin���������������ע����˵����¼�ɹ���������ܵ�¼����ʧ�ܵ�
    reply = manager.get(QNetworkRequest(QUrl("http://10.97.80.119/admin/")));
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    if (reply->error() == QNetworkReply::NoError) {
        data = reply->readAll();
        // ������Ӧ����
        codec = QTextCodec::codecForName("UTF-8");
        decodedData = codec->toUnicode(data);
        //qDebug().noquote() << "decodedData admin:" << decodedData;        

        if (decodedData.contains("ע��")) {
            jsonData["result"] = "true";//��¼�ɹ�
            std::cout << "�ı��а�����\"ע��\"��" << std::endl;
            FlagLoginResult = true;
        }
        else {
            std::cout << "�ı��в�����\"ע��\"��" << std::endl;
            jsonData["result"] = "false";//��¼ʧ��
            FlagLoginResult = false;
            jsonData["info"] = "�򿪵�admin��̨��û��ע������ʣ�˵����¼û�ɹ���";
            return jsonData;
        }



        
    }
    else {
        // �������˵����admin��ַû��������Ӧ
        FlagLoginResult = false;
        qDebug() << "Error: " << reply->errorString();
        jsonData["result"] = "false";
        jsonData["info"] = "δ�ܴ�admin��̨��˵����¼û�ɹ���";
        return jsonData;
    }
    

    // �ͷ���Դ    
    reply->deleteLater();
    

    return jsonData;
}

