#pragma once
#ifndef LISTVIEWFILE_H
#define LISTVIEWFILE_H

#include <QListView>
#include <QFileSystemModel>
#include <QMenu>
#include <QAction>
#include <QKeySequence>
#include <QDesktopServices>
#include <QUrl>
#include <QPoint>
#include <QDir>
#include <QFileInfo>
#include <QModelIndex>
#include <QKeySequence>
#include <QDesktopServices>
#include <QUrl>
#include <QApplication>
#include <QKeyEvent>
#include <QMessageBox>
#include <QDebug>
#include <QShortcut>

class ListViewFile : public QListView
{
    Q_OBJECT

public:
    explicit ListViewFile(const QString& path, QWidget* parent = nullptr);
    void openFolder(const QString& folderPath);

signals:
    void triggerListViewFileStr(const QString& content);
    void triggerListViewFileStrVsInputA(const QString& content);
    void triggerListViewFileStrVsInputB(const QString& content);
    void triggerListViewFileStrSwitchTab(const QString& content);

private slots:
    void showContextMenu(const QPoint& pos);
    void openSelected();
    void copySelected();
    void pasteSelected();
    void cutSelected();
    void deleteSelected();
    void renameSelected();
    void newFolder();
    void dmsUploadToMainJobSelected();
    void rarUncompressToRarFileNameFolderSelected();
    void rarUncompressToCurrentFolderSelected();

private:
    void customizeContextMenu();
    void createShortcuts();

    QString path;
    QString absolutePath;
    QMenu* contextMenu;
    QAction* openAction;
    QAction* copyAction;
    QAction* pasteAction;
    QAction* cutAction;
    QAction* deleteAction;
    QAction* renameAction;
    QAction* newFolderAction;
    QMenu* subMenuDms;
    QAction* dmsUploadToMainJobAction;
    QMenu* subMenuRar;
    QAction* rarUncompressToRarFileNameFolder;
    QAction* rarUncompressToCurrentFolder;
    QString fileName;
};

#endif // LISTVIEWFILE_H
