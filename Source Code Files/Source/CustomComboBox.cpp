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
        QString text = currentText();  // 获取当前文本
        qDebug() << "回车键按下，当前文本为：" << text;
        // 在这里可以执行任何你想要的操作
        emit triggerStr("enter");
    }
    else {
        // print('cc2')
        QComboBox::keyPressEvent(event);
    }
}
