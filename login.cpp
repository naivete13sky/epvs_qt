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
#include "ccMethod/jsonutils.h" // ����ͷ�ļ�
#include "dms/dms.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;



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
    //���ܽ��ܷ���
    EncryptionQByteArray encryptionQByteArray;
    
    QString jsonFilePath = "settings/epvs.json";
    QJsonObject loadedObject;
    // ��JSON�ļ��ж�ȡJSON����
    QFile loadJsonFile(jsonFilePath);
    if (loadJsonFile.open(QIODevice::ReadOnly)) {
        QByteArray jsonData = loadJsonFile.readAll();
        QJsonDocument loadedJsonDoc = QJsonDocument::fromJson(jsonData);
        loadedObject = loadedJsonDoc.object();        
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

    //��ס��¼��Ϣ
    if (ui->checkBoxRememberPassword->isChecked()) {        
        // loginUserName���浽�����ļ�
        modifyJsonValue(loadedObject, "login/user_name", loginUserName);

        // ��������
        QString encryptedPassword = encryptionQByteArray.encrypt(loginPassword);
        // �����ܺ�����뱣�浽�����ļ�
        modifyJsonValue(loadedObject, "login/password", encryptedPassword);
        
        modifyJsonValue(loadedObject, "login/remember", "True");

        modifyJsonValue(loadedObject, "login/user_type", login_user_type);

    }
    else {
        // loginUserName���浽�����ļ�
        modifyJsonValue(loadedObject, "login/user_name", loginUserName);
        modifyJsonValue(loadedObject, "login/password", "");
        modifyJsonValue(loadedObject, "login/remember", "False");
        
    }


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



    if (login_user_type == "common") {
        if (loginUserName == "cc" && loginPassword == "123") {
            //QMessageBox::information(this, "cc", "cc!");

            epvs.show();
            close();
        }
        else {
            // ����һ�������
            QMessageBox::warning(nullptr, u8"��¼����", u8"�û������������!");
            ui->lineEditUserName->setFocus();
        }

    }


    if (login_user_type == "dms") {
        DMS dms;
        json jsonResult = dms.login(loginUserName, loginPassword);
        // �� JSON ����ת��Ϊ�ַ���
        std::string jsonDataString = jsonResult.dump();
        // ��� JSON �ַ���    
        qDebug() << "jsonResult:" << jsonDataString.c_str();

        
        json loginResultJson = json::parse(jsonDataString);
        std::string loginResult = loginResultJson["result"];
        qDebug() << "Result: " << loginResult.c_str();


        
        if (loginResult == "true") {
            epvs.show();
            close();
        }
        else {
            // ����һ�������
            QMessageBox::warning(nullptr, u8"��¼����", u8"�û������������!");
            ui->lineEditUserName->setFocus();
        }

    }
    


    




}
