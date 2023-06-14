#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include <QWidget>
#include <QPushButton>


namespace Ui {
class Login;
}

class Login : public QMainWindow
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();

public slots:
    void handleButtonClick();


private:
    Ui::Login *ui;
};

#endif // LOGIN_H
