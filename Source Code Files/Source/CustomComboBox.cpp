#pragma execution_character_set("utf-8")
#include "./../Include/CustomComboBox.h"
#include <QtCore/QDebug>



CustomComboBox::CustomComboBox(QWidget* parent)
    : QComboBox(parent)
{
    




}



CustomComboBox::~CustomComboBox()
{}




void CustomComboBox::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
        QString text = currentText();  // ��ȡ��ǰ�ı�
        qDebug() << "�س������£���ǰ�ı�Ϊ��" << text;
        // ���������ִ���κ�����Ҫ�Ĳ���
        emit triggerStr("enter");
    }
    else {
        // print('cc2')
        QComboBox::keyPressEvent(event);
    }
}
