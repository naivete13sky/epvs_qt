#pragma once
#include <QtWidgets/QListWidget>


class QListWidgetCommonFolder:public QListWidget {
    Q_OBJECT

public:
    QListWidgetCommonFolder(QWidget* parent = nullptr);

    ~QListWidgetCommonFolder();

signals:
    void triggerQListWidgetCommonFolderStr(const QString&);

private:
    bool isFixedCommonFolder(const QString& folderName);
private slots:
    void folderListHandleRightClick(const QPoint& pos);
    
};