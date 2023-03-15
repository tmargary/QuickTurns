#pragma once

#include <QWidget>
#include <QPushButton>

class QuickTurns : public QWidget{
public:
     QuickTurns(QWidget* parent = nullptr);
private:
    QPushButton* button{nullptr};
};