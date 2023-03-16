#pragma once

#include <QHBoxLayout>
#include <QPushButton>
#include <QWidget>

class MainView : public QWidget
{
  public:
    MainView(QWidget *parent = nullptr);

  private:
    void addButton(QHBoxLayout *);
    QPushButton *button{nullptr};
};