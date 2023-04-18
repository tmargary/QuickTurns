#pragma once

#include <QWidget>
#include <QPushButton>
#include <QStackedWidget>

#include "HomeView.h"
#include "ReaderView.h"

class StackedView : public QWidget
{
    Q_OBJECT

public:
    explicit StackedView(const QString &folderPath, QWidget *parent = nullptr);
    
public slots:
    void switchToReaderView(const QString &filePath);
    void switchView();

private:
    HomeView *homeView;
    ReaderView *readerView;
    QStackedWidget *stackedWidget;
    QPushButton *homeButton;
};
