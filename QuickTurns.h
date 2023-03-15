#pragma once

#include <QWidget>
#include <QPushButton>
#include <QFileDialog>

class QuickTurns : public QWidget{
public:
     QuickTurns(QWidget* parent = nullptr);
private:
    QPushButton* button{nullptr};
};