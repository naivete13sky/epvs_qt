#include "../Include/TabBarStyle.h"
#include <QPainter>
#include <QStyleOptionTab>
#include <QDebug>

TabBarStyle::TabBarStyle(Qt::Orientation orientation/* = Qt::Vertical*/)
	: QProxyStyle()
{
	m_orientation = orientation;
}

TabBarStyle::~TabBarStyle()
{
}

void TabBarStyle::drawControl(QStyle::ControlElement element, const QStyleOption* option, QPainter* painter, const QWidget* widget /*= nullptr*/) const
{// <1> �˴�element����Ϊ��CE_TabBarTab,CE_TabBarTabShape,CE_TabBarTabLabel��
 // <2> ��element == CE_TabBarTabLabelʱ��QProxyStyle::drawControl���������drawItemText������
 // <3> ����drawItemText�����ڵõ���rect,��û�д˴��õ���controlRect�������
 // <4>	��������Ҫ����ʵ��drawItemText���������øú�����Ϊ�գ�����Ҫ��drawItemText���������ı�
 // <5> ���������ı��������ڴ˴����д���

	// ����һ�����ø���Ļ��ƿؼ�����
	QProxyStyle::drawControl(element, option, painter, widget);

	// ����������»���tab��ǩҳ�ı�
	if (element == CE_TabBarTabLabel) {
		if (const QStyleOptionTab* tab = qstyleoption_cast<const QStyleOptionTab*>(option)) {
			QRect controlRect = tab->rect;

			QString tabText;
			if (m_orientation == Qt::Vertical)
			{
				// ���ı��ַ������д���
				for (int i = 0; i < tab->text.length(); i++)
				{
					tabText.append(tab->text.at(i));
					tabText.append('\n');
				}
				if (tabText.length() > 1)
					tabText = tabText.mid(0, tabText.length() - 1);
			}
			else
				tabText = tab->text;

			// �ı����ж���
			QTextOption option;
			option.setAlignment(Qt::AlignCenter);
			QPen pen = painter->pen();
			pen.setColor(tab->palette.color(QPalette::WindowText));	// �ı���ɫ
			painter->setPen(pen);
			painter->drawText(controlRect, tabText, option);
		}
	}
}

void TabBarStyle::drawItemText(QPainter* painter, const QRect& rect, int flags, const QPalette& pal, bool enabled, const QString& text, QPalette::ColorRole textRole /*= QPalette::NoRole*/) const
{
	// ��д�麯�������Ǻ�������ʲô������д��ԭ�����£�
	// <1> ��ΪdrawControl�����еõ���controlRect������tab��ǩҳ�Ĵ�С��tab��ǩҳָĳһ��ѡ�ҳ�棬����ָ����tabBar��
	// <2> ���˴�rect�õ��Ĳ�֪����ʲô��С
	// <3> �������Ծ���drawControl�����л����ı��ˣ���drawControl�����������Ѿ����ַ��������д������»����ı��ˣ�
}

QSize TabBarStyle::sizeFromContents(QStyle::ContentsType type, const QStyleOption* option, const QSize& contentsSize, const QWidget* widget /*= nullptr*/) const
{
	QSize size = contentsSize;
	if (type == CT_TabBarTab)
	{
		if (m_orientation == Qt::Vertical)
		{
			size.rwidth() += 10;
			size.rheight() += 20;
		}
		else // m_orientation == Qt::Horizontal
		{
			size.transpose();//��tabҳ��ǩ��WEST���򣬲�������ˮƽ��������ʱʹ�ã�
			size.rwidth() += 10;
			size.rheight() += 50;
		}
	}

	return size;
}
