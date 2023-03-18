#pragma once

#include <QtWidgets>

class ReaderView : public QWidget {
public:
    ReaderView(QWidget *parent = nullptr);
private:
    void  chooseBackColor(QPushButton*);

};