#pragma once

#include <QWidget>

class MainView : public QWidget{
public:
     MainView(QWidget* parent = nullptr);
private:
    QPushButton* button{nullptr};
};