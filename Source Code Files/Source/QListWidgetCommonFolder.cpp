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
    // ��ӳ����ļ�����
    addItem("����");
    addItem("����");
    addItem("�ĵ�");
    addItem("ͼƬ");
    addItem("����");
    addItem("��Ƶ");

    // �����Զ��峣���ļ��У��������ļ���ȡ
    // ��ȡ�����ļ�
    QJsonDocument doc;
    QJsonObject general_data;
    QFile file("settings/epvs.json");
    // ���ļ���ȡJSON����
    if (file.open(QIODevice::ReadOnly))
    {
        doc = QJsonDocument::fromJson(file.readAll());
        file.close();        
    }


    //QJsonObject common_folder = general_data["common_folder"].toObject();
    
    
    // ����JSON���ݲ���ȡcommon_folder������
    
    if (!doc.isNull()) {
        if (doc.isObject()) {
            QJsonObject jsonObject = doc.object();
            QJsonValue commonFolderValue = jsonObject.value("general").toObject().value("common_folder");
            if (commonFolderValue.isObject()) {
                QJsonObject commonFolderObject = commonFolderValue.toObject();

                // �������common_folder������
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