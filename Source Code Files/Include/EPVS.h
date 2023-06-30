#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_EPVS.h"
#include "../Include/QListWidgetCommonFolder.h"
#include <vector>
#include "../Include/CustomComboBox.h"
#include <QModelIndex>
#include "../Include/ListViewFile.h"
#include <QTabWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QTreeView>
#include <QVBoxLayout>


class EPVS : public QMainWindow
{
    Q_OBJECT

public:
    EPVS(QWidget *parent = nullptr);
    ~EPVS();

    QString currentFolder;// ��ǰ��ѡ�ļ��е�·��
    std::vector<QString> backHistory;// �ļ���·������ʷ��¼
    std::vector<QString> forwardHistory;// ǰ��·������ʷ��¼    
    QString path;


    QWidget* centralWidget;// ��widget�����������Ҫ��Ϊ��������
    QTabWidget* tabWidget;//centralWidget-->tabWidget
    QVBoxLayout* layout_main;
    QWidget* centralwidgetTabWidget;//centralWidget-->tabWidget-->centralwidgetTabWidget


    QWidget* tabMainFileExplorer;
    QWidget* widget_fileExplorer_top;//tabMainFileExplorer--widget_fileExplorer_top
    QPushButton* pushButtonMainFileExplorerForward;// ǰ��
    QPushButton* pushButtonMainFileExplorerUp;// ����
    QPushButton* pushButtonMainFileExplorerBack;// ����
    CustomComboBox* comboBoxMainFileExplorerPath;
    QLineEdit* lineEditMainFileExplorerSearch;// ����

    QWidget* widget_fileExplorer_bot;//tabMainFileExplorer--widget_fileExplorer_bot
    QWidget* widgetMainFileExplorerRightMain;//tabMainFileExplorer--widget_fileExplorer_bot--widgetMainFileExplorerRightMain
    QWidget* widgetMainFileExplorerSideBar;//tabMainFileExplorer--widget_fileExplorer_bot--widgetMainFileExplorerSideBar
    QWidget* widgetLeftSiderTop;//tabMainFileExplorer--widget_fileExplorer_bot--widgetMainFileExplorerSideBar--widgetLeftSiderTop
    QWidget* widgetLeftSiderBot;//tabMainFileExplorer--widget_fileExplorer_bot--widgetMainFileExplorerSideBar--widgetLeftSiderBot

    QTreeView* file_tree_view;
    ListViewFile* folderListView;
    ListViewFileForList* folderListViewForList;



    QWidget* tabMainEPVS;
    QWidget* widget_vs_left;//tabMainEPVS-->widget_vs_left
    QWidget* widget_vs_left_top;//tabMainEPVS-->widget_vs_left-->widget_vs_left_top
    QWidget* widget_vs_left_bot;//tabMainEPVS-->widget_vs_left-->widget_vs_left_bot
    QTableWidget* tableWidgetVS;//tabMainEPVS-->widget_vs_left-->widget_vs_left_bot-->tableWidgetVS

    QWidget* widget_vs_right;//tabMainEPVS-->widget_vs_right
    QWidget* widget_vs_right_top;//tabMainEPVS-->widget_vs_right-->widget_vs_right_top
    QWidget* widget_vs_right_bot;//tabMainEPVS-->widget_vs_right-->widget_vs_right_bot



    QPushButton* pushButtonJobBReset;





    void initPublicVariable();
    void createCentralWidget();
    void createQTabWidget();

    void createMainFileExplorerTab();
    void createMainFileExplorerWidget(QWidget* tabMainFileExplorer);
    void createFileExplorerTopLayout(QWidget* widget_fileExplorer_top);
    void createFileExplorerBotLayout(QWidget* widget_fileExplorer_bot);
    void createMainFileExplorerRightMainLayout(QWidget* widgetMainFileExplorerRightMain);
    void createMainFileExplorerSideBarLayout(QWidget* widgetMainFileExplorerSideBar);
    void createLeftSiderTopLayout(QWidget* widgetLeftSiderTop);
    void createLeftSiderBotLayout(QWidget* widgetLeftSiderBot);

    void createMainEPVSTab();
    void createMainEPVSWidget(QWidget* tabMainEPVS);
    void createMainEPVSLeftTopLayout(QWidget* widget_vs_left_top);
    void createMainEPVSLeftBotLayout(QWidget* widget_vs_left_bot);
    void createMainEPVSRightLayout(QWidget* widget_vs_right);


    void set_column_width_ratios(QTableWidget* tableWidget, const QList<int>& ratios);
    void resizeEvent(QResizeEvent* event);//��д�¼�


    void setConnect();


    void triggerQListWidgetCommonFolderStr_update(const QString& message);
    QListWidgetCommonFolder* common_folder_list;
    
    void updateFolderContents(const QString& pathText);
    void searchResultSelected(const QModelIndex& index);
    
    void closeEvent(QCloseEvent* event);

    

public slots:
    void on_goBackClicked();
    void on_goForwardClicked();
    void on_goUpClicked();
    void on_commonFolderListItemClicked(QListWidgetItem* item);
    void on_folderSelectedDoubleClicked(const QModelIndex& index);
    void on_comboBoxMainFileExplorerPath_activated();
    void on_lineEditMainFileExplorerSearchReturnPressed();
    void updateTriggerListViewFileStr(const QString& message);



    void on_buttonTestClicked();

private:
    Ui::EPVSClass ui;
};
