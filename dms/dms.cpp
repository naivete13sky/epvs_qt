#include "dms.h"
#include <iostream>
#include <nlohmann/json.hpp>
#include <QTextCodec>
#include <gumbo.h>
#include <libxml/HTMLparser.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>
#include "../ccMethod/MySoup.h"


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

        MySoup mySoup;
        
        mySoup.parseHtml(decodedData);










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


//void DMS::parseHtml(const QString& htmlContent) {
//    // ��ʼ��libxml2��
//    xmlInitParser();
//
//    // ��HTML����ת��ΪC�ַ���
//    QByteArray htmlBytes = htmlContent.toUtf8();
//    const char* html = htmlBytes.constData();
//
//    // ����HTML�ĵ�������
//    htmlDocPtr doc = htmlReadMemory(html, htmlBytes.length(), nullptr, nullptr, HTML_PARSE_RECOVER);
//
//    if (doc == nullptr) {
//        qCritical("Failed to parse HTML");
//        return;
//    }
//
//    // ����XPath������
//    xmlXPathContextPtr xpathCtx = xmlXPathNewContext(doc);
//    if (xpathCtx == nullptr) {
//        qCritical("Failed to create XPath context");
//        xmlFreeDoc(doc);
//        return;
//    }
//
//    // ʹ��XPath���ʽѡ�����������ֶ�Ԫ��
//    xmlXPathObjectPtr xpathObj = xmlXPathEvalExpression(reinterpret_cast<const xmlChar*>("//input[@type='hidden']"), xpathCtx);
//    if (xpathObj == nullptr) {
//        qCritical("Failed to evaluate XPath expression");
//        xmlXPathFreeContext(xpathCtx);
//        xmlFreeDoc(doc);
//        return;
//    }
//
//    // ��ȡ�����ֶ�ֵ
//    xmlNodeSetPtr nodes = xpathObj->nodesetval;
//    for (int i = 0; i < nodes->nodeNr; ++i) {
//        xmlNodePtr node = nodes->nodeTab[i];
//        xmlChar* value = xmlGetProp(node, reinterpret_cast<const xmlChar*>("value"));
//        if (value != nullptr) {
//            QString fieldName = reinterpret_cast<const char*>(xmlGetProp(node, reinterpret_cast<const xmlChar*>("name")));
//            QString fieldValue = reinterpret_cast<const char*>(value);
//            qDebug() << "Field Name: " << fieldName;
//            qDebug() << "Field Value: " << fieldValue;
//            xmlFree(value);
//        }
//    }
//
//    // �ͷ���Դ
//    xmlXPathFreeObject(xpathObj);
//    xmlXPathFreeContext(xpathCtx);
//    xmlFreeDoc(doc);
//    xmlCleanupParser();
//}