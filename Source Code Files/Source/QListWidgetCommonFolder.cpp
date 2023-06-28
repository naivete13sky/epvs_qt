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
    // 添加常用文件夹项
    addItem("桌面");
    addItem("下载");
    addItem("文档");
    addItem("图片");
    addItem("音乐");
    addItem("视频");

    

    // 读取配置文件
    QFile file("settings/epvs.json");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QByteArray jsonData = file.readAll();
        QJsonDocument document(QJsonDocument::fromJson(jsonData));
        QJsonObject jsonObject = document.object();
        QJsonObject commonFolderObject = jsonObject["general"].toObject()["common_folder"].toObject();

        // 添加自定义常用文件夹
        for (const QString& folderName : commonFolderObject.keys())
        {
            addItem(folderName);
        }
    }

    // 设置右键菜单处理函数
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

    // 创建快捷菜单并添加动作
    QMenu menu(this);
    QAction deleteAction("Delete", this);
    menu.addAction(&deleteAction);

    // 在全局坐标位置显示快捷菜单
    QAction* selectedAction = menu.exec(mapToGlobal(pos));

    // 处理选择的动作
    if (selectedAction == &deleteAction)
    {
        QString itemText = item->text();
        qDebug() << "Delete item:" << itemText;

        if (itemText != "桌面" && itemText != "下载" && itemText != "文档" && itemText != "图片" && itemText != "音乐" && itemText != "视频")
        {
            // 读取配置文件
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

                // 将JSON对象写入文件
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
            QMessageBox::information(this, "无法删除", "此文件夹为固定常用文件夹，无法删除！");
        }
    }
}


bool QListWidgetCommonFolder::isFixedCommonFolder(const QString& folderName)
{
    QStringList fixedFolders = { "桌面", "下载", "文档", "图片", "音乐", "视频" };
    return fixedFolders.contains(folderName);
}