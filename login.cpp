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
    qDebug() << "loadConfig:";
    QSettings settings("settings/config.ini", QSettings::IniFormat);
    QString remember = settings.value("DEFAULT/remember").toString();
    qDebug() << "remember:" << remember;
    if (remember == "True") {
        ui->lineEditUserName->setText(settings.value("DEFAULT/user_name").toString());

        // 读取并解密密码
        EncryptionQByteArray encryptionQByteArray;
        QString storedpassword = settings.value("DEFAULT/password").toString();
        QString decryptedPassword = encryptionQByteArray.decrypt(storedpassword);
        ui->lineEditPassword->setText(decryptedPassword);

        ui->checkBoxRememberPassword->setChecked(true);
        
        login_user_type = settings.value("DEFAULT/user_type").toString();

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
        // 加密密码
        QString encryptedPassword = encryptionQByteArray.encrypt(loginPassword);
        // 将加密后的密码保存到配置文件
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


    // 创建嵌套的JSON数据
    QJsonObject root;
    root["name"] = "John";
    root["age"] = 25;

    QJsonObject address;
    address["city"] = "New York";
    address["street"] = "123 Main St";

    root["address"] = address;

    // 将JSON数据写入文件
    QFile file("config.json");
    if (file.open(QIODevice::WriteOnly))
    {
        QJsonDocument doc(root);
        file.write(doc.toJson());
        file.close();
    }

    // 从文件读取JSON数据
    if (file.open(QIODevice::ReadOnly))
    {
        QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
        file.close();

        if (doc.isObject())
        {
            QJsonObject data = doc.object();

            QString name = data["name"].toString();
            int age = data["age"].toInt();

            QJsonObject addressData = data["address"].toObject();
            QString city = addressData["city"].toString();
            QString street = addressData["street"].toString();

            qDebug() << "Name:" << name;
            qDebug() << "Age:" << age;
            qDebug() << "City:" << city;
            qDebug() << "Street:" << street;
        }
    }





}
