#pragma execution_character_set("utf-8")
#include "../Include/EPVS.h"
#include <QLineEdit>
#include <QPushButton>
#include <QGroupBox>
#include <QLabel>
#include <QComboBox>
#include <QTextBrowser>
#include <QVBoxLayout>
#include "../Include/QListWidgetCommonFolder.h"
#include <QTreeView>
#include <QFileSystemModel>
#include <QDir>
#include <QSplitter>
#include "../Include/CustomComboBox.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include "../Include/FileNameDelegate.h"
#include <Filter.h>
#include <QModelIndex>
#include <algorithm>
#include <QStandardItemModel>
#include "../Include/global_variables.h"
#include "../Include/g/g.h"
#include <iostream>



EPVS::EPVS(QWidget *parent)
    : QMainWindow(parent)
{
    //UI设置
    ui.setupUi(this);
    setWindowTitle("悦谱转图比对系统 EPVS-V1.0");
    setGeometry(200, 35, 1300, 900);
    
    initPublicVariable();//初始化公共变量
    createCentralWidget();//设置主窗口部件
    createQTabWidget();//主窗口中放置QTabWidget部件。
    createMainFileExplorerTab();//添加tab页面--文件管理     
    createMainEPVSTab();//添加tab页面--悦谱比图
                  
    setConnect();//连接信号槽

}

EPVS::~EPVS()
{}


void EPVS::initPublicVariable() {
    currentFolder = "";  // 当前所选文件夹的路径
    backHistory.clear();  // 文件夹路径的历史记录
    forwardHistory.clear();  // 前进路径的历史记录

}

void EPVS::createCentralWidget()
{
    centralWidget = new QWidget(this);// 创建一个QWidget对象
    centralWidget->setGeometry(0, 35, 1600, 1000);// 设置QWidget的位置和大小    
    centralWidget->setStyleSheet("background-color: red;");// 设置QWidget的背景颜色
    setCentralWidget(centralWidget);// 设置QWidget作为EPVS类的子部件


    QMenuBar* menubar = new QMenuBar(this);
    menubar->setGeometry(0, 0, 1179, 23);
    setMenuBar(menubar);

    QStatusBar* statusbar = new QStatusBar(this);
    statusbar->setObjectName("statusbar");
    setStatusBar(statusbar);



}

void EPVS::createQTabWidget() {
    // QTabWidget
    tabWidget = new QTabWidget(centralWidget);
    tabWidget->setGeometry(10, 0, 1550, 950);
    tabWidget->setTabPosition(QTabWidget::West);

    //为了使得tabWidget随着主窗口大小变化跟着调整, 需要设置一下layout。
    layout_main = new QVBoxLayout();
    //将Tab Widget放置在布局管理器中
    layout_main->addWidget(tabWidget);
    //创建一个容器窗口部件
    centralwidgetTabWidget = new QWidget();
    //将布局管理器设置为容器窗口部件的布局
    centralwidgetTabWidget->setLayout(layout_main);
    //将容器窗口部件设置为主窗口的中央部件
    setCentralWidget(centralwidgetTabWidget);


    


}

//文件管理页面
void EPVS::createMainFileExplorerTab()
{
    tabMainFileExplorer = new QWidget();
    // 创建文件管理的子部件
    createMainFileExplorerWidget(tabMainFileExplorer);
    
    

    // 设置top与 bot 2个部分可以拖拽调整大小
    QSplitter* splitter_tabMainFileExplorer_top_bot = new QSplitter();
    splitter_tabMainFileExplorer_top_bot->setStyleSheet("QSplitter::handle { background-color: darkGray; }");
    // 设置手柄宽度为1个像素
    splitter_tabMainFileExplorer_top_bot->setHandleWidth(1);
    splitter_tabMainFileExplorer_top_bot->setOrientation(Qt::Vertical);  // 设置为垂直方向分割
    splitter_tabMainFileExplorer_top_bot->addWidget(widget_fileExplorer_top);
    splitter_tabMainFileExplorer_top_bot->addWidget(widget_fileExplorer_bot);
    QHBoxLayout* layout_tabMainFileExplorer = new QHBoxLayout(tabMainFileExplorer);
    layout_tabMainFileExplorer->addWidget(splitter_tabMainFileExplorer_top_bot);
    
    
    
    // 添加到Tab Widget中
    tabWidget->addTab(tabMainFileExplorer, "");
    tabWidget->setTabText(tabWidget->indexOf(tabMainFileExplorer), "文件管理");

    // 设置tabWidget为当前活动Tab
    tabWidget->setCurrentIndex(0);
}

void EPVS::createMainFileExplorerWidget(QWidget* tabMainFileExplorer)
{
    // 创建文件管理的子部件
    widget_fileExplorer_top = new QWidget(tabMainFileExplorer);//tabMainFileExplorer--widget_fileExplorer_top
    widget_fileExplorer_top->setGeometry(0, 10, 1141, 31);

    widget_fileExplorer_bot = new QWidget(tabMainFileExplorer);
    widget_fileExplorer_bot->setGeometry(-1, 59, 1141, 751);

    widgetMainFileExplorerRightMain = new QWidget(widget_fileExplorer_bot);
    widgetMainFileExplorerRightMain->setGeometry(260, 0, 881, 781);

    widgetMainFileExplorerSideBar = new QWidget(widget_fileExplorer_bot);
    widgetMainFileExplorerSideBar->setGeometry(0, 0, 251, 781);

    widgetLeftSiderTop = new QWidget(widgetMainFileExplorerSideBar);
    widgetLeftSiderTop->setGeometry(0, 0, 231, 331);

    widgetLeftSiderBot = new QWidget(widgetMainFileExplorerSideBar);
    widgetLeftSiderBot->setGeometry(0, 340, 231, 351);


    // 添加布局和控件到各个子部件中
    createFileExplorerTopLayout(widget_fileExplorer_top);
    createFileExplorerBotLayout(widget_fileExplorer_bot);
    createMainFileExplorerRightMainLayout(widgetMainFileExplorerRightMain);
    createMainFileExplorerSideBarLayout(widgetMainFileExplorerSideBar);
    createLeftSiderTopLayout(widgetLeftSiderTop);
    createLeftSiderBotLayout(widgetLeftSiderBot);

    
}

void EPVS::createFileExplorerTopLayout(QWidget* widget_fileExplorer_top)
{
    
    lineEditMainFileExplorerSearch = new QLineEdit(widget_fileExplorer_top);
    lineEditMainFileExplorerSearch->setGeometry(880, 0, 241, 20);
    lineEditMainFileExplorerSearch->setPlaceholderText("搜索");
    pushButtonMainFileExplorerForward = new QPushButton(widget_fileExplorer_top);
    pushButtonMainFileExplorerForward->setGeometry(90, 0, 75, 23);
    pushButtonMainFileExplorerForward->setText("前进");
    pushButtonMainFileExplorerUp = new QPushButton(widget_fileExplorer_top);
    pushButtonMainFileExplorerUp->setGeometry(180, 0, 75, 23);
    pushButtonMainFileExplorerUp->setText("上级");
    pushButtonMainFileExplorerBack = new QPushButton(widget_fileExplorer_top);
    pushButtonMainFileExplorerBack->setGeometry(0, 0, 75, 23);
    pushButtonMainFileExplorerBack->setText("后退");
    

    // 设置top里的多个部分可以拖拽调整大小
    QSplitter* splitter_tabMainFileExplorer_top = new QSplitter();
    splitter_tabMainFileExplorer_top->setStyleSheet("QSplitter::handle { background-color: darkGray; }");
    splitter_tabMainFileExplorer_top->addWidget(pushButtonMainFileExplorerBack);
    splitter_tabMainFileExplorer_top->addWidget(pushButtonMainFileExplorerForward);
    splitter_tabMainFileExplorer_top->addWidget(pushButtonMainFileExplorerUp);
    splitter_tabMainFileExplorer_top->setHandleWidth(1);

    comboBoxMainFileExplorerPath = new CustomComboBox(this);
    QObject::connect(comboBoxMainFileExplorerPath, SIGNAL(activated(const QString&)), this, SLOT(comboBoxMainFileExplorerPath_enter_do(const QString&)));
    comboBoxMainFileExplorerPath->setEditable(true);
    splitter_tabMainFileExplorer_top->addWidget(comboBoxMainFileExplorerPath);
    splitter_tabMainFileExplorer_top->addWidget(lineEditMainFileExplorerSearch);
    QHBoxLayout* layout_tabMainFileExplorerTop = new QHBoxLayout(widget_fileExplorer_top);
    layout_tabMainFileExplorerTop->addWidget(splitter_tabMainFileExplorer_top);
    QList<int> sizes;
    sizes << 20 << 20 << 20 << 800 << 200;
    splitter_tabMainFileExplorer_top->setSizes(sizes);

}

void EPVS::createFileExplorerBotLayout(QWidget* widget_fileExplorer_bot)
{
    // 设置底部的侧边栏与右边主窗口2个部分可以拖拽调整大小
    QSplitter* splitter_tabMainFileExplorer_bot = new QSplitter();
    splitter_tabMainFileExplorer_bot->setStyleSheet("QSplitter::handle { background-color: darkGray; }");
    splitter_tabMainFileExplorer_bot->addWidget(widgetMainFileExplorerSideBar);
    splitter_tabMainFileExplorer_bot->addWidget(widgetMainFileExplorerRightMain);
    splitter_tabMainFileExplorer_bot->setHandleWidth(1);
    QHBoxLayout* layout_tabMainFileExplorerBot = new QHBoxLayout(widget_fileExplorer_bot);
    layout_tabMainFileExplorerBot->addWidget(splitter_tabMainFileExplorer_bot);
}

void EPVS::createMainFileExplorerRightMainLayout(QWidget* widgetMainFileExplorerRightMain)
{
    // 创建布局管理器，右侧主窗口
    QVBoxLayout* layout3 = new QVBoxLayout();
    widgetMainFileExplorerRightMain->setLayout(layout3);
    // 创建主体窗口B部件
    QWidget* content_widget = new QWidget();
    content_widget->setStyleSheet("background-color: white;");
    content_widget->setObjectName("content_widget");
    QGridLayout* content_layout = new QGridLayout(content_widget);
    content_widget->setLayout(content_layout);
    layout3->addWidget(content_widget);

}

void EPVS::createMainFileExplorerSideBarLayout(QWidget* widgetMainFileExplorerSideBar)
{
    // 设置侧边栏上下2个部分可以拖拽调整大小
    QSplitter* splitter_tabMainFileExplorer_SideBar = new QSplitter();
    splitter_tabMainFileExplorer_SideBar->setStyleSheet("QSplitter::handle { background-color: darkGray; }");
    splitter_tabMainFileExplorer_SideBar->setOrientation(Qt::Vertical);  // 设置为垂直方向分割
    splitter_tabMainFileExplorer_SideBar->addWidget(widgetLeftSiderTop);
    splitter_tabMainFileExplorer_SideBar->addWidget(widgetLeftSiderBot);
    splitter_tabMainFileExplorer_SideBar->setHandleWidth(1);
    QHBoxLayout* layout_tabMainFileExplorerSideBar = new QHBoxLayout(widgetMainFileExplorerSideBar);
    layout_tabMainFileExplorerSideBar->addWidget(splitter_tabMainFileExplorer_SideBar);
}

void EPVS::createLeftSiderTopLayout(QWidget* widgetLeftSiderTop)
{
    
    // 创建布局管理器，常用文件夹
    QVBoxLayout* layout = new QVBoxLayout();
    widgetLeftSiderTop->setLayout(layout);
    // 创建常用文件夹列表
    common_folder_list = new QListWidgetCommonFolder(widgetLeftSiderTop);
    QObject::connect(common_folder_list, &QListWidgetCommonFolder::triggerQListWidgetCommonFolderStr, this, &EPVS::triggerQListWidgetCommonFolderStr_update);
    // 将子QListWidget添加到布局管理器中
    layout->addWidget(common_folder_list);
    
    
    /*QVBoxLayout* layout = new QVBoxLayout(widgetLeftSiderTop);
    QPushButton* pushButtonSiderTop = new QPushButton(widgetLeftSiderTop);
    QLabel* labelFileList = new QLabel(widgetLeftSiderTop);
    layout->addWidget(pushButtonSiderTop);
    layout->addWidget(labelFileList);*/
}

void EPVS::createLeftSiderBotLayout(QWidget* widgetLeftSiderBot)
{
    // 创建布局管理器，文件系统，树形结构
    QVBoxLayout* layout2 = new QVBoxLayout();
    widgetLeftSiderBot->setLayout(layout2);
    // 创建文件树视图
    file_tree_view = new QTreeView();
    file_tree_view->setStyleSheet("background-color: lightgray;");
    file_tree_view->setHeaderHidden(true);
    // 创建文件系统模型
    QFileSystemModel* file_system_model = new QFileSystemModel();
    file_system_model->setRootPath(QDir::rootPath());
    file_tree_view->setModel(file_system_model);
    // 隐藏文件类型和时间列
    file_tree_view->setColumnHidden(1, true);  // 文件类型列
    file_tree_view->setColumnHidden(2, true);  // 修改时间列
    file_tree_view->setColumnHidden(3, true);  // 修改时间列
    // 将子QListWidget添加到布局管理器中
    layout2->addWidget(file_tree_view);
}

//比图页面
void EPVS::createMainEPVSTab() {
    //tabMainEPVS
    tabMainEPVS = new QWidget();
    // 创建子部件
    createMainEPVSWidget(tabMainEPVS);

    tabWidget->addTab(tabMainEPVS, "");
    tabWidget->setTabText(tabWidget->indexOf(tabMainEPVS), "转图比对");

}

void EPVS::createMainEPVSWidget(QWidget* tabMainEPVS) {
    widget_vs_left = new QWidget(tabMainEPVS);
    widget_vs_left->setGeometry(0, 0, 901, 821);

    widget_vs_left_top = new QWidget(widget_vs_left);
    widget_vs_left_top->setGeometry(-1, -1, 901, 151);

    widget_vs_left_bot = new QWidget(widget_vs_left);
    widget_vs_left_bot->setGeometry(-1, 159, 901, 651);

    widget_vs_right = new QWidget(tabMainEPVS);
    widget_vs_right->setGeometry(910, 0, 221, 821);


    createMainEPVSLeftTopLayout(widget_vs_left_top);
    createMainEPVSLeftBotLayout(widget_vs_left_bot);
    createMainEPVSRightLayout(widget_vs_right);


    // 设置左边上下2个部分可以拖拽调整大小
    QSplitter* splitter_tabMainVS_left = new QSplitter();
    splitter_tabMainVS_left->setStyleSheet("QSplitter::handle { background-color: darkGray; }");
    splitter_tabMainVS_left->setOrientation(Qt::Vertical);  // 设置为垂直方向分割
    // 设置分割条的比例    
    splitter_tabMainVS_left->addWidget(widget_vs_left_top);
    splitter_tabMainVS_left->addWidget(widget_vs_left_bot);
    splitter_tabMainVS_left->setHandleWidth(1);
    QHBoxLayout* layout_tabMainVS_left = new QHBoxLayout(widget_vs_left);
    layout_tabMainVS_left->addWidget(splitter_tabMainVS_left);


    // 设置右边上下2个部分可以拖拽调整大小
    QSplitter* splitter_tabMainVS_right = new QSplitter();
    splitter_tabMainVS_right->setStyleSheet("QSplitter::handle { background-color: darkGray; }");
    splitter_tabMainVS_right->setOrientation(Qt::Vertical);  // 设置为垂直方向分割
    splitter_tabMainVS_right->addWidget(widget_vs_right_top);
    splitter_tabMainVS_right->addWidget(widget_vs_right_bot);
    splitter_tabMainVS_right->setHandleWidth(1);
    QHBoxLayout* layout_tabMainVS_right = new QHBoxLayout(widget_vs_right);
    layout_tabMainVS_right->addWidget(splitter_tabMainVS_right);


    // 设置左边主窗口与右窗口2个部分可以拖拽调整大小
    QSplitter* splitter_tabMainVs = new QSplitter();
    splitter_tabMainVs->setStyleSheet("QSplitter::handle { background-color: darkGray; }");
    splitter_tabMainVs->addWidget(widget_vs_left);
    splitter_tabMainVs->addWidget(widget_vs_right);
    splitter_tabMainVs->setHandleWidth(1);
    QHBoxLayout* layout_tabMainVs = new QHBoxLayout(tabMainEPVS);
    layout_tabMainVs->addWidget(splitter_tabMainVs);


}

void EPVS::createMainEPVSLeftTopLayout(QWidget* widget_vs_left_top) {

    QGroupBox* groupBoxJobA = new QGroupBox(widget_vs_left_top);
    groupBoxJobA->setTitle("料号A");
    groupBoxJobA->setGeometry(30, 0, 278, 139);
    groupBoxJobA->setAlignment(Qt::AlignCenter);
    QPushButton* pushButtonInputA = new QPushButton(groupBoxJobA);
    pushButtonInputA->setText("Input");
    pushButtonInputA->setGeometry(40, 50, 81, 31);
    QPushButton* pushButtonImportA = new QPushButton(groupBoxJobA);
    pushButtonImportA->setText("Import");
    pushButtonImportA->setGeometry(180, 50, 81, 31);
    QLabel* labelStatusJobA = new QLabel(groupBoxJobA);
    labelStatusJobA->setText("状态：");
    labelStatusJobA->setGeometry(10, 110, 171, 16);
    QPushButton* pushButtonJobAReset = new QPushButton(groupBoxJobA);
    pushButtonJobAReset->setText("重置A");
    pushButtonJobAReset->setGeometry(180, 100, 81, 31);

    QGroupBox* groupBoxJobB = new QGroupBox(widget_vs_left_top);
    groupBoxJobB->setTitle("料号B");
    groupBoxJobB->setGeometry(590, 0, 311, 139);
    groupBoxJobB->setAlignment(Qt::AlignCenter);
    QPushButton* pushButtonImportB = new QPushButton(groupBoxJobB);
    pushButtonImportB->setText("Import");
    pushButtonImportB->setGeometry(170, 50, 81, 31);
    QPushButton* pushButtonInputB = new QPushButton(groupBoxJobB);
    pushButtonInputB->setText("Input");
    pushButtonInputB->setGeometry(30, 50, 81, 31);
    QLabel* labelStatusJobB = new QLabel(groupBoxJobB);
    labelStatusJobB->setText("状态：");
    labelStatusJobB->setGeometry(10, 110, 161, 16);
    pushButtonJobBReset = new QPushButton(groupBoxJobB);
    pushButtonJobBReset->setText("重置B");
    pushButtonJobBReset->setGeometry(170, 100, 81, 31);

    QGroupBox* groupBoxVS = new QGroupBox(widget_vs_left_top);
    groupBoxVS->setTitle("比图");
    groupBoxVS->setGeometry(370, 0, 171, 131);
    groupBoxVS->setAlignment(Qt::AlignCenter);
    QPushButton* pushButtonVS = new QPushButton(groupBoxVS);
    pushButtonVS->setText("比图");
    pushButtonVS->setGeometry(30, 20, 116, 23);
    QComboBox* comboBoxVSMethod = new QComboBox(groupBoxVS);
    comboBoxVSMethod->setItemText(0, "方案1：G比图");
    comboBoxVSMethod->setItemText(1, "方案2：悦谱比图");
    comboBoxVSMethod->setGeometry(30, 64, 116, 20);
    comboBoxVSMethod->addItem("");
    comboBoxVSMethod->addItem("");
    QPushButton* pushButtonAllReset = new QPushButton(groupBoxVS);
    pushButtonAllReset->setText("重置所有");
    pushButtonAllReset->setGeometry(30, 105, 116, 23);


    // 创建布局管理器，VS左侧主窗口上部的按钮区域
    QHBoxLayout* layout_vs_left_top = new QHBoxLayout();
    widget_vs_left_top->setLayout(layout_vs_left_top);
    layout_vs_left_top->addWidget(groupBoxJobA);
    layout_vs_left_top->addWidget(groupBoxVS);
    layout_vs_left_top->addWidget(groupBoxJobB);

    //设置QgroupBox中的部件布局, 使得里面的部件大小可以随着窗口变化而自动调整
    // groupBoxJobA，创建一个网格布局
    QGridLayout* layout_groupBoxJobA = new QGridLayout(groupBoxJobA);
    layout_groupBoxJobA->addWidget(pushButtonInputA, 0, 0);
    layout_groupBoxJobA->addWidget(pushButtonImportA, 0, 1);
    layout_groupBoxJobA->addWidget(labelStatusJobA, 1, 0);
    layout_groupBoxJobA->addWidget(pushButtonJobAReset, 1, 1);
    // 设置布局中各个部件的间距
    layout_groupBoxJobA->setSpacing(10);

    // groupBoxVS，创建一个网格布局
    QGridLayout* layout_groupBoxVS = new QGridLayout(groupBoxVS);
    layout_groupBoxVS->addWidget(pushButtonVS, 0, 0);
    layout_groupBoxVS->addWidget(comboBoxVSMethod, 1, 0);
    layout_groupBoxVS->addWidget(pushButtonAllReset, 2, 0);
    // 设置布局中各个部件的间距
    layout_groupBoxVS->setSpacing(10);

    // groupBoxJobB，创建一个网格布局
    QGridLayout* layout_groupBoxJobB = new QGridLayout(groupBoxJobB);
    layout_groupBoxJobB->addWidget(pushButtonInputB, 0, 0);
    layout_groupBoxJobB->addWidget(pushButtonImportB, 0, 1);
    layout_groupBoxJobB->addWidget(labelStatusJobB, 1, 0);
    layout_groupBoxJobB->addWidget(pushButtonJobBReset, 1, 1);
    // 设置布局中各个部件的间距
    layout_groupBoxJobB->setSpacing(10);






}

void EPVS::createMainEPVSLeftBotLayout(QWidget* widget_vs_left_bot) {
    tableWidgetVS = new QTableWidget(widget_vs_left_bot);
    tableWidgetVS->setGeometry(10, 10, 891, 641);
    tableWidgetVS->setColumnCount(0);
    tableWidgetVS->setRowCount(0);

    // region 设置比对主表格
    QHBoxLayout* layout_vs_left_bot = new QHBoxLayout();
    widget_vs_left_bot->setLayout(layout_vs_left_bot);
    layout_vs_left_bot->addWidget(tableWidgetVS);
    tableWidgetVS->setRowCount(0);
    tableWidgetVS->setColumnCount(5);
    // 设置列标签
    QStringList column_labels = { "文件名", "料号A转图结果", "比图结果", "料号B转图结果", "说明" };
    tableWidgetVS->setHorizontalHeaderLabels(column_labels);
    // 设置固定宽度为多少像素
    tableWidgetVS->setColumnWidth(0, 200);
    tableWidgetVS->setColumnWidth(1, 100);
    tableWidgetVS->setColumnWidth(2, 300);
    tableWidgetVS->setColumnWidth(3, 100);
    tableWidgetVS->setColumnWidth(4, 200);
    // 设置表格的水平表头
    QHeaderView* header = tableWidgetVS->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::Stretch);
    // 设置列宽的比例
    QList<int> column_width_ratios = { 15, 15, 40, 15, 15 };
    set_column_width_ratios(tableWidgetVS, column_width_ratios);

}

void EPVS::set_column_width_ratios(QTableWidget* tableWidget, const QList<int>& ratios)
{
    int total_width = tableWidget->viewport()->width();
    QHeaderView* header = tableWidget->horizontalHeader();

    for (int i = 0; i < ratios.size(); ++i)
    {
        // 设置列为自动调整模式
        header->setSectionResizeMode(i, QHeaderView::Interactive);
        // 设置列宽为比例乘以总宽度
        int width = total_width * ratios[i] / 100;
        header->resizeSection(i, width);
    }

    // 最后一列设置为自动填充剩余空间
    header->setSectionResizeMode(ratios.size() - 1, QHeaderView::Stretch);
}

void EPVS::resizeEvent(QResizeEvent* event) {
    // 在主窗口大小变化时调整表格部件的大小    
    QWidget::resizeEvent(event);
    QList<int> column_width_ratios = { 15, 15, 40, 15, 15 };
    set_column_width_ratios(tableWidgetVS,column_width_ratios);
}


void EPVS::createMainEPVSRightLayout(QWidget* widget_vs_right) {
    widget_vs_right_top = new QWidget(widget_vs_right);
    widget_vs_right_top->setGeometry(0, 0, 221, 151);
    QPushButton* pushButtonHelp = new QPushButton(widget_vs_right_top);
    pushButtonHelp->setText("帮助");
    pushButtonHelp->setGeometry(140, 120, 75, 23);
    QPushButton* pushButtonLoadEPCAM = new QPushButton(widget_vs_right_top);
    pushButtonLoadEPCAM->setText("加载EPCAM");
    pushButtonLoadEPCAM->setGeometry(20, 10, 75, 21);
    QPushButton* pushButtonSettings = new QPushButton(widget_vs_right_top);
    pushButtonSettings->setText("配置");
    pushButtonSettings->setGeometry(140, 80, 75, 23);

    QPushButton* pushButtonSaveLocal = new QPushButton(widget_vs_right_top);
    pushButtonSaveLocal->setText("保存至本地");
    pushButtonSaveLocal->setGeometry(140, 50, 75, 23);

    QPushButton* pushButtonSaveDMS = new QPushButton(widget_vs_right_top);
    pushButtonSaveDMS->setText("保存至DMS");
    pushButtonSaveDMS->setGeometry(140, 10, 75, 23);

    // widget_vs_right_top，创建一个网格布局
    QGridLayout* layout_widget_vs_right_top = new QGridLayout(widget_vs_right_top);
    layout_widget_vs_right_top->addWidget(pushButtonLoadEPCAM, 0, 0);
    layout_widget_vs_right_top->addWidget(pushButtonSaveDMS, 0, 1);
    if (login_user_type != "dms") {
        pushButtonSaveDMS->setDisabled(true);
    }    
    layout_widget_vs_right_top->addWidget(pushButtonSaveLocal, 1, 1);
    layout_widget_vs_right_top->addWidget(pushButtonSettings, 2, 1);
    layout_widget_vs_right_top->addWidget(pushButtonHelp, 3, 1);
    // 设置布局中各个部件的间距
    layout_widget_vs_right_top->setSpacing(10);


    widget_vs_right_bot = new QWidget(widget_vs_right);
    widget_vs_right_bot->setGeometry(-1, 159, 221, 651);

    QTextBrowser* textBrowserMain = new QTextBrowser(widget_vs_right_bot);
    textBrowserMain->setGeometry(0, 10, 221, 631);
    QVBoxLayout* layout_widget_vs_right_bot = new QVBoxLayout(widget_vs_right_bot);
    layout_widget_vs_right_bot->addWidget(textBrowserMain);


    
}







void EPVS::triggerQListWidgetCommonFolderStr_update(const QString& message) {
    //qDebug() << "ccabc";
    int index = message.toInt();
    QListWidgetItem* item = common_folder_list->takeItem(index);
    delete item;
    common_folder_list->repaint();
    
    

}

void EPVS::on_goBackClicked()
{
    // 文件夹导航，后退
    if (!backHistory.empty()) {
        QString backFolder = backHistory.back();
        backHistory.pop_back();
        updateFolderContents(backFolder);
    }
}

void EPVS::on_goForwardClicked()
{
    // 文件夹导航，前进
    QString forwardFolder;
    if (!forwardHistory.empty()) {
        if (forwardHistory.size() > 0) {
            forwardFolder = forwardHistory.back();
            forwardHistory.pop_back();
        }
        if (forwardHistory.size() > 0) {
            forwardFolder = forwardHistory.back();
            forwardHistory.pop_back();
        }
        backHistory.push_back(currentFolder);  // 将当前文件夹路径添加到历史记录中
        currentFolder = forwardFolder;  // 更新当前文件夹路径
        updateFolderContents(forwardFolder);
    }
}

void EPVS::on_goUpClicked()
{
    // 文件夹导航，向上
    QString currentText = comboBoxMainFileExplorerPath->currentText();
    QString upFolder = QFileInfo(currentText).dir().path();

    updateFolderContents(upFolder);
}

void EPVS::on_commonFolderListItemClicked(QListWidgetItem* item)
{
    QString folder_name = item->text();
    
    // 设置自定义常用文件夹，从配置文件读取
    // 读取配置文件
    QFile file("settings/epvs.json");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QString file_contents = file.readAll();
        file.close();

        QJsonDocument json_doc = QJsonDocument::fromJson(file_contents.toUtf8());
        QJsonObject settings_dict = json_doc.object();
        QJsonObject general_dict = settings_dict["general"].toObject();
        QJsonObject common_folder_dict = general_dict["common_folder"].toObject();

        QString folder_path;

        if (folder_name == "桌面")
            folder_path = QDir::homePath() + "/Desktop";
        else if (folder_name == "下载")
            folder_path = QDir::homePath() + "/Downloads";
        else if (folder_name == "文档")
            folder_path = QDir::homePath() + "/Documents";
        else if (folder_name == "图片")
            folder_path = QDir::homePath() + "/Pictures";
        else if (folder_name == "音乐")
            folder_path = QDir::homePath() + "/Music";
        else if (folder_name == "视频")
            folder_path = QDir::homePath() + "/Videos";
        else if (!common_folder_dict.isEmpty())
        {
            for (auto it = common_folder_dict.constBegin(); it != common_folder_dict.constEnd(); ++it)
            {
                QString k = it.key();
                QString v = it.value().toString();
                if (folder_name == k)
                {
                    folder_path = v;
                    break;
                }
            }
        }
        else
        {
            return;
        }

        backHistory.push_back(currentFolder);  // 将当前文件夹路径添加到历史记录中
        currentFolder = folder_path;  // 更新当前文件夹路径
        updateFolderContents(folder_path);
    }
}

void EPVS::updateFolderContents(const QString& pathText) {
    // 更新文件夹视图
    QWidget* contentWidget = findChild<QWidget*>("content_widget");

    // 清空内容
    while (contentWidget->layout()->count() > 0) {
        QLayoutItem* child = contentWidget->layout()->takeAt(0);
        if (child->widget()) {
            child->widget()->deleteLater();
        }
        delete child;
    }

    // 创建文件夹内容部件
    QWidget* folderContentsWidget = new QWidget();
    QGridLayout* folderContentsLayout = new QGridLayout(folderContentsWidget);
    folderContentsLayout->setContentsMargins(10, 10, 10, 10);
    folderContentsLayout->setSpacing(10);

    folderListView = new ListViewFile(pathText);
    // 设置自定义委托来绘制文件名的自动换行
    FileNameDelegate* delegate = new FileNameDelegate(folderListView);
    folderListView->setItemDelegate(delegate);

    QObject::connect(folderListView, &ListViewFile::doubleClicked, this, &EPVS::on_folderSelectedDoubleClicked);
    
    connect(folderListView, &ListViewFile::triggerListViewFileStr, this, &EPVS::updateTriggerListViewFileStr);
    //connect(folderListView, &ListViewFile::triggerListViewFileStrVsInputA, this, &MyClass::updateTriggerListViewFileStrVsInputA);
    //connect(folderListView, &ListViewFile::triggerListViewFileStrVsInputB, this, &MyClass::updateTriggerListViewFileStrVsInputB);
    //connect(folderListView, &ListViewFile::triggerListViewFileStrSwitchTab, this, &MyClass::updateTriggerListViewFileStrSwitchTab);*/

    // 将文件夹内容部件添加到布局中
    folderContentsLayout->addWidget(folderListView);

    // 将文件夹内容部件设置为右边窗口B的子部件
    contentWidget->layout()->addWidget(folderContentsWidget);

    // 将当前文件夹路径添加到前进路径的历史记录
    forwardHistory.push_back(pathText);

    // 更新地址栏
     comboBoxMainFileExplorerPath->setCurrentText(pathText);

    folderListView->setPath(pathText);  // 更新path

    // 更新历史记录到地址栏    
    QStringList itemsList;
    std::copy_if(backHistory.begin(), backHistory.end(), std::back_inserter(itemsList),
        [](const QString& item) { return item.length() > 0; });
    QSet<QString> uniqueItemsSet = QSet<QString>::fromList(itemsList);
    itemsList = uniqueItemsSet.toList();

    comboBoxMainFileExplorerPath->clear();
    comboBoxMainFileExplorerPath->addItems(itemsList);
    // 更新地址栏
    comboBoxMainFileExplorerPath->setCurrentText(pathText);

    path = pathText;
}

void EPVS::on_folderSelectedDoubleClicked(const QModelIndex& index)
{
    //QFileSystemModel* folderModel = qobject_cast<QFileSystemModel*>(index.model());
    QFileSystemModel* folderModel = static_cast<QFileSystemModel*>(const_cast<QAbstractItemModel*>(index.model()));

    if (folderModel->isDir(index))
    {
        backHistory.push_back(currentFolder);  // 将当前文件夹路径添加到历史记录中
        forwardHistory.push_back(currentFolder);  // 将当前文件夹路径添加到 forward 记录中
        currentFolder = folderModel->filePath(index);  // 更新当前文件夹路径
        updateFolderContents(currentFolder);
    }
    else
    {
        // 处理选择的是文件的情况
        QString filePath = folderModel->filePath(index);
        QUrl url = QUrl::fromLocalFile(filePath);
        QDesktopServices::openUrl(url);
    }
}

void EPVS::on_comboBoxMainFileExplorerPath_activated() {
    updateFolderContents(comboBoxMainFileExplorerPath->currentText());
}

void EPVS::on_lineEditMainFileExplorerSearchReturnPressed()
{
    QString keyword = lineEditMainFileExplorerSearch->text();
    if (!keyword.isEmpty()) {
        QString search_path = comboBoxMainFileExplorerPath->currentText();        
        QStringList filePaths = QDir(search_path).entryList(QStringList() << "*" + keyword + "*", QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot, QDir::DirsFirst | QDir::IgnoreCase);

        /* 更新文件夹视图 */
        QWidget* content_widget = findChild<QWidget*>("content_widget");
        // 清空内容
        while (content_widget->layout()->count() > 0) {
            QLayoutItem* child = content_widget->layout()->takeAt(0);
            if (child->widget()) {
                child->widget()->deleteLater();
            }
        }

        // 创建文件夹内容部件
        QWidget* folder_contents_widget = new QWidget();
        QGridLayout* folder_contents_layout = new QGridLayout(folder_contents_widget);
        folder_contents_layout->setContentsMargins(10, 10, 10, 10);
        folder_contents_layout->setSpacing(10);


        QStringList modifiedList;

        // 使用迭代器遍历并修改字符串列表
        for (QStringList::const_iterator it = filePaths.begin(); it != filePaths.end(); ++it) {
            // 使用静态函数拼接路径
            QString modifiedString = QDir::cleanPath(QDir(path).filePath(*it));
            
            modifiedList.append(modifiedString);
        }

        


        folderListViewForList = new ListViewFileForList(modifiedList, this);

        connect(folderListViewForList, &ListViewFileForList::doubleClicked, this, &EPVS::searchResultSelected);

        // 将文件夹内容部件添加到布局中
        folder_contents_layout->addWidget(folderListViewForList);

        // 将文件夹内容部件设置为右边窗口B的子部件
        content_widget->layout()->addWidget(folder_contents_widget);
    }
    else {
        // 如果关键字为空，执行其他操作
        updateFolderContents(comboBoxMainFileExplorerPath->currentText());
    }
}

void EPVS::searchResultSelected(const QModelIndex& index)
{   
    
    // 选中文件夹
    QAbstractItemModel* abstractModel = folderListViewForList->model;
    QStandardItemModel* model = static_cast<QStandardItemModel*>(abstractModel);    
    QStandardItem* item = model->itemFromIndex(index);           
    QString pathStr = item->text();


    if (QDir(pathStr).exists()) {
        backHistory.push_back(currentFolder); // 将当前文件夹路径添加到历史记录中
        currentFolder = pathStr; // 更新当前文件夹路径
        updateFolderContents(currentFolder);
    }
    else {
        // 处理选择的是文件的情况
        QString filePath = pathStr;

        QUrl url = QUrl::fromLocalFile(filePath);
        QDesktopServices::openUrl(url);
    }
}


void EPVS::updateTriggerListViewFileStr(const QString& message){
    qDebug() << "outcc2" << message;
    QString str = message;
    QStringList splitList = str.split("|"); // 拆分字符串

    if (splitList.size() >= 2) {
        QString contentUsageType = splitList[0]; // 获取内容
        if (contentUsageType == "openFolder") {
            QString content = splitList[1];
            updateFolderContents(content);
        }
    }
    else {
        qDebug() << "Invalid input string.";
    }


}


void EPVS::setConnect() {
    //QObject::connect(pushButtonMainFileExplorerBack, SIGNAL(clicked()), this, SLOT(goBack()));
    QObject::connect(pushButtonMainFileExplorerBack, &QPushButton::clicked, this, &EPVS::on_goBackClicked);
    QObject::connect(pushButtonMainFileExplorerForward, SIGNAL(clicked()), this, SLOT(on_goForwardClicked()));
    QObject::connect(pushButtonMainFileExplorerUp, SIGNAL(clicked()), this, SLOT(on_goUpClicked()));
    QObject::connect(common_folder_list, &QListWidget::itemClicked, this, &EPVS::on_commonFolderListItemClicked);
    QObject::connect(file_tree_view, &QListView::clicked, this, &EPVS::on_folderSelectedDoubleClicked);
    connect(comboBoxMainFileExplorerPath, QOverload<int>::of(&QComboBox::activated), this, &EPVS::on_comboBoxMainFileExplorerPath_activated);
    connect(lineEditMainFileExplorerSearch, &QLineEdit::returnPressed, this, &EPVS::on_lineEditMainFileExplorerSearchReturnPressed);


    connect(pushButtonJobBReset, &QPushButton::clicked, this, &EPVS::on_buttonTestClicked);


}



void EPVS::closeEvent(QCloseEvent* event) {
    // 创建一个消息框
    QMessageBox messageBox(this);
    messageBox.setIcon(QMessageBox::Question);
    messageBox.setWindowTitle("确认退出");
    messageBox.setText("确定要退出吗？");

    // 添加确认和取消按钮
    QPushButton* confirmButton = messageBox.addButton("确认", QMessageBox::AcceptRole);
    QPushButton* cancelButton = messageBox.addButton("取消", QMessageBox::RejectRole);

    // 显示消息框，并等待用户响应
    messageBox.exec();

    // 判断用户点击的是哪个按钮
    if (messageBox.clickedButton() == confirmButton) {
        event->accept();
    }
    else {
        event->ignore();
    }
}


void EPVS::on_buttonTestClicked() {

    qDebug() << "ccout3";

    G* g = new G("C:/cc/python/epwork/epvs/config_g/bin/gateway.exe");
    //const char* str = R"(COM info,args=-t root -m display -d JOBS_LIST,out_file=\\vmware-host\Shared Folders\share\epvs\job_list.txt,write_mode=replace,units=inch)";
    QString cmd = R"(COM info,args=-t root -m display -d JOBS_LIST,out_file=\\vmware-host\Shared Folders\share\epvs\job_list.txt,write_mode=replace,units=inch)";
    int result = g->exec_cmd(cmd);
    qDebug().noquote() << "return type:" << result;


    int result2 = g->exec_cmd(cmd);
    qDebug().noquote() << "return2 type:" << result2;

}