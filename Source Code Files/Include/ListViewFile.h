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
    void setPath(const QString& pathText);

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




#ifndef LISTVIEWFILEFORLIST_H
#define LISTVIEWFILEFORLIST_H

#include <QListView>
#include <QStandardItemModel>
#include <QContextMenuEvent>
#include <QMenu>
#include <QAction>
#include <QShortcut>

class ListViewFileForList : public QListView
{
    Q_OBJECT
public:
    explicit ListViewFileForList(const QStringList& listPath, QWidget* parent = nullptr);

    QStandardItemModel* model;

protected:
    void contextMenuEvent(QContextMenuEvent* event) override;
    void customizeContextMenu();
    void showContextMenu(const QPoint& position);

private slots:
    void openSelected();
    void copySelected();
    void cutSelected();
    void deleteSelected();
    void renameSelected();
    void createShortcuts();
    void keyPressEvent(QKeyEvent* event) override;

private:
    
    QStringList listPath;
    QMenu* contextMenu;
    QAction* openAction;
    QAction* copyAction;
    QAction* cutAction;
    QAction* deleteAction;
    QAction* renameAction;
};

#endif // LISTVIEWFILEFORLIST_H
