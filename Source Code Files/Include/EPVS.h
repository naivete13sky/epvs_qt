#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_EPVS.h"
#include "../Include/QListWidgetCommonFolder.h"
#include <vector>
#include "../Include/CustomComboBox.h"
#include <QModelIndex>
#include "../Include/ListViewFile.h"


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
    QString path;

    void triggerQListWidgetCommonFolderStr_update(const QString& message);
    QListWidgetCommonFolder* common_folder_list;
    
    void updateFolderContents(const QString& pathText);
    void searchResultSelected(const QModelIndex& index);
    
    QLineEdit* lineEditMainFileExplorerSearch;
    ListViewFile* folderListView;
    ListViewFileForList* folderListViewForList;

public slots:
    void on_goBackClicked();
    void on_goForwardClicked();
    void on_goUpClicked();
    void on_commonFolderListItemClicked(QListWidgetItem* item);
    void on_folderSelectedDoubleClicked(const QModelIndex& index);
    void on_comboBoxMainFileExplorerPath_activated();
    void on_lineEditMainFileExplorerSearchReturnPressed();

private:
    Ui::EPVSClass ui;
};
