#pragma once

#include <QWidget>

class QuickTurns : public QWidget{
public:
     QuickTurns(QWidget* parent = nullptr);
private:
    QPushButton* button{nullptr};
};