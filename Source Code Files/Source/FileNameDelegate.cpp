#include "./../Include/FileNameDelegate.h"
#include <QPainter>

FileNameDelegate::FileNameDelegate(QObject* parent)
    : QStyledItemDelegate(parent)
{
}

void FileNameDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    // 获取文件名和图标
    QString file_model = index.data(Qt::DisplayRole).toString();
    QIcon file_icon = qvariant_cast<QIcon>(index.data(Qt::DecorationRole));

    // 获取绘制区域和边距
    QRect rect = option.rect;
    int margins = 4;

    // 绘制背景
    painter->save();
    if (option.state & QStyle::State_Selected)
        painter->fillRect(rect, option.palette.highlight());

    // 绘制图标
    QRect icon_rect(rect.x(), rect.y(), rect.width(), rect.height() - 20);  // 调整图标区域的高度，最后数字越大，图标越小
    file_icon.paint(painter, icon_rect, Qt::AlignCenter, QIcon::Normal, QIcon::Off);

    // 绘制文件名，自动换行且居中对齐
    QRect text_rect(rect.x(), rect.y() + icon_rect.height(), rect.width(), rect.height() - icon_rect.height());
    QTextDocument doc;
    doc.setDefaultStyleSheet("p { margin: 0; text-align: center; }");
    doc.setHtml("<p>" + file_model + "</p>");
    doc.setTextWidth(text_rect.width());
    QAbstractTextDocumentLayout* layout = doc.documentLayout();
    painter->translate(text_rect.topLeft());
    layout->draw(painter, QAbstractTextDocumentLayout::PaintContext());
    painter->restore();
}
