#pragma once

#include <QWidget>
#include <QPushButton>

class MainView : public QWidget{
public:
     MainView(QWidget* parent = nullptr);
private:
    QPushButton* button{nullptr};
};