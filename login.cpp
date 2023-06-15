#include "login.h"
#include "ui_login.h"
#include <QMessageBox>
#include "EPVS.h"
#include "ccMethod/EncryptionQByteArray.h"
#include <QSettings>
#include <QtCore/QDebug>
#include "global_variables.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>



//login_user_type��ȫ�ֱ���
QString login_user_type = "";





Login::Login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

    this->loadConfig();


    connect(ui->pushButtonLogin, SIGNAL(clicked()), this, SLOT(handleButtonClick()));


}

Login::~Login()
{
    delete ui;
}


void Login::loadConfig() {   
    
    QJsonObject login_data;
    QFile file("settings/epvs.json");
    // ���ļ���ȡJSON����
    if (file.open(QIODevice::ReadOnly))
    {
        QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
        file.close();

        if (doc.isObject())
        {
            QJsonObject data = doc.object();
            login_data = data["login"].toObject();            
        }
    }


    QString remember = login_data["remember"].toString();
    QString user_name = login_data["user_name"].toString();    
    QString storedpassword = login_data["password"].toString();
    QString login_user_type = login_data["user_type"].toString();
        
    qDebug() << "remember:" << remember;    
    
    if (remember == "True") {
        // �������ļ���ȡ�û������ڵ�¼����Ĭ����ʾ����
        ui->lineEditUserName->setText(user_name);

        // �������ļ���ȡ���벢�ڵ�¼����Ĭ����ʾ����
        // ��Ҫ�������룬
        EncryptionQByteArray encryptionQByteArray;        
        QString decryptedPassword = encryptionQByteArray.decrypt(storedpassword);
        ui->lineEditPassword->setText(decryptedPassword);
        
        // �Ƿ�Ҫ��ס����
        ui->checkBoxRememberPassword->setChecked(true); 
        

        if (login_user_type == "common") {
            ui->radioButtonUserNameTypeCommon->setChecked(true);            
        }
        if (login_user_type == "dms") {
            ui->radioButtonUserNameTypeDMS->setChecked(true);
        }


    }
    else {
        ui->checkBoxRememberPassword->setChecked(false);
    }


}




void Login::handleButtonClick()
{
    //QMessageBox::information(this, "Button Clicked", "The button was clicked!");       


    EncryptionQByteArray encryptionQByteArray;

    
    QSettings settings("settings/config.ini", QSettings::IniFormat);

    
    QString jsonFilePath = "settings/epvs.json";

    // ��JSON�ļ��ж�ȡJSON����
    QFile loadJsonFile(jsonFilePath);
    if (loadJsonFile.open(QIODevice::ReadOnly)) {
        QByteArray jsonData = loadJsonFile.readAll();
        QJsonDocument loadedJsonDoc = QJsonDocument::fromJson(jsonData);
        QJsonObject loadedObject = loadedJsonDoc.object();

        // �޸�Ƕ��JSON�е�һ��������ֵ
        modifyJsonValue(loadedObject, "nestedObject/var2", "new value");

        // ���޸ĺ��JSON���󱣴��JSON�ļ�
        QFile saveJsonFile(jsonFilePath);
        if (saveJsonFile.open(QIODevice::WriteOnly)) {
            QJsonDocument modifiedJsonDoc(loadedObject);
            saveJsonFile.write(modifiedJsonDoc.toJson());
            saveJsonFile.close();
            qDebug() << "Modified JSON file saved successfully.";
        }
        else {
            qDebug() << "Failed to save modified JSON file.";
        }
    }
    else {
        qDebug() << "Failed to load JSON file.";
    }





    
       

    
    loginUserName = ui->lineEditUserName->text();
    loginPassword = ui->lineEditPassword->text();

    if (ui->radioButtonUserNameTypeCommon->isChecked()) {
        login_user_type = "common";
    }
    if (ui->radioButtonUserNameTypeDMS->isChecked()) {
        login_user_type = "dms";
    }

    
    if (ui->checkBoxRememberPassword->isChecked()) {
        settings.setValue("DEFAULT/user_name", loginUserName);





        // ��������
        QString encryptedPassword = encryptionQByteArray.encrypt(loginPassword);
        // �����ܺ�����뱣�浽�����ļ�
        settings.setValue("DEFAULT/password", encryptedPassword);
        settings.setValue("DEFAULT/remember", "True");

    }
    else {
        settings.setValue("DEFAULT/user_name", loginUserName);        
        settings.setValue("DEFAULT/remember", "False");
    }


    if (loginUserName == "cc" && loginPassword == "123") {
        //QMessageBox::information(this, "cc", "cc!");
        
        epvs.show();
        close();

        

    }


    //// ����Ƕ�׵�JSON����
    //QJsonObject root;
    //root["name"] = "John";
    //root["age"] = 25;

    //QJsonObject address;
    //address["city"] = "New York";
    //address["street"] = "123 Main St";

    //root["address"] = address;

    //// ��JSON����д���ļ�
    //QFile file2("config.json");
    //if (file2.open(QIODevice::WriteOnly))
    //{
    //    QJsonDocument doc(root);
    //    file2.write(doc.toJson());
    //    file2.close();
    //}

    





}
