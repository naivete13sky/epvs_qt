#include "EPVS.h"
#include "login.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //EPVS w;
    Login login;
    //w.show();
    login.show();

    return a.exec();
}
