#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include "./EPVS.h"

namespace Ui {
class Login;
}

class Login : public QMainWindow
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();

    void Login::loadConfig();



    EPVS epvs;

public slots:
    void handleButtonClick();


private:
    Ui::Login *ui;
    QString loginUserName;
    QString loginPassword;
};



#endif // LOGIN_H
