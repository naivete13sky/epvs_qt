#pragma once
#ifndef FILENAMEDELEGATE_H
#define FILENAMEDELEGATE_H

#include <QStyledItemDelegate>
#include <QTextDocument>
#include <QAbstractTextDocumentLayout>
#include <QStyleOptionViewItem>

class FileNameDelegate : public QStyledItemDelegate
{
public:
    FileNameDelegate(QObject* parent = nullptr);

    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
};

#endif // FILENAMEDELEGATE_H
