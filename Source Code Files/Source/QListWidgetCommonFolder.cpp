#pragma execution_character_set("utf-8")
#include "./../Include/QListWidgetCommonFolder.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QtCore/QDebug>
#include <QMenu>
#include <QMessageBox>


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

    

    // ��ȡ�����ļ�
    QFile file("settings/epvs.json");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QByteArray jsonData = file.readAll();
        QJsonDocument document(QJsonDocument::fromJson(jsonData));
        QJsonObject jsonObject = document.object();
        QJsonObject commonFolderObject = jsonObject["general"].toObject()["common_folder"].toObject();

        // ����Զ��峣���ļ���
        for (const QString& folderName : commonFolderObject.keys())
        {
            addItem(folderName);
        }
    }

    // �����Ҽ��˵�������
    setContextMenuPolicy(Qt::CustomContextMenu);
    //connect(this, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(folderListHandleRightClick(const QPoint&)));
    connect(this, &QListWidget::customContextMenuRequested, this, &QListWidgetCommonFolder::folderListHandleRightClick);


    

}



QListWidgetCommonFolder::~QListWidgetCommonFolder()
{}




void QListWidgetCommonFolder::folderListHandleRightClick(const QPoint& pos)
{
    QListWidgetItem* item = itemAt(pos);
    if (!item)
        return;

    // ������ݲ˵�����Ӷ���
    QMenu menu(this);
    QAction deleteAction("Delete", this);
    menu.addAction(&deleteAction);

    // ��ȫ������λ����ʾ��ݲ˵�
    QAction* selectedAction = menu.exec(mapToGlobal(pos));

    // ����ѡ��Ķ���
    if (selectedAction == &deleteAction)
    {
        QString itemText = item->text();
        qDebug() << "Delete item:" << itemText;

        if (itemText != "����" && itemText != "����" && itemText != "�ĵ�" && itemText != "ͼƬ" && itemText != "����" && itemText != "��Ƶ")
        {
            // ��ȡ�����ļ�
            QFile file("settings/epvs.json");
            if (file.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                QString jsonData = file.readAll();
                file.close();

                QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData.toUtf8());
                QJsonObject jsonObj = jsonDoc.object();
                QJsonObject commonFolderObj = jsonObj["general"].toObject()["common_folder"].toObject();

                commonFolderObj.remove(itemText);

                jsonObj["general"].toObject()["common_folder"] = commonFolderObj;

                // ��JSON����д���ļ�
                if (file.open(QIODevice::WriteOnly | QIODevice::Text))
                {
                    file.write(QJsonDocument(jsonObj).toJson());
                    file.close();
                }

                emit triggerQListWidgetCommonFolderStr(QString::number(row(item)));
            }
        }
        else
        {
            QMessageBox::information(this, "�޷�ɾ��", "���ļ���Ϊ�̶������ļ��У��޷�ɾ����");
        }
    }
}


bool QListWidgetCommonFolder::isFixedCommonFolder(const QString& folderName)
{
    QStringList fixedFolders = { "����", "����", "�ĵ�", "ͼƬ", "����", "��Ƶ" };
    return fixedFolders.contains(folderName);
}