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
#include "ccMethod/jsonutils.h" // 包含头文件
#include "dms/dms.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;



//login_user_type是全局变量
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
    // 从文件读取JSON数据
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
        // 从配置文件读取用户名并在登录窗口默认显示出来
        ui->lineEditUserName->setText(user_name);

        // 从配置文件读取密码并在登录窗口默认显示出来
        // 需要解密密码，
        EncryptionQByteArray encryptionQByteArray;        
        QString decryptedPassword = encryptionQByteArray.decrypt(storedpassword);
        ui->lineEditPassword->setText(decryptedPassword);
        
        // 是否要记住密码
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
    //加密解密方法
    EncryptionQByteArray encryptionQByteArray;
    
    QString jsonFilePath = "settings/epvs.json";
    QJsonObject loadedObject;
    // 从JSON文件中读取JSON对象
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

    //记住登录信息
    if (ui->checkBoxRememberPassword->isChecked()) {        
        // loginUserName保存到配置文件
        modifyJsonValue(loadedObject, "login/user_name", loginUserName);

        // 加密密码
        QString encryptedPassword = encryptionQByteArray.encrypt(loginPassword);
        // 将加密后的密码保存到配置文件
        modifyJsonValue(loadedObject, "login/password", encryptedPassword);
        
        modifyJsonValue(loadedObject, "login/remember", "True");

        modifyJsonValue(loadedObject, "login/user_type", login_user_type);

    }
    else {
        // loginUserName保存到配置文件
        modifyJsonValue(loadedObject, "login/user_name", loginUserName);
        modifyJsonValue(loadedObject, "login/password", "");
        modifyJsonValue(loadedObject, "login/remember", "False");
        
    }


    // 将修改后的JSON对象保存回JSON文件
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
            // 创建一个警告框
            QMessageBox::warning(nullptr, u8"登录错误", u8"用户名或密码错误!");
            ui->lineEditUserName->setFocus();
        }

    }


    if (login_user_type == "dms") {
        DMS dms;
        json jsonResult = dms.login(loginUserName, loginPassword);
        // 将 JSON 数据转换为字符串
        std::string jsonDataString = jsonResult.dump();
        // 输出 JSON 字符串    
        qDebug() << "jsonResult:" << jsonDataString.c_str();

        
        json loginResultJson = json::parse(jsonDataString);
        std::string loginResult = loginResultJson["result"];
        qDebug() << "Result: " << loginResult.c_str();


        
        if (loginResult == "true") {
            epvs.show();
            close();
        }
        else {
            // 创建一个警告框
            QMessageBox::warning(nullptr, u8"登录错误", u8"用户名或密码错误!");
            ui->lineEditUserName->setFocus();
        }

    }
    


    




}
