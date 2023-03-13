#ifndef QUICKTURNS_H
#define QUICKTURNS_H

#include <QWidget>
#include <QPushButton>
#include <QFileDialog>

class MainView : public QWidget{
public:
     MainView(QWidget* parent = nullptr);
private:
    QPushButton* button/*("Open File Explorer", nullptr)*/;
};

#endif