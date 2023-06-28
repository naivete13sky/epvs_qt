#pragma execution_character_set("utf-8")
#include "../Include/EPVS.h"
#include <QTabWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QGroupBox>
#include <QLabel>
#include <QComboBox>
#include <QTableWidget>
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
#include "../Include/ListViewFile.h"
#include "../Include/FileNameDelegate.h"
#include <Filter.h>
#include <QModelIndex>



EPVS::EPVS(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    setWindowTitle("悦谱转图比对系统 EPVS-V1.0");
    setGeometry(200, 35, 1200, 900);
        
    // 创建一个QWidget对象
    QWidget* centralWidget = new QWidget(this);
    // 设置QWidget的位置和大小
    centralWidget->setGeometry(200, 35, 1600, 1000);
    // 设置QWidget的背景颜色
    //centralWidget->setStyleSheet("background-color: red;");
    // 设置QWidget作为EPVS类的子部件
    setCentralWidget(centralWidget);

    // QTabWidget
    QTabWidget* tabWidget = new QTabWidget(centralWidget);
    tabWidget->setGeometry(10, 0, 1550, 950);
    tabWidget->setTabPosition(QTabWidget::West);

    //tabMainFileExplorer
    currentFolder = "";  // 当前所选文件夹的路径
    backHistory.clear();  // 文件夹路径的历史记录
    forwardHistory.clear();  // 前进路径的历史记录

    QWidget* tabMainFileExplorer = new QWidget();
    //tabMainFileExplorer--widget_fileExplorer_top
    QWidget* widget_fileExplorer_top = new QWidget(tabMainFileExplorer);
    widget_fileExplorer_top->setGeometry(0, 10, 1141, 31);
    // 搜索
    QLineEdit* lineEditMainFileExplorerSearch = new QLineEdit(widget_fileExplorer_top);
    lineEditMainFileExplorerSearch->setGeometry(880, 0, 241, 20);
    // 前进
    QPushButton* pushButtonMainFileExplorerForward = new QPushButton(widget_fileExplorer_top);
    pushButtonMainFileExplorerForward->setGeometry(90, 0, 75, 23);
    pushButtonMainFileExplorerForward->setText("前进");
    // 向上
    QPushButton* pushButtonMainFileExplorerUp = new QPushButton(widget_fileExplorer_top);
    pushButtonMainFileExplorerUp->setGeometry(180, 0, 75, 23);
    pushButtonMainFileExplorerUp->setText("上级");
    // 回退
    QPushButton* pushButtonMainFileExplorerBack = new QPushButton(widget_fileExplorer_top);
    pushButtonMainFileExplorerBack->setGeometry(0, 0, 75, 23);
    pushButtonMainFileExplorerBack->setText("后退");

    //tabMainFileExplorer--widget_fileExplorer_bot
    QWidget* widget_fileExplorer_bot = new QWidget(tabMainFileExplorer);
    widget_fileExplorer_bot->setGeometry(-1, 59, 1141, 751);
    //tabMainFileExplorer--widget_fileExplorer_bot--widgetMainFileExplorerRightMain
    QWidget* widgetMainFileExplorerRightMain = new QWidget(widget_fileExplorer_bot);
    widgetMainFileExplorerRightMain->setGeometry(260, 0, 881, 781);
    //tabMainFileExplorer--widget_fileExplorer_bot--widgetMainFileExplorerSideBar
    QWidget* widgetMainFileExplorerSideBar = new QWidget(widget_fileExplorer_bot);
    widgetMainFileExplorerSideBar->setGeometry(0, 0, 251, 781);
    //tabMainFileExplorer--widget_fileExplorer_bot--widgetMainFileExplorerSideBar--widgetLeftSiderTop
    QWidget* widgetLeftSiderTop = new QWidget(widgetMainFileExplorerSideBar);
    widgetLeftSiderTop->setGeometry(0, 0, 231, 331);
    //tabMainFileExplorer--widget_fileExplorer_bot--widgetMainFileExplorerSideBar--widgetLeftSiderBot
    QWidget* widgetLeftSiderBot = new QWidget(widgetMainFileExplorerSideBar);
    widgetLeftSiderBot->setGeometry(0, 340, 231, 351);

    tabWidget->addTab(tabMainFileExplorer, "");


    //tabMainEPVS
    QWidget* tabMainEPVS = new QWidget();
    QWidget* widget_vs_left = new QWidget(tabMainEPVS);
    widget_vs_left->setGeometry(0, 0, 901, 821);
    QWidget* widget_vs_left_top = new QWidget(widget_vs_left);
    widget_vs_left_top->setGeometry(-1, -1, 901, 151);
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
    QPushButton* pushButtonJobBReset = new QPushButton(groupBoxJobB);
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

    QWidget* widget_vs_left_bot = new QWidget(widget_vs_left);
    widget_vs_left_bot->setGeometry(-1, 159, 901, 651);
    QTableWidget* tableWidgetVS = new QTableWidget(widget_vs_left_bot);
    tableWidgetVS->setGeometry(10, 10, 891, 641);
    tableWidgetVS->setColumnCount(0);
    tableWidgetVS->setRowCount(0);
    QWidget* widget_vs_right = new QWidget(tabMainEPVS);
    widget_vs_right->setGeometry(910, 0, 221, 821);

    QWidget* widget_vs_right_top = new QWidget(widget_vs_right);
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

    QWidget* widget_vs_right_bot = new QWidget(widget_vs_right);
    widget_vs_right_bot->setGeometry(-1, 159, 221, 651);

    QTextBrowser* textBrowserMain = new QTextBrowser(widget_vs_right_bot);
    textBrowserMain->setGeometry(0, 10, 221, 631);

    tabWidget->addTab(tabMainEPVS, "");

    setCentralWidget(centralWidget);
    QMenuBar* menubar = new QMenuBar(this);
    menubar->setGeometry(0, 0, 1179, 23);
    setMenuBar(menubar);
    QStatusBar* statusbar = new QStatusBar(this);
    statusbar->setObjectName("statusbar");
    setStatusBar(statusbar);

    tabWidget->setTabText(tabWidget->indexOf(tabMainFileExplorer), "文件管理");
    tabWidget->setTabText(tabWidget->indexOf(tabMainEPVS), "转图比对");

    tabWidget->setCurrentIndex(0);


    //为了使得tab widget随着主窗口大小变化跟着调整, 需要设置一下layout。
    QVBoxLayout* layout_main = new QVBoxLayout();
    //将Tab Widget放置在布局管理器中
    layout_main->addWidget(tabWidget);
    //创建一个容器窗口部件
    QWidget* central_widget = new QWidget();
    //将布局管理器设置为容器窗口部件的布局
    central_widget->setLayout(layout_main);
    //将容器窗口部件设置为主窗口的中央部件
    setCentralWidget(central_widget);


    // 创建布局管理器，常用文件夹
    QVBoxLayout* layout = new QVBoxLayout();
    widgetLeftSiderTop->setLayout(layout);
    // 创建常用文件夹列表
    common_folder_list = new QListWidgetCommonFolder(widgetLeftSiderTop);    
    QObject::connect(common_folder_list, &QListWidgetCommonFolder::triggerQListWidgetCommonFolderStr, this, &EPVS::triggerQListWidgetCommonFolderStr_update);
    // 将子QListWidget添加到布局管理器中
    layout->addWidget(common_folder_list);


    // 创建布局管理器，文件系统，树形结构
    QVBoxLayout* layout2 = new QVBoxLayout();
    widgetLeftSiderBot->setLayout(layout2);
    // 创建文件树视图
    QTreeView* file_tree_view = new QTreeView();
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


    // 设置top里的多个部分可以拖拽调整大小
    QSplitter* splitter_tabMainFileExplorer_top = new QSplitter();
    splitter_tabMainFileExplorer_top->setStyleSheet("QSplitter::handle { background-color: darkGray; }");
    splitter_tabMainFileExplorer_top->addWidget(pushButtonMainFileExplorerBack);
    splitter_tabMainFileExplorer_top->addWidget(pushButtonMainFileExplorerForward);
    splitter_tabMainFileExplorer_top->addWidget(pushButtonMainFileExplorerUp);
    splitter_tabMainFileExplorer_top->setHandleWidth(1);


    // Qt设计师画的Qcombox没有回车事件，为了实现这个效果，需要自己写一个类来实现，这在个类中重写keyPressEvent方法
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

    
    // 设置底部的侧边栏与右边主窗口2个部分可以拖拽调整大小
    QSplitter* splitter_tabMainFileExplorer_bot = new QSplitter();
    splitter_tabMainFileExplorer_bot->setStyleSheet("QSplitter::handle { background-color: darkGray; }");
    splitter_tabMainFileExplorer_bot->addWidget(widgetMainFileExplorerSideBar);
    splitter_tabMainFileExplorer_bot->addWidget(widgetMainFileExplorerRightMain);
    splitter_tabMainFileExplorer_bot->setHandleWidth(1);        
    QHBoxLayout* layout_tabMainFileExplorerBot = new QHBoxLayout(widget_fileExplorer_bot);
    layout_tabMainFileExplorerBot->addWidget(splitter_tabMainFileExplorer_bot);


    // 设置侧边栏上下2个部分可以拖拽调整大小
    QSplitter* splitter_tabMainFileExplorer_SideBar = new QSplitter();
    splitter_tabMainFileExplorer_SideBar->setStyleSheet("QSplitter::handle { background-color: darkGray; }");
    splitter_tabMainFileExplorer_SideBar->setOrientation(Qt::Vertical);  // 设置为垂直方向分割
    splitter_tabMainFileExplorer_SideBar->addWidget(widgetLeftSiderTop);
    splitter_tabMainFileExplorer_SideBar->addWidget(widgetLeftSiderBot);
    splitter_tabMainFileExplorer_SideBar->setHandleWidth(1);
    QHBoxLayout* layout_tabMainFileExplorerSideBar = new QHBoxLayout(widgetMainFileExplorerSideBar);
    layout_tabMainFileExplorerSideBar->addWidget(splitter_tabMainFileExplorer_SideBar);


    // 设置搜索栏
    lineEditMainFileExplorerSearch->setPlaceholderText("搜索");


    
    //QObject::connect(pushButtonMainFileExplorerBack, SIGNAL(clicked()), this, SLOT(goBack()));
    QObject::connect(pushButtonMainFileExplorerBack, &QPushButton::clicked, this, &EPVS::goBack);
    QObject::connect(pushButtonMainFileExplorerForward, SIGNAL(clicked()), this, SLOT(goForward()));
    QObject::connect(pushButtonMainFileExplorerUp, SIGNAL(clicked()), this, SLOT(goUp()));
    QObject::connect(common_folder_list, &QListWidget::itemClicked, this,&EPVS::on_commonFolderListItemClicked);
    QObject::connect(file_tree_view, &QListView::clicked, this, &EPVS::on_folderSelectedDoubleClicked);


}

EPVS::~EPVS()
{}



void EPVS::triggerQListWidgetCommonFolderStr_update(const QString& message) {
    //qDebug() << "ccabc";
    int index = message.toInt();
    QListWidgetItem* item = common_folder_list->takeItem(index);
    delete item;
    common_folder_list->repaint();
    
    

}
    

void EPVS::goBack()
{
    // 文件夹导航，后退
    if (!backHistory.empty()) {
        QString backFolder = backHistory.back();
        backHistory.pop_back();
        updateFolderContents(backFolder);
    }
}


void EPVS::goForward()
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


void EPVS::goUp()
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


void EPVS::updateFolderContents(const QString& path) {
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

    ListViewFile* folderListView = new ListViewFile(path);
    // 设置自定义委托来绘制文件名的自动换行
    FileNameDelegate* delegate = new FileNameDelegate(folderListView);
    folderListView->setItemDelegate(delegate);

    QObject::connect(folderListView, &ListViewFile::doubleClicked, this, &EPVS::on_folderSelectedDoubleClicked);
    
    ///*connect(folderListView, &ListViewFile::triggerListViewFileStr, this, &MyClass::updateTriggerListViewFileStr);
    //connect(folderListView, &ListViewFile::triggerListViewFileStrVsInputA, this, &MyClass::updateTriggerListViewFileStrVsInputA);
    //connect(folderListView, &ListViewFile::triggerListViewFileStrVsInputB, this, &MyClass::updateTriggerListViewFileStrVsInputB);
    //connect(folderListView, &ListViewFile::triggerListViewFileStrSwitchTab, this, &MyClass::updateTriggerListViewFileStrSwitchTab);*/

    // 将文件夹内容部件添加到布局中
    folderContentsLayout->addWidget(folderListView);

    // 将文件夹内容部件设置为右边窗口B的子部件
    contentWidget->layout()->addWidget(folderContentsWidget);

    // 将当前文件夹路径添加到前进路径的历史记录
    forwardHistory.push_back(path);

    // 更新地址栏
     comboBoxMainFileExplorerPath->setCurrentText(path);

    //folderListView->setPath(path);  // 更新path

    // 更新历史记录到地址栏
    //QStringList itemsList = back_history.filter([](const QString& item) { return item.length() > 0; }).toSet().toList();
    comboBoxMainFileExplorerPath->clear();
    //comboBoxMainFileExplorerPath->addItems(itemsList);
    // 更新地址栏
    comboBoxMainFileExplorerPath->setCurrentText(path);
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
