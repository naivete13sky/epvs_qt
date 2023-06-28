#pragma once
#include <QtWidgets/QComboBox>
#include <QKeyEvent>


class CustomComboBox :public QComboBox {
    Q_OBJECT

public:
    CustomComboBox(QWidget* parent = nullptr);

    ~CustomComboBox();

signals:
    void triggerStr(QString);

protected:
    void keyPressEvent(QKeyEvent* event) override;

};