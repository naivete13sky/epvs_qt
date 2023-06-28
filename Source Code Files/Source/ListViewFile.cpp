#include "./../Include/ListViewFile.h"
#include "./../Include/global_variables.h"


ListViewFile::ListViewFile(const QString& path, QWidget* parent)
    : QListView(parent), path(path)
{
    QFileSystemModel* folderModel = new QFileSystemModel(this);
    folderModel->setRootPath(path);
    setModel(folderModel);
    setRootIndex(folderModel->index(path));
    setIconSize(QSize(64, 64));
    setViewMode(QListView::IconMode);
    setResizeMode(QListView::Adjust);
    setGridSize(QSize(120, 120));
    setSpacing(20);

    contextMenu = new QMenu(this);
    contextMenu->setStyleSheet("QMenu::item:selected { color: black; }");

    openAction = new QAction("Open", this);
    copyAction = new QAction("Copy", this);
    pasteAction = new QAction("Paste", this);
    cutAction = new QAction("Cut", this);
    deleteAction = new QAction("Delete", this);
    renameAction = new QAction("Rename", this);
    newFolderAction = new QAction("New Folder", this);
    subMenuDms = new QMenu("DMS", this);
    dmsUploadToMainJobAction = new QAction("Upload DMS Main Job", this);
    subMenuDms->addAction(dmsUploadToMainJobAction);

    if (login_user_type != "dms")
    {
        subMenuDms->setDisabled(true);
    }

    contextMenu->addAction(openAction);
    contextMenu->addAction(copyAction);
    contextMenu->addAction(pasteAction);
    contextMenu->addAction(cutAction);
    contextMenu->addAction(deleteAction);
    contextMenu->addAction(renameAction);
    contextMenu->addAction(newFolderAction);
    contextMenu->addMenu(subMenuDms);

    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(showContextMenu(const QPoint&)));

    connect(openAction, SIGNAL(triggered()), this, SLOT(openSelected()));
    connect(copyAction, SIGNAL(triggered()), this, SLOT(copySelected()));
    connect(pasteAction, SIGNAL(triggered()), this, SLOT(pasteSelected()));
    connect(cutAction, SIGNAL(triggered()), this, SLOT(cutSelected()));
    connect(deleteAction, SIGNAL(triggered()), this, SLOT(deleteSelected()));
    connect(renameAction, SIGNAL(triggered()), this, SLOT(renameSelected()));
    connect(newFolderAction, SIGNAL(triggered()), this, SLOT(newFolder()));
    connect(dmsUploadToMainJobAction, SIGNAL(triggered()), this, SLOT(dmsUploadToMainJobSelected()));

    createShortcuts();
}

void ListViewFile::showContextMenu(const QPoint& pos)
{
    customizeContextMenu();
    contextMenu->exec(mapToGlobal(pos));
}


void ListViewFile::setPath(const QString& pathText) {
    path = pathText;
}





void ListViewFile::openSelected()
{
    QModelIndex index = currentIndex();
    QString selectedName = index.data().toString();
    absolutePath = QDir::cleanPath(path + QDir::separator() + selectedName);
    QFileInfo fileInfo(absolutePath);

    if (fileInfo.isFile())
    {
        QDesktopServices::openUrl(QUrl::fromLocalFile(absolutePath));
    }
    else if (fileInfo.isDir())
    {
        openFolder(absolutePath);
    }
}

void ListViewFile::copySelected()
{
    // Copy selected item(s) to clipboard
    // Implementation goes here
}

void ListViewFile::pasteSelected()
{
    // Paste item(s) from clipboard
    // Implementation goes here
}

void ListViewFile::cutSelected()
{
    // Cut selected item(s) to clipboard
    // Implementation goes here
}

void ListViewFile::deleteSelected()
{
    // Delete selected item(s)
    // Implementation goes here
}

void ListViewFile::renameSelected()
{
    // Rename selected item
    // Implementation goes here
}

void ListViewFile::newFolder()
{
    // Create a new folder
    // Implementation goes here
}

void ListViewFile::dmsUploadToMainJobSelected()
{
    // DMS Upload to Main Job
    // Implementation goes here
}

void ListViewFile::rarUncompressToRarFileNameFolderSelected()
{
    // Uncompress selected RAR file to a folder with the RAR file name
    // Implementation goes here
}

void ListViewFile::rarUncompressToCurrentFolderSelected()
{
    // Uncompress selected RAR file to the current folder
    // Implementation goes here
}

void ListViewFile::customizeContextMenu()
{
    contextMenu->clear();

    openAction = new QAction("Open", this);
    copyAction = new QAction("Copy", this);
    pasteAction = new QAction("Paste", this);
    cutAction = new QAction("Cut", this);
    deleteAction = new QAction("Delete", this);
    renameAction = new QAction("Rename", this);
    newFolderAction = new QAction("New Folder", this);
    subMenuDms = new QMenu("DMS", this);
    subMenuDms->setStyleSheet("QMenu::item:selected { color: red; }");
    dmsUploadToMainJobAction = new QAction("Upload DMS Main Job", this);
    subMenuDms->addAction(dmsUploadToMainJobAction);

    contextMenu->addAction(openAction);
    contextMenu->addAction(copyAction);
    contextMenu->addAction(pasteAction);
    contextMenu->addAction(cutAction);
    contextMenu->addAction(deleteAction);
    contextMenu->addAction(renameAction);
    contextMenu->addAction(newFolderAction);
    contextMenu->addMenu(subMenuDms);

    if (login_user_type != "dms")
    {
        subMenuDms->setDisabled(true);
    }
}

void ListViewFile::createShortcuts()
{
    QShortcut* copyShortcut = new QShortcut(QKeySequence::Copy, this);
    QShortcut* pasteShortcut = new QShortcut(QKeySequence::Paste, this);
    QShortcut* cutShortcut = new QShortcut(QKeySequence::Cut, this);
    QShortcut* deleteShortcut = new QShortcut(QKeySequence::Delete, this);
    QShortcut* renameShortcut = new QShortcut(QKeySequence(Qt::Key_F2), this);

    connect(copyShortcut, SIGNAL(activated()), this, SLOT(copySelected()));
    connect(pasteShortcut, SIGNAL(activated()), this, SLOT(pasteSelected()));
    connect(cutShortcut, SIGNAL(activated()), this, SLOT(cutSelected()));
    connect(deleteShortcut, SIGNAL(activated()), this, SLOT(deleteSelected()));
    connect(renameShortcut, SIGNAL(activated()), this, SLOT(renameSelected()));
}

void ListViewFile::openFolder(const QString& folderPath)
{
    emit triggerListViewFileStr(folderPath);
    emit triggerListViewFileStrVsInputA(folderPath);
    emit triggerListViewFileStrVsInputB(folderPath);
    emit triggerListViewFileStrSwitchTab("0");
}
