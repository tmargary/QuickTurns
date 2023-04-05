#include "StackedView.h"

StackedView::StackedView(QWidget *parent)
    : QWidget(parent), homeView(new HomeView), readerView(new ReaderView), stackedWidget(new QStackedWidget),
      button(new QPushButton("Switch View"))
{
    showNormal();

    stackedWidget->addWidget(homeView);
    stackedWidget->addWidget(readerView);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(stackedWidget);
    layout->addWidget(button);
    button->hide();
    setLayout(layout);

    connect(homeView, &HomeView::itemClicked, this, &StackedView::switchToReaderView);
    connect(stackedWidget, &QStackedWidget::currentChanged, this, [this](int index) {
        if (index == 0)
        {
            button->hide();
        }
        else
        {
            button->show();
            connect(button, &QPushButton::clicked, this, &StackedView::switchView);
        }
    });
}

void StackedView::switchToReaderView(const QString &filePath)
{
    readerView->loadFile(filePath);
    stackedWidget->setCurrentIndex(1);
}

void StackedView::switchView()
{
    if (stackedWidget->currentIndex() == 0)
    {
        stackedWidget->setCurrentIndex(1);
    }
    else
    {
        stackedWidget->setCurrentIndex(0);
    }
}

#include "moc_StackedView.cpp"