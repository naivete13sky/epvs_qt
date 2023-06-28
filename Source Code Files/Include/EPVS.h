#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_EPVS.h"
#include "../Include/QListWidgetCommonFolder.h"
#include <vector>
#include "../Include/CustomComboBox.h"
#include <QModelIndex>

class EPVS : public QMainWindow
{
    Q_OBJECT

public:
    EPVS(QWidget *parent = nullptr);
    ~EPVS();
    QString currentFolder;// 当前所选文件夹的路径
    std::vector<QString> backHistory;// 文件夹路径的历史记录
    std::vector<QString> forwardHistory;// 前进路径的历史记录
    CustomComboBox* comboBoxMainFileExplorerPath;

    void triggerQListWidgetCommonFolderStr_update(const QString& message);
    QListWidgetCommonFolder* common_folder_list;
    
    void updateFolderContents(const QString& path);
    

public slots:
    void on_goBackClicked();
    void on_goForwardClicked();
    void on_goUpClicked();
    void on_commonFolderListItemClicked(QListWidgetItem* item);
    void on_folderSelectedDoubleClicked(const QModelIndex& index);


private:
    Ui::EPVSClass ui;
};
