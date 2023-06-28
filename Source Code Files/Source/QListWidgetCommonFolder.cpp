#pragma execution_character_set("utf-8")
#include "./../Include/QListWidgetCommonFolder.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QtCore/QDebug>


QListWidgetCommonFolder::QListWidgetCommonFolder(QWidget* parent)
	: QListWidget(parent)
{
	setStyleSheet("background-color: lightgray;");
    // 添加常用文件夹项
    addItem("桌面");
    addItem("下载");
    addItem("文档");
    addItem("图片");
    addItem("音乐");
    addItem("视频");

    // 增加自定义常用文件夹，从配置文件读取
    // 读取配置文件
    QJsonDocument doc;
    QJsonObject general_data;
    QFile file("settings/epvs.json");
    // 从文件读取JSON数据
    if (file.open(QIODevice::ReadOnly))
    {
        doc = QJsonDocument::fromJson(file.readAll());
        file.close();        
    }


    //QJsonObject common_folder = general_data["common_folder"].toObject();
    
    
    // 解析JSON数据并获取common_folder的内容
    
    if (!doc.isNull()) {
        if (doc.isObject()) {
            QJsonObject jsonObject = doc.object();
            QJsonValue commonFolderValue = jsonObject.value("general").toObject().value("common_folder");
            if (commonFolderValue.isObject()) {
                QJsonObject commonFolderObject = commonFolderValue.toObject();

                // 遍历输出common_folder的内容
                qDebug() << "common_folder contents:";
                for (auto it = commonFolderObject.constBegin(); it != commonFolderObject.constEnd(); ++it) {
                    QString key = it.key();
                    QString value = it.value().toString();
                    qDebug() << key << ": " << value;
                }
            }
        }
    }

    

}

QListWidgetCommonFolder::~QListWidgetCommonFolder()
{}