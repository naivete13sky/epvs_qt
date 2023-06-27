#pragma execution_character_set("utf-8")
#include "../Include/EPVS.h"
#include <QTabWidget>
#include <QLineEdit>
#include <QPushButton>

EPVS::EPVS(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);



    setGeometry(100, 25, 1600, 1000);

    
    // 创建一个QWidget对象
    QWidget* centralWidget = new QWidget(this);

    // 设置QWidget的位置和大小
    centralWidget->setGeometry(100, 25, 1600, 1000);

    // 设置QWidget的背景颜色
    //centralWidget->setStyleSheet("background-color: red;");

    // 设置QWidget作为EPVS类的子部件
    setCentralWidget(centralWidget);

    // QTabWidget
    QTabWidget* tabWidget = new QTabWidget(centralWidget);
    tabWidget->setGeometry(10, 0, 1550, 950);
    tabWidget->setTabPosition(QTabWidget::West);

    //tabMainFileExplorer
    QWidget* tabMainFileExplorer = new QWidget();


    //tabMainFileExplorer--widget_fileExplorer_top
    QWidget* widget_fileExplorer_top = new QWidget(tabMainFileExplorer);
    widget_fileExplorer_top->setGeometry(0, 10, 1141, 31);
    // 搜索
    QWidget* lineEditMainFileExplorerSearch = new QLineEdit(widget_fileExplorer_top);
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
    tabWidget->addTab(tabMainEPVS, "");


    tabWidget->setTabText(tabWidget->indexOf(tabMainFileExplorer), "文件管理");
    tabWidget->setTabText(tabWidget->indexOf(tabMainEPVS), "转图比对");


}

EPVS::~EPVS()
{}
