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
    json jsonData;//登录返回信息
    bool FlagGetLoginUrlResult = false;//打开登录地址是否有响应
    bool FlagGetCsrfmiddlewaretoken = false;//是否获得了登录地址的csrf
    bool FlagLoginResult = false;//是否成功登录
    std::list<Dictionary> resulutMySoup;//MySoup结果存储用的
    QUrlQuery postData;//登录postdata数据结构

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
        // 处理错误，说明get登录地址没有正常回应
        FlagGetLoginUrlResult = false;
        qDebug() << "Error: " << reply->errorString();
        jsonData["result"] = "false";
        jsonData["info"] = "打开登录地址失败";
        return jsonData;
    }

    //获取csrfmiddlewaretoken
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
        // 列表为空，处理空列表的情况，获取csrf失败        
        FlagGetCsrfmiddlewaretoken = false;
        jsonData["result"] = "false";
        jsonData["info"] = "获取登录地址的csrf失败！";
        return jsonData;
    }


    
    
    //登录,post    
    Dictionary firstElement = resulutMySoup.front();// 使用 front() 函数获取第一个元素
    std::string csrfmiddlewaretoken = firstElement.value;

    // 设置请求头
    requestLogin.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    requestLogin.setRawHeader("User-Agent", "Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/86.0.4240.198 Safari/537.36");
    requestLogin.setRawHeader("Accept", "*/*");

    // 构建 POST 数据            
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
        // 处理响应数据
        codec = QTextCodec::codecForName("UTF-8");
        QString decodedData = codec->toUnicode(data);
        qDebug().noquote() << "decodedData post result:" << decodedData;
        if (decodedData == "") {
            //FlagLoginResult = true;
            
        }
        else {
            FlagLoginResult = false;
            jsonData["result"] = "false";
            jsonData["info"] = "登录失败，请输入正确的用户名或密码！";
            return jsonData;
        }
        qDebug() << "FlagLoginResult:" << FlagLoginResult;

    }
    else {
        // 处理错误，说明post录地址没有正常回应
        FlagLoginResult = false;
        qDebug() << "Error: " << reply->errorString();
        jsonData["result"] = "false";
        jsonData["info"] = "登录时未能正常响应！";
        return jsonData;
    }
    
    // 再打开一下admin，如果能搜索到“注销”说明登录成功，否则可能登录还是失败的
    reply = manager.get(QNetworkRequest(QUrl("http://10.97.80.119/admin/")));
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    if (reply->error() == QNetworkReply::NoError) {
        data = reply->readAll();
        // 处理响应数据
        codec = QTextCodec::codecForName("UTF-8");
        decodedData = codec->toUnicode(data);
        //qDebug().noquote() << "decodedData admin:" << decodedData;        

        if (decodedData.contains("注销")) {
            jsonData["result"] = "true";//登录成功
            std::cout << "文本中包含了\"注销\"。" << std::endl;
            FlagLoginResult = true;
        }
        else {
            std::cout << "文本中不包含\"注销\"。" << std::endl;
            jsonData["result"] = "false";//登录失败
            FlagLoginResult = false;
            jsonData["info"] = "打开的admin后台中没有注销这个词，说明登录没成功！";
            return jsonData;
        }



        
    }
    else {
        // 处理错误，说明打开admin地址没有正常回应
        FlagLoginResult = false;
        qDebug() << "Error: " << reply->errorString();
        jsonData["result"] = "false";
        jsonData["info"] = "未能打开admin后台，说明登录没成功！";
        return jsonData;
    }
    

    // 释放资源    
    reply->deleteLater();
    

    return jsonData;
}

