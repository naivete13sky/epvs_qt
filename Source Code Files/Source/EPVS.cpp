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

EPVS::EPVS(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    setWindowTitle("����תͼ�ȶ�ϵͳ EPVS-V1.0");

    setGeometry(100, 25, 1600, 1000);

    
    // ����һ��QWidget����
    QWidget* centralWidget = new QWidget(this);

    // ����QWidget��λ�úʹ�С
    centralWidget->setGeometry(100, 25, 1600, 1000);

    // ����QWidget�ı�����ɫ
    //centralWidget->setStyleSheet("background-color: red;");

    // ����QWidget��ΪEPVS����Ӳ���
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
    // ����
    QWidget* lineEditMainFileExplorerSearch = new QLineEdit(widget_fileExplorer_top);
    lineEditMainFileExplorerSearch->setGeometry(880, 0, 241, 20);
    // ǰ��
    QPushButton* pushButtonMainFileExplorerForward = new QPushButton(widget_fileExplorer_top);
    pushButtonMainFileExplorerForward->setGeometry(90, 0, 75, 23);
    pushButtonMainFileExplorerForward->setText("ǰ��");
    // ����
    QPushButton* pushButtonMainFileExplorerUp = new QPushButton(widget_fileExplorer_top);
    pushButtonMainFileExplorerUp->setGeometry(180, 0, 75, 23);
    pushButtonMainFileExplorerUp->setText("�ϼ�");
    // ����
    QPushButton* pushButtonMainFileExplorerBack = new QPushButton(widget_fileExplorer_top);
    pushButtonMainFileExplorerBack->setGeometry(0, 0, 75, 23);
    pushButtonMainFileExplorerBack->setText("����");

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
    groupBoxJobA->setTitle("�Ϻ�A");
    groupBoxJobA->setGeometry(30, 0, 278, 139);
    groupBoxJobA->setAlignment(Qt::AlignCenter);
    QPushButton* pushButtonInputA = new QPushButton(groupBoxJobA);
    pushButtonInputA->setText("Input");
    pushButtonInputA->setGeometry(40, 50, 81, 31);
    QPushButton* pushButtonImportA = new QPushButton(groupBoxJobA);
    pushButtonImportA->setText("Import");
    pushButtonImportA->setGeometry(180, 50, 81, 31);
    QLabel* labelStatusJobA = new QLabel(groupBoxJobA);
    labelStatusJobA->setText("״̬��");
    labelStatusJobA->setGeometry(10, 110, 171, 16);
    QPushButton* pushButtonJobAReset = new QPushButton(groupBoxJobA);
    pushButtonJobAReset->setText("����A");
    pushButtonJobAReset->setGeometry(180, 100, 81, 31);

    QGroupBox* groupBoxJobB = new QGroupBox(widget_vs_left_top);
    groupBoxJobB->setTitle("�Ϻ�B");
    groupBoxJobB->setGeometry(590, 0, 311, 139);
    groupBoxJobB->setAlignment(Qt::AlignCenter);
    QPushButton* pushButtonImportB = new QPushButton(groupBoxJobB);
    pushButtonImportB->setText("Import");
    pushButtonImportB->setGeometry(170, 50, 81, 31);
    QPushButton* pushButtonInputB = new QPushButton(groupBoxJobB);
    pushButtonInputB->setText("Input");
    pushButtonInputB->setGeometry(30, 50, 81, 31);
    QLabel* labelStatusJobB = new QLabel(groupBoxJobB);
    labelStatusJobB->setText("״̬��");
    labelStatusJobB->setGeometry(10, 110, 161, 16);
    QPushButton* pushButtonJobBReset = new QPushButton(groupBoxJobB);
    pushButtonJobBReset->setText("����B");
    pushButtonJobBReset->setGeometry(170, 100, 81, 31);

    QGroupBox* groupBoxVS = new QGroupBox(widget_vs_left_top);
    groupBoxVS->setTitle("��ͼ");
    groupBoxVS->setGeometry(370, 0, 171, 131);
    groupBoxVS->setAlignment(Qt::AlignCenter);
    QPushButton* pushButtonVS = new QPushButton(groupBoxVS);
    pushButtonVS->setText("��ͼ");
    pushButtonVS->setGeometry(30, 20, 116, 23);
    QComboBox* comboBoxVSMethod = new QComboBox(groupBoxVS);
    comboBoxVSMethod->setItemText(0, "����1��G��ͼ");
    comboBoxVSMethod->setItemText(1, "����2�����ױ�ͼ");
    comboBoxVSMethod->setGeometry(30, 64, 116, 20);
    comboBoxVSMethod->addItem("");
    comboBoxVSMethod->addItem("");
    QPushButton* pushButtonAllReset = new QPushButton(groupBoxVS);
    pushButtonAllReset->setText("��������");
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
    pushButtonHelp->setText("����");
    pushButtonHelp->setGeometry(140, 120, 75, 23);
    QPushButton* pushButtonLoadEPCAM = new QPushButton(widget_vs_right_top);
    pushButtonLoadEPCAM->setText("����EPCAM");
    pushButtonLoadEPCAM->setGeometry(20, 10, 75, 21);
    QPushButton* pushButtonSettings = new QPushButton(widget_vs_right_top);
    pushButtonSettings->setText("����");
    pushButtonSettings->setGeometry(140, 80, 75, 23);

    QPushButton* pushButtonSaveLocal = new QPushButton(widget_vs_right_top);
    pushButtonSaveLocal->setText("����������");
    pushButtonSaveLocal->setGeometry(140, 50, 75, 23);

    QPushButton* pushButtonSaveDMS = new QPushButton(widget_vs_right_top);
    pushButtonSaveDMS->setText("������DMS");
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





    tabWidget->setTabText(tabWidget->indexOf(tabMainFileExplorer), "�ļ�����");
    tabWidget->setTabText(tabWidget->indexOf(tabMainEPVS), "תͼ�ȶ�");


    tabWidget->setCurrentIndex(0);



}

EPVS::~EPVS()
{}