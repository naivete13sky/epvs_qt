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
    QString current_folder;// ��ǰ��ѡ�ļ��е�·��
    std::vector<QString> back_history;// �ļ���·������ʷ��¼
    std::vector<QString> forward_history;// ǰ��·������ʷ��¼
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
