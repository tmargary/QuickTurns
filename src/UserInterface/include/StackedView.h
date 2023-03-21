#pragma once

#include <QWidget>
#include <QPushButton>
#include <QStackedWidget>

#include "HomeView.h"
#include "ReaderView.h"

class StackedView : public QWidget {
    // Q_OBJECT  // Remove this line

public:
    StackedView(QWidget *parent = nullptr);

private slots:
    void switchView();

private:
    HomeView *homeView;
    ReaderView *readerView;
    QPushButton *button;
    QStackedWidget *stackedWidget;
};
