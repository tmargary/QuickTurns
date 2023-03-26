#pragma once

#include <QPushButton>
#include <QWidget>

class HomeView : public QWidget
{
  public:
    HomeView(QWidget *parent = nullptr);

  private:
    QPushButton *button{nullptr};
};