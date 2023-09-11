/********************************************************************
 * Author:		 浮生流年
 * Created:	     2021年12月18日
 * Description:	 垂直文本
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

	// 控制CE_TabBarTabLabel的尺寸
	QSize sizeFromContents(QStyle::ContentsType type, const QStyleOption* option,
		const QSize& contentsSize, const QWidget* widget = nullptr) const;

private:
	Qt::Orientation m_orientation;	// 文本方向
};
