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
    QString currentFolder;// ��ǰ��ѡ�ļ��е�·��
    std::vector<QString> backHistory;// �ļ���·������ʷ��¼
    std::vector<QString> forwardHistory;// ǰ��·������ʷ��¼
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
    void on_comboBoxMainFileExplorerPath_activated();


private:
    Ui::EPVSClass ui;
};
