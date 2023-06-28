#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_EPVS.h"
#include "../Include/QListWidgetCommonFolder.h"
#include <vector>
#include "../Include/CustomComboBox.h"

class EPVS : public QMainWindow
{
    Q_OBJECT

public:
    EPVS(QWidget *parent = nullptr);
    ~EPVS();
    QString current_folder;// 当前所选文件夹的路径
    std::vector<QString> back_history;// 文件夹路径的历史记录
    std::vector<QString> forward_history;// 前进路径的历史记录
    CustomComboBox* comboBoxMainFileExplorerPath;

    void triggerQListWidgetCommonFolderStr_update(const QString& message);
    QListWidgetCommonFolder* folder_list;
    
    void updateFolderContents(const QString& path);
    

public slots:
    void on_folderListItemClicked(QListWidgetItem* item);
    //void folderSelected(const QModelIndex& index);

private:
    Ui::EPVSClass ui;
};
