#include "StackedView.h"

StackedView::StackedView(QWidget *parent)
    : QWidget(parent), homeView(new HomeView), readerView(new ReaderView), button(new QPushButton("Switch View")),
      stackedWidget(new QStackedWidget)
{

    // Enter full screen mode
    if (isFullScreen())
    {
        showNormal();
    }
    else
    {
        showFullScreen();
    }

    stackedWidget->addWidget(homeView);
    stackedWidget->addWidget(readerView);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(stackedWidget);
    layout->addWidget(button);
    setLayout(layout);

    connect(button, &QPushButton::clicked, this, &StackedView::switchView);
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
