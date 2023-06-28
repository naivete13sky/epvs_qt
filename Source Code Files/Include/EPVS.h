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
    QListWidgetCommonFolder* folder_list;
    
    void updateFolderContents(const QString& path);
    

public slots:
    void goBack();
    void goForward();
    void goUp();
    void on_folderListItemClicked(QListWidgetItem* item);
    void on_folderSelectedDoubleClicked(const QModelIndex& index);


private:
    Ui::EPVSClass ui;
};
