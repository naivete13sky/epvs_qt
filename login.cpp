#include "login.h"
#include "ui_login.h"
#include <QMessageBox>
#include "EPVS.h"
#include "ccMethod/EncryptionQByteArray.h"
#include <QSettings>
#include <QtCore/QDebug>

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
        QString login_user_type = settings.value("DEFAULT/user_type").toString();
    }


}




void Login::handleButtonClick()
{
    //QMessageBox::information(this, "Button Clicked", "The button was clicked!");       


    EncryptionQByteArray encryptionQByteArray;

    // 加密密码
    QString password = "123";
    QString encryptedPassword = encryptionQByteArray.encrypt(password);
    // 将加密后的密码保存到配置文件
    QSettings settings("settings/config.ini", QSettings::IniFormat);
    settings.setValue("account/password", encryptedPassword);

    

    

    // 读取并解密密码
    QString storedpassword = settings.value("account/password").toString();
    QString decryptedPassword = encryptionQByteArray.decrypt(storedpassword);

    qDebug() << "Original password:" << password;
    qDebug() << "Encrypted password:" << encryptedPassword;
    qDebug() << "Decrypted password:" << decryptedPassword;
    


    
    loginUserName = ui->lineEditUserName->text();
    loginPassword = ui->lineEditPassword->text();
    if (loginUserName == "cc" && loginPassword == "123") {
        //QMessageBox::information(this, "cc", "cc!");
        
        epvs.show();
        close();

        

    }



}
