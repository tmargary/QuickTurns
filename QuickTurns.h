#ifndef QUICKTURNS_H
#define QUICKTURNS_H

#include <QWidget>
#include <QPushButton>
#include <QFileDialog>

class QuickTurns : public QWidget{
public:
     QuickTurns(QWidget* parent = nullptr);
private:
    QPushButton* button/*("Open File Explorer", nullptr)*/;
};

#endif