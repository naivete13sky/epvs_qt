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

    connect(ui->pushButtonLogin, SIGNAL(clicked()), this, SLOT(handleButtonClick()));


}

Login::~Login()
{
    delete ui;
}

void Login::handleButtonClick()
{
    //QMessageBox::information(this, "Button Clicked", "The button was clicked!");


    //// 加密密码
    //QString password = "mysecretpassword";
    //QString encryptedPassword = PasswordManager::encryptPassword(password);

    //// 将加密后的密码保存到配置文件
    //QSettings settings("config.ini", QSettings::IniFormat);
    //settings.setValue("account/password", encryptedPassword);


    EncryptionQByteArray encryptionQByteArray;

    // Encrypt
    QString plainText = "Hello, World!";
    QString cipherText = encryptionQByteArray.encrypt(plainText);
    qDebug() << "Plain Text:" << plainText;
    qDebug() << "Cipher Text:" << cipherText;

    // Decrypt
    QString decryptedText = encryptionQByteArray.decrypt(cipherText);
    qDebug() << "Decrypted Text:" << decryptedText;






    //// 读取并解密密码
    //QString storedPassword = settings.value("account/password").toString();
    //QString decryptedPassword = PasswordManager::decryptPassword2(storedPassword);

    qDebug() << "Original password:" << plainText;
    qDebug() << "Encrypted password:" << cipherText;    
    qDebug() << "Decrypted password:" << decryptedText;

    



    
    loginUserName = ui->lineEditUserName->text();
    loginPassword = ui->lineEditPassword->text();
    if (loginUserName == "cc" && loginPassword == "123") {
        //QMessageBox::information(this, "cc", "cc!");
        
        epvs.show();
        close();

        

    }



}
