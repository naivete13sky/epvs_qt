#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_EPVS.h"

class EPVS : public QMainWindow
{
    Q_OBJECT

public:
    EPVS(QWidget *parent = nullptr);
    ~EPVS();

private:
    Ui::EPVSClass ui;
};
