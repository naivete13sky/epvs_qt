#include "../../Include/ccMethod/MySoup.h"
#include <libxml/HTMLparser.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>
#include <QtCore/QDebug>
#include <list>
#include <string>
#include <map>






std::list<Dictionary> MySoup::parseHtml(const QString& htmlContent,QString xpathText)
{
    
    std::list<Dictionary> myDictList;

    // ��ʼ��libxml2��
    xmlInitParser();

    // ��HTML����ת��ΪC�ַ���
    QByteArray htmlBytes = htmlContent.toUtf8();
    const char* html = htmlBytes.constData();

    // ����HTML�ĵ�������
    htmlDocPtr doc = htmlReadMemory(html, htmlBytes.length(), nullptr, nullptr, HTML_PARSE_RECOVER);

    if (doc == nullptr) {
        qCritical("Failed to parse HTML");
        return myDictList;
    }

    // ����XPath������
    xmlXPathContextPtr xpathCtx = xmlXPathNewContext(doc);
    if (xpathCtx == nullptr) {
        qCritical("Failed to create XPath context");
        xmlFreeDoc(doc);
        return myDictList;
    }

    // ʹ��XPath���ʽѡ�����������ֶ�Ԫ��
    //xmlXPathObjectPtr xpathObj = xmlXPathEvalExpression(reinterpret_cast<const xmlChar*>("//input[@type='hidden']"), xpathCtx);
    QByteArray byteArrayXpathText = xpathText.toUtf8();  // ����ʹ�� toLatin1()
    const char* charArrayXpathText = byteArrayXpathText.constData();
    xmlXPathObjectPtr xpathObj = xmlXPathEvalExpression(reinterpret_cast<const xmlChar*>(charArrayXpathText), xpathCtx);
    if (xpathObj == nullptr) {
        qCritical("Failed to evaluate XPath expression");
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return myDictList;
    }

    // ��ȡ�ֶ�ֵ
    xmlNodeSetPtr nodes = xpathObj->nodesetval;
    for (int i = 0; i < nodes->nodeNr; ++i) {
        xmlNodePtr node = nodes->nodeTab[i];
        xmlChar* value = xmlGetProp(node, reinterpret_cast<const xmlChar*>("value"));
        if (value != nullptr) {
            QString fieldName = reinterpret_cast<const char*>(xmlGetProp(node, reinterpret_cast<const xmlChar*>("name")));
            QString fieldValue = reinterpret_cast<const char*>(value);
            qDebug() << "Field Name: " << fieldName;
            qDebug() << "Field Value: " << fieldValue;
            Dictionary dictData;
            dictData.name = fieldName.toStdString();
            dictData.value = fieldValue.toStdString();
            myDictList.push_back(dictData);

            xmlFree(value);
        }
    }

    // �ͷ���Դ
    xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx);
    xmlFreeDoc(doc);
    xmlCleanupParser();
    

    return myDictList;
}