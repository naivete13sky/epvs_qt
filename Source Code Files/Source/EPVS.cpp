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
    //UI����
    ui.setupUi(this);
    setWindowTitle("����תͼ�ȶ�ϵͳ EPVS-V1.0");
    setGeometry(200, 35, 1300, 900);
    
    initPublicVariable();//��ʼ����������
    createCentralWidget();//���������ڲ���
    createQTabWidget();//�������з���QTabWidget������
    createMainFileExplorerTab();//���tabҳ��--�ļ�����     
    createMainEPVSTab();//���tabҳ��--���ױ�ͼ
                  
    setConnect();//�����źŲ�

}

EPVS::~EPVS()
{}


void EPVS::initPublicVariable() {
    currentFolder = "";  // ��ǰ��ѡ�ļ��е�·��
    backHistory.clear();  // �ļ���·������ʷ��¼
    forwardHistory.clear();  // ǰ��·������ʷ��¼

}

void EPVS::createCentralWidget()
{
    centralWidget = new QWidget(this);// ����һ��QWidget����
    centralWidget->setGeometry(0, 35, 1600, 1000);// ����QWidget��λ�úʹ�С    
    centralWidget->setStyleSheet("background-color: red;");// ����QWidget�ı�����ɫ
    setCentralWidget(centralWidget);// ����QWidget��ΪEPVS����Ӳ���


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

    //Ϊ��ʹ��tabWidget���������ڴ�С�仯���ŵ���, ��Ҫ����һ��layout��
    layout_main = new QVBoxLayout();
    //��Tab Widget�����ڲ��ֹ�������
    layout_main->addWidget(tabWidget);
    //����һ���������ڲ���
    centralwidgetTabWidget = new QWidget();
    //�����ֹ���������Ϊ�������ڲ����Ĳ���
    centralwidgetTabWidget->setLayout(layout_main);
    //���������ڲ�������Ϊ�����ڵ����벿��
    setCentralWidget(centralwidgetTabWidget);


    


}

//�ļ�����ҳ��
void EPVS::createMainFileExplorerTab()
{
    tabMainFileExplorer = new QWidget();
    // �����ļ�������Ӳ���
    createMainFileExplorerWidget(tabMainFileExplorer);
    
    

    // ����top�� bot 2�����ֿ�����ק������С
    QSplitter* splitter_tabMainFileExplorer_top_bot = new QSplitter();
    splitter_tabMainFileExplorer_top_bot->setStyleSheet("QSplitter::handle { background-color: darkGray; }");
    // �����ֱ����Ϊ1������
    splitter_tabMainFileExplorer_top_bot->setHandleWidth(1);
    splitter_tabMainFileExplorer_top_bot->setOrientation(Qt::Vertical);  // ����Ϊ��ֱ����ָ�
    splitter_tabMainFileExplorer_top_bot->addWidget(widget_fileExplorer_top);
    splitter_tabMainFileExplorer_top_bot->addWidget(widget_fileExplorer_bot);
    QHBoxLayout* layout_tabMainFileExplorer = new QHBoxLayout(tabMainFileExplorer);
    layout_tabMainFileExplorer->addWidget(splitter_tabMainFileExplorer_top_bot);
    
    
    
    // ��ӵ�Tab Widget��
    tabWidget->addTab(tabMainFileExplorer, "");
    tabWidget->setTabText(tabWidget->indexOf(tabMainFileExplorer), "�ļ�����");

    // ����tabWidgetΪ��ǰ�Tab
    tabWidget->setCurrentIndex(0);
}

void EPVS::createMainFileExplorerWidget(QWidget* tabMainFileExplorer)
{
    // �����ļ�������Ӳ���
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


    // ��Ӳ��ֺͿؼ��������Ӳ�����
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
    lineEditMainFileExplorerSearch->setPlaceholderText("����");
    pushButtonMainFileExplorerForward = new QPushButton(widget_fileExplorer_top);
    pushButtonMainFileExplorerForward->setGeometry(90, 0, 75, 23);
    pushButtonMainFileExplorerForward->setText("ǰ��");
    pushButtonMainFileExplorerUp = new QPushButton(widget_fileExplorer_top);
    pushButtonMainFileExplorerUp->setGeometry(180, 0, 75, 23);
    pushButtonMainFileExplorerUp->setText("�ϼ�");
    pushButtonMainFileExplorerBack = new QPushButton(widget_fileExplorer_top);
    pushButtonMainFileExplorerBack->setGeometry(0, 0, 75, 23);
    pushButtonMainFileExplorerBack->setText("����");
    

    // ����top��Ķ�����ֿ�����ק������С
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
    // ���õײ��Ĳ�������ұ�������2�����ֿ�����ק������С
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
    // �������ֹ��������Ҳ�������
    QVBoxLayout* layout3 = new QVBoxLayout();
    widgetMainFileExplorerRightMain->setLayout(layout3);
    // �������崰��B����
    QWidget* content_widget = new QWidget();
    content_widget->setStyleSheet("background-color: white;");
    content_widget->setObjectName("content_widget");
    QGridLayout* content_layout = new QGridLayout(content_widget);
    content_widget->setLayout(content_layout);
    layout3->addWidget(content_widget);

}

void EPVS::createMainFileExplorerSideBarLayout(QWidget* widgetMainFileExplorerSideBar)
{
    // ���ò��������2�����ֿ�����ק������С
    QSplitter* splitter_tabMainFileExplorer_SideBar = new QSplitter();
    splitter_tabMainFileExplorer_SideBar->setStyleSheet("QSplitter::handle { background-color: darkGray; }");
    splitter_tabMainFileExplorer_SideBar->setOrientation(Qt::Vertical);  // ����Ϊ��ֱ����ָ�
    splitter_tabMainFileExplorer_SideBar->addWidget(widgetLeftSiderTop);
    splitter_tabMainFileExplorer_SideBar->addWidget(widgetLeftSiderBot);
    splitter_tabMainFileExplorer_SideBar->setHandleWidth(1);
    QHBoxLayout* layout_tabMainFileExplorerSideBar = new QHBoxLayout(widgetMainFileExplorerSideBar);
    layout_tabMainFileExplorerSideBar->addWidget(splitter_tabMainFileExplorer_SideBar);
}

void EPVS::createLeftSiderTopLayout(QWidget* widgetLeftSiderTop)
{
    
    // �������ֹ������������ļ���
    QVBoxLayout* layout = new QVBoxLayout();
    widgetLeftSiderTop->setLayout(layout);
    // ���������ļ����б�
    common_folder_list = new QListWidgetCommonFolder(widgetLeftSiderTop);
    QObject::connect(common_folder_list, &QListWidgetCommonFolder::triggerQListWidgetCommonFolderStr, this, &EPVS::triggerQListWidgetCommonFolderStr_update);
    // ����QListWidget��ӵ����ֹ�������
    layout->addWidget(common_folder_list);
    
    
    /*QVBoxLayout* layout = new QVBoxLayout(widgetLeftSiderTop);
    QPushButton* pushButtonSiderTop = new QPushButton(widgetLeftSiderTop);
    QLabel* labelFileList = new QLabel(widgetLeftSiderTop);
    layout->addWidget(pushButtonSiderTop);
    layout->addWidget(labelFileList);*/
}

void EPVS::createLeftSiderBotLayout(QWidget* widgetLeftSiderBot)
{
    // �������ֹ��������ļ�ϵͳ�����νṹ
    QVBoxLayout* layout2 = new QVBoxLayout();
    widgetLeftSiderBot->setLayout(layout2);
    // �����ļ�����ͼ
    file_tree_view = new QTreeView();
    file_tree_view->setStyleSheet("background-color: lightgray;");
    file_tree_view->setHeaderHidden(true);
    // �����ļ�ϵͳģ��
    QFileSystemModel* file_system_model = new QFileSystemModel();
    file_system_model->setRootPath(QDir::rootPath());
    file_tree_view->setModel(file_system_model);
    // �����ļ����ͺ�ʱ����
    file_tree_view->setColumnHidden(1, true);  // �ļ�������
    file_tree_view->setColumnHidden(2, true);  // �޸�ʱ����
    file_tree_view->setColumnHidden(3, true);  // �޸�ʱ����
    // ����QListWidget��ӵ����ֹ�������
    layout2->addWidget(file_tree_view);
}

//��ͼҳ��
void EPVS::createMainEPVSTab() {
    //tabMainEPVS
    tabMainEPVS = new QWidget();
    // �����Ӳ���
    createMainEPVSWidget(tabMainEPVS);

    tabWidget->addTab(tabMainEPVS, "");
    tabWidget->setTabText(tabWidget->indexOf(tabMainEPVS), "תͼ�ȶ�");

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


    // �����������2�����ֿ�����ק������С
    QSplitter* splitter_tabMainVS_left = new QSplitter();
    splitter_tabMainVS_left->setStyleSheet("QSplitter::handle { background-color: darkGray; }");
    splitter_tabMainVS_left->setOrientation(Qt::Vertical);  // ����Ϊ��ֱ����ָ�
    // ���÷ָ����ı���    
    splitter_tabMainVS_left->addWidget(widget_vs_left_top);
    splitter_tabMainVS_left->addWidget(widget_vs_left_bot);
    splitter_tabMainVS_left->setHandleWidth(1);
    QHBoxLayout* layout_tabMainVS_left = new QHBoxLayout(widget_vs_left);
    layout_tabMainVS_left->addWidget(splitter_tabMainVS_left);


    // �����ұ�����2�����ֿ�����ק������С
    QSplitter* splitter_tabMainVS_right = new QSplitter();
    splitter_tabMainVS_right->setStyleSheet("QSplitter::handle { background-color: darkGray; }");
    splitter_tabMainVS_right->setOrientation(Qt::Vertical);  // ����Ϊ��ֱ����ָ�
    splitter_tabMainVS_right->addWidget(widget_vs_right_top);
    splitter_tabMainVS_right->addWidget(widget_vs_right_bot);
    splitter_tabMainVS_right->setHandleWidth(1);
    QHBoxLayout* layout_tabMainVS_right = new QHBoxLayout(widget_vs_right);
    layout_tabMainVS_right->addWidget(splitter_tabMainVS_right);


    // ����������������Ҵ���2�����ֿ�����ק������С
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
    pushButtonJobBReset = new QPushButton(groupBoxJobB);
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


    // �������ֹ�������VS����������ϲ��İ�ť����
    QHBoxLayout* layout_vs_left_top = new QHBoxLayout();
    widget_vs_left_top->setLayout(layout_vs_left_top);
    layout_vs_left_top->addWidget(groupBoxJobA);
    layout_vs_left_top->addWidget(groupBoxVS);
    layout_vs_left_top->addWidget(groupBoxJobB);

    //����QgroupBox�еĲ�������, ʹ������Ĳ�����С�������Ŵ��ڱ仯���Զ�����
    // groupBoxJobA������һ�����񲼾�
    QGridLayout* layout_groupBoxJobA = new QGridLayout(groupBoxJobA);
    layout_groupBoxJobA->addWidget(pushButtonInputA, 0, 0);
    layout_groupBoxJobA->addWidget(pushButtonImportA, 0, 1);
    layout_groupBoxJobA->addWidget(labelStatusJobA, 1, 0);
    layout_groupBoxJobA->addWidget(pushButtonJobAReset, 1, 1);
    // ���ò����и��������ļ��
    layout_groupBoxJobA->setSpacing(10);

    // groupBoxVS������һ�����񲼾�
    QGridLayout* layout_groupBoxVS = new QGridLayout(groupBoxVS);
    layout_groupBoxVS->addWidget(pushButtonVS, 0, 0);
    layout_groupBoxVS->addWidget(comboBoxVSMethod, 1, 0);
    layout_groupBoxVS->addWidget(pushButtonAllReset, 2, 0);
    // ���ò����и��������ļ��
    layout_groupBoxVS->setSpacing(10);

    // groupBoxJobB������һ�����񲼾�
    QGridLayout* layout_groupBoxJobB = new QGridLayout(groupBoxJobB);
    layout_groupBoxJobB->addWidget(pushButtonInputB, 0, 0);
    layout_groupBoxJobB->addWidget(pushButtonImportB, 0, 1);
    layout_groupBoxJobB->addWidget(labelStatusJobB, 1, 0);
    layout_groupBoxJobB->addWidget(pushButtonJobBReset, 1, 1);
    // ���ò����и��������ļ��
    layout_groupBoxJobB->setSpacing(10);






}

void EPVS::createMainEPVSLeftBotLayout(QWidget* widget_vs_left_bot) {
    tableWidgetVS = new QTableWidget(widget_vs_left_bot);
    tableWidgetVS->setGeometry(10, 10, 891, 641);
    tableWidgetVS->setColumnCount(0);
    tableWidgetVS->setRowCount(0);

    // region ���ñȶ������
    QHBoxLayout* layout_vs_left_bot = new QHBoxLayout();
    widget_vs_left_bot->setLayout(layout_vs_left_bot);
    layout_vs_left_bot->addWidget(tableWidgetVS);
    tableWidgetVS->setRowCount(0);
    tableWidgetVS->setColumnCount(5);
    // �����б�ǩ
    QStringList column_labels = { "�ļ���", "�Ϻ�Aתͼ���", "��ͼ���", "�Ϻ�Bתͼ���", "˵��" };
    tableWidgetVS->setHorizontalHeaderLabels(column_labels);
    // ���ù̶����Ϊ��������
    tableWidgetVS->setColumnWidth(0, 200);
    tableWidgetVS->setColumnWidth(1, 100);
    tableWidgetVS->setColumnWidth(2, 300);
    tableWidgetVS->setColumnWidth(3, 100);
    tableWidgetVS->setColumnWidth(4, 200);
    // ���ñ���ˮƽ��ͷ
    QHeaderView* header = tableWidgetVS->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::Stretch);
    // �����п�ı���
    QList<int> column_width_ratios = { 15, 15, 40, 15, 15 };
    set_column_width_ratios(tableWidgetVS, column_width_ratios);

}

void EPVS::set_column_width_ratios(QTableWidget* tableWidget, const QList<int>& ratios)
{
    int total_width = tableWidget->viewport()->width();
    QHeaderView* header = tableWidget->horizontalHeader();

    for (int i = 0; i < ratios.size(); ++i)
    {
        // ������Ϊ�Զ�����ģʽ
        header->setSectionResizeMode(i, QHeaderView::Interactive);
        // �����п�Ϊ���������ܿ��
        int width = total_width * ratios[i] / 100;
        header->resizeSection(i, width);
    }

    // ���һ������Ϊ�Զ����ʣ��ռ�
    header->setSectionResizeMode(ratios.size() - 1, QHeaderView::Stretch);
}

void EPVS::resizeEvent(QResizeEvent* event) {
    // �������ڴ�С�仯ʱ������񲿼��Ĵ�С    
    QWidget::resizeEvent(event);
    QList<int> column_width_ratios = { 15, 15, 40, 15, 15 };
    set_column_width_ratios(tableWidgetVS,column_width_ratios);
}


void EPVS::createMainEPVSRightLayout(QWidget* widget_vs_right) {
    widget_vs_right_top = new QWidget(widget_vs_right);
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

    // widget_vs_right_top������һ�����񲼾�
    QGridLayout* layout_widget_vs_right_top = new QGridLayout(widget_vs_right_top);
    layout_widget_vs_right_top->addWidget(pushButtonLoadEPCAM, 0, 0);
    layout_widget_vs_right_top->addWidget(pushButtonSaveDMS, 0, 1);
    if (login_user_type != "dms") {
        pushButtonSaveDMS->setDisabled(true);
    }    
    layout_widget_vs_right_top->addWidget(pushButtonSaveLocal, 1, 1);
    layout_widget_vs_right_top->addWidget(pushButtonSettings, 2, 1);
    layout_widget_vs_right_top->addWidget(pushButtonHelp, 3, 1);
    // ���ò����и��������ļ��
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
    // �ļ��е���������
    if (!backHistory.empty()) {
        QString backFolder = backHistory.back();
        backHistory.pop_back();
        updateFolderContents(backFolder);
    }
}

void EPVS::on_goForwardClicked()
{
    // �ļ��е�����ǰ��
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
        backHistory.push_back(currentFolder);  // ����ǰ�ļ���·����ӵ���ʷ��¼��
        currentFolder = forwardFolder;  // ���µ�ǰ�ļ���·��
        updateFolderContents(forwardFolder);
    }
}

void EPVS::on_goUpClicked()
{
    // �ļ��е���������
    QString currentText = comboBoxMainFileExplorerPath->currentText();
    QString upFolder = QFileInfo(currentText).dir().path();

    updateFolderContents(upFolder);
}

void EPVS::on_commonFolderListItemClicked(QListWidgetItem* item)
{
    QString folder_name = item->text();
    
    // �����Զ��峣���ļ��У��������ļ���ȡ
    // ��ȡ�����ļ�
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

        if (folder_name == "����")
            folder_path = QDir::homePath() + "/Desktop";
        else if (folder_name == "����")
            folder_path = QDir::homePath() + "/Downloads";
        else if (folder_name == "�ĵ�")
            folder_path = QDir::homePath() + "/Documents";
        else if (folder_name == "ͼƬ")
            folder_path = QDir::homePath() + "/Pictures";
        else if (folder_name == "����")
            folder_path = QDir::homePath() + "/Music";
        else if (folder_name == "��Ƶ")
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

        backHistory.push_back(currentFolder);  // ����ǰ�ļ���·����ӵ���ʷ��¼��
        currentFolder = folder_path;  // ���µ�ǰ�ļ���·��
        updateFolderContents(folder_path);
    }
}

void EPVS::updateFolderContents(const QString& pathText) {
    // �����ļ�����ͼ
    QWidget* contentWidget = findChild<QWidget*>("content_widget");

    // �������
    while (contentWidget->layout()->count() > 0) {
        QLayoutItem* child = contentWidget->layout()->takeAt(0);
        if (child->widget()) {
            child->widget()->deleteLater();
        }
        delete child;
    }

    // �����ļ������ݲ���
    QWidget* folderContentsWidget = new QWidget();
    QGridLayout* folderContentsLayout = new QGridLayout(folderContentsWidget);
    folderContentsLayout->setContentsMargins(10, 10, 10, 10);
    folderContentsLayout->setSpacing(10);

    folderListView = new ListViewFile(pathText);
    // �����Զ���ί���������ļ������Զ�����
    FileNameDelegate* delegate = new FileNameDelegate(folderListView);
    folderListView->setItemDelegate(delegate);

    QObject::connect(folderListView, &ListViewFile::doubleClicked, this, &EPVS::on_folderSelectedDoubleClicked);
    
    connect(folderListView, &ListViewFile::triggerListViewFileStr, this, &EPVS::updateTriggerListViewFileStr);
    //connect(folderListView, &ListViewFile::triggerListViewFileStrVsInputA, this, &MyClass::updateTriggerListViewFileStrVsInputA);
    //connect(folderListView, &ListViewFile::triggerListViewFileStrVsInputB, this, &MyClass::updateTriggerListViewFileStrVsInputB);
    //connect(folderListView, &ListViewFile::triggerListViewFileStrSwitchTab, this, &MyClass::updateTriggerListViewFileStrSwitchTab);*/

    // ���ļ������ݲ�����ӵ�������
    folderContentsLayout->addWidget(folderListView);

    // ���ļ������ݲ�������Ϊ�ұߴ���B���Ӳ���
    contentWidget->layout()->addWidget(folderContentsWidget);

    // ����ǰ�ļ���·����ӵ�ǰ��·������ʷ��¼
    forwardHistory.push_back(pathText);

    // ���µ�ַ��
     comboBoxMainFileExplorerPath->setCurrentText(pathText);

    folderListView->setPath(pathText);  // ����path

    // ������ʷ��¼����ַ��    
    QStringList itemsList;
    std::copy_if(backHistory.begin(), backHistory.end(), std::back_inserter(itemsList),
        [](const QString& item) { return item.length() > 0; });
    QSet<QString> uniqueItemsSet = QSet<QString>::fromList(itemsList);
    itemsList = uniqueItemsSet.toList();

    comboBoxMainFileExplorerPath->clear();
    comboBoxMainFileExplorerPath->addItems(itemsList);
    // ���µ�ַ��
    comboBoxMainFileExplorerPath->setCurrentText(pathText);

    path = pathText;
}

void EPVS::on_folderSelectedDoubleClicked(const QModelIndex& index)
{
    //QFileSystemModel* folderModel = qobject_cast<QFileSystemModel*>(index.model());
    QFileSystemModel* folderModel = static_cast<QFileSystemModel*>(const_cast<QAbstractItemModel*>(index.model()));

    if (folderModel->isDir(index))
    {
        backHistory.push_back(currentFolder);  // ����ǰ�ļ���·����ӵ���ʷ��¼��
        forwardHistory.push_back(currentFolder);  // ����ǰ�ļ���·����ӵ� forward ��¼��
        currentFolder = folderModel->filePath(index);  // ���µ�ǰ�ļ���·��
        updateFolderContents(currentFolder);
    }
    else
    {
        // ����ѡ������ļ������
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

        /* �����ļ�����ͼ */
        QWidget* content_widget = findChild<QWidget*>("content_widget");
        // �������
        while (content_widget->layout()->count() > 0) {
            QLayoutItem* child = content_widget->layout()->takeAt(0);
            if (child->widget()) {
                child->widget()->deleteLater();
            }
        }

        // �����ļ������ݲ���
        QWidget* folder_contents_widget = new QWidget();
        QGridLayout* folder_contents_layout = new QGridLayout(folder_contents_widget);
        folder_contents_layout->setContentsMargins(10, 10, 10, 10);
        folder_contents_layout->setSpacing(10);


        QStringList modifiedList;

        // ʹ�õ������������޸��ַ����б�
        for (QStringList::const_iterator it = filePaths.begin(); it != filePaths.end(); ++it) {
            // ʹ�þ�̬����ƴ��·��
            QString modifiedString = QDir::cleanPath(QDir(path).filePath(*it));
            
            modifiedList.append(modifiedString);
        }

        


        folderListViewForList = new ListViewFileForList(modifiedList, this);

        connect(folderListViewForList, &ListViewFileForList::doubleClicked, this, &EPVS::searchResultSelected);

        // ���ļ������ݲ�����ӵ�������
        folder_contents_layout->addWidget(folderListViewForList);

        // ���ļ������ݲ�������Ϊ�ұߴ���B���Ӳ���
        content_widget->layout()->addWidget(folder_contents_widget);
    }
    else {
        // ����ؼ���Ϊ�գ�ִ����������
        updateFolderContents(comboBoxMainFileExplorerPath->currentText());
    }
}

void EPVS::searchResultSelected(const QModelIndex& index)
{   
    
    // ѡ���ļ���
    QAbstractItemModel* abstractModel = folderListViewForList->model;
    QStandardItemModel* model = static_cast<QStandardItemModel*>(abstractModel);    
    QStandardItem* item = model->itemFromIndex(index);           
    QString pathStr = item->text();


    if (QDir(pathStr).exists()) {
        backHistory.push_back(currentFolder); // ����ǰ�ļ���·����ӵ���ʷ��¼��
        currentFolder = pathStr; // ���µ�ǰ�ļ���·��
        updateFolderContents(currentFolder);
    }
    else {
        // ����ѡ������ļ������
        QString filePath = pathStr;

        QUrl url = QUrl::fromLocalFile(filePath);
        QDesktopServices::openUrl(url);
    }
}


void EPVS::updateTriggerListViewFileStr(const QString& message){
    qDebug() << "outcc2" << message;
    QString str = message;
    QStringList splitList = str.split("|"); // ����ַ���

    if (splitList.size() >= 2) {
        QString contentUsageType = splitList[0]; // ��ȡ����
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
    // ����һ����Ϣ��
    QMessageBox messageBox(this);
    messageBox.setIcon(QMessageBox::Question);
    messageBox.setWindowTitle("ȷ���˳�");
    messageBox.setText("ȷ��Ҫ�˳���");

    // ���ȷ�Ϻ�ȡ����ť
    QPushButton* confirmButton = messageBox.addButton("ȷ��", QMessageBox::AcceptRole);
    QPushButton* cancelButton = messageBox.addButton("ȡ��", QMessageBox::RejectRole);

    // ��ʾ��Ϣ�򣬲��ȴ��û���Ӧ
    messageBox.exec();

    // �ж��û���������ĸ���ť
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