#pragma once

#include <QWidget>
#include <QPushButton>
#include <QFileDialog>

class MainView : public QWidget{
public:
     MainView(QWidget* parent = nullptr);
private:
    QPushButton* button/*("Open File Explorer", nullptr)*/;
};