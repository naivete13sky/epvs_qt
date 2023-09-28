/********************************************************************
 * Author:		 ��������
 * Created:	     2021��12��18��
 * Description:	 ��ֱ�ı�
 * Filename: 	 TabBarStyle.h
*********************************************************************/
#pragma once

#include <QProxyStyle>

class TabBarStyle : public QProxyStyle
{
	Q_OBJECT

public:
	TabBarStyle(Qt::Orientation orientation = Qt::Vertical);
	~TabBarStyle();

	void drawControl(QStyle::ControlElement element, const QStyleOption* option,
		QPainter* painter, const QWidget* widget = nullptr) const;

	void drawItemText(QPainter* painter, const QRect& rect, int flags, const QPalette& pal,
		bool enabled, const QString& text, QPalette::ColorRole textRole = QPalette::NoRole) const;

	// ����CE_TabBarTabLabel�ĳߴ�
	QSize sizeFromContents(QStyle::ContentsType type, const QStyleOption* option,
		const QSize& contentsSize, const QWidget* widget = nullptr) const;

private:
	Qt::Orientation m_orientation;	// �ı�����
};
