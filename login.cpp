#include "login.h"
#include "ui_login.h"
#include <QMessageBox>

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
    QMessageBox::information(this, "Button Clicked", "The button was clicked!");
}
