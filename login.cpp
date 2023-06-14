#include "login.h"
#include "ui_login.h"
#include <QMessageBox>
#include "EPVS.h"

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
    
    loginUserName = ui->lineEditUserName->text();
    loginPassword = ui->lineEditPassword->text();
    if (loginUserName == "cc" && loginPassword == "123") {
        //QMessageBox::information(this, "cc", "cc!");
        
        epvs.show();
        close();
        

    }



}
