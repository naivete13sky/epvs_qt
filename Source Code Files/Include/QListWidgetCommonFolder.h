#pragma once
#include <QtWidgets/QListWidget>


class QListWidgetCommonFolder:public QListWidget {
    Q_OBJECT

public:
    QListWidgetCommonFolder(QWidget* parent = nullptr);

    ~QListWidgetCommonFolder();

signals:
    void triggerQListWidgetCommonFolderStr(QString value);

private:
    
};