#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_EPVS.h"
#include "../Include/QListWidgetCommonFolder.h"

class EPVS : public QMainWindow
{
    Q_OBJECT

public:
    EPVS(QWidget *parent = nullptr);
    ~EPVS();
    void triggerQListWidgetCommonFolderStr_update(const QString& message);
    QListWidgetCommonFolder* folder_list;
private:
    Ui::EPVSClass ui;
};
