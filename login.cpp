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


    EncryptionQByteArray encryptionQByteArray;

    // ��������
    QString password = "Hello, World!";
    QString encryptedPassword = encryptionQByteArray.encrypt(password);
    // �����ܺ�����뱣�浽�����ļ�
    QSettings settings("settings/config.ini", QSettings::IniFormat);
    settings.setValue("account/password", encryptedPassword);

    
    

    // ��ȡ����������
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
