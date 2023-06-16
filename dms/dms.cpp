#include "dms.h"
#include <iostream>
#include <nlohmann/json.hpp>
#include <QTextCodec>
#include <gumbo.h>
#include <libxml/HTMLparser.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>


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


        const char* html = "<form class=\"simpleui-form\" action=\"/admin/login/\" method=\"post\" id=\"login-form\">\n"
            "    <input type=\"hidden\" name=\"csrfmiddlewaretoken\" value=\"JUV2r51P0z1zFOC1ukIRsfUp8g317hoe1NdwvujlCOwKIz7jvml81DPivWJKBP1r\">\n"
            "    <div class=\"simpleui-input-inline\">\n"
            "        <el-input prefix-icon=\"fas fa-user\" v-model=\"username\" name=\"username\"\n"
            "                  placeholder=\"用户名\" autofocus></el-input>\n"
            "    </div>\n"
            "    <div class=\"simpleui-input-inline\">\n"
            "        <el-input prefix-icon=\"fas fa-lock\" type=\"password\" v-model=\"password\" name=\"password\"\n"
            "                  @keyup.enter.native=\"login()\"\n"
            "                  placeholder=\"密码\" show-password></el-input>\n"
            "    </div>\n"
            "    \n"
            "    <div class=\"simpleui-input-inline login-btn\">\n"
            "        <el-button :icon=\"loading?'el-icon-loading':''\" @click=\"login()\"\n"
            "                   type=\"primary\">登录</el-button>\n"
            "    </div>\n"
            "\n"
            "    <input type=\"hidden\" name=\"next\" value=\"/admin/\"/>\n"
            "</form>";


        
        parseHtml(html);










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


void DMS::parseHtml(const QString& htmlContent) {
    // 初始化libxml2库
    xmlInitParser();

    // 将HTML内容转换为C字符串
    QByteArray htmlBytes = htmlContent.toUtf8();
    const char* html = htmlBytes.constData();

    // 创建HTML文档解析器
    htmlDocPtr doc = htmlReadMemory(html, htmlBytes.length(), nullptr, nullptr, HTML_PARSE_RECOVER);

    if (doc == nullptr) {
        qCritical("Failed to parse HTML");
        return;
    }

    // 创建XPath上下文
    xmlXPathContextPtr xpathCtx = xmlXPathNewContext(doc);
    if (xpathCtx == nullptr) {
        qCritical("Failed to create XPath context");
        xmlFreeDoc(doc);
        return;
    }

    // 使用XPath表达式选择所有隐藏字段元素
    xmlXPathObjectPtr xpathObj = xmlXPathEvalExpression(reinterpret_cast<const xmlChar*>("//input[@type='hidden']"), xpathCtx);
    if (xpathObj == nullptr) {
        qCritical("Failed to evaluate XPath expression");
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return;
    }

    // 提取隐藏字段值
    xmlNodeSetPtr nodes = xpathObj->nodesetval;
    for (int i = 0; i < nodes->nodeNr; ++i) {
        xmlNodePtr node = nodes->nodeTab[i];
        xmlChar* value = xmlGetProp(node, reinterpret_cast<const xmlChar*>("value"));
        if (value != nullptr) {
            QString fieldName = reinterpret_cast<const char*>(xmlGetProp(node, reinterpret_cast<const xmlChar*>("name")));
            QString fieldValue = reinterpret_cast<const char*>(value);
            qDebug() << "Field Name: " << fieldName;
            qDebug() << "Field Value: " << fieldValue;
            xmlFree(value);
        }
    }

    // 释放资源
    xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx);
    xmlFreeDoc(doc);
    xmlCleanupParser();
}