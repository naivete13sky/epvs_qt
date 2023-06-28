#include "./../Include/FileNameDelegate.h"
#include <QPainter>

FileNameDelegate::FileNameDelegate(QObject* parent)
    : QStyledItemDelegate(parent)
{
}

void FileNameDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    // ��ȡ�ļ�����ͼ��
    QString file_model = index.data(Qt::DisplayRole).toString();
    QIcon file_icon = qvariant_cast<QIcon>(index.data(Qt::DecorationRole));

    // ��ȡ��������ͱ߾�
    QRect rect = option.rect;
    int margins = 4;

    // ���Ʊ���
    painter->save();
    if (option.state & QStyle::State_Selected)
        painter->fillRect(rect, option.palette.highlight());

    // ����ͼ��
    QRect icon_rect(rect.x(), rect.y(), rect.width(), rect.height() - 20);  // ����ͼ������ĸ߶ȣ��������Խ��ͼ��ԽС
    file_icon.paint(painter, icon_rect, Qt::AlignCenter, QIcon::Normal, QIcon::Off);

    // �����ļ������Զ������Ҿ��ж���
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
