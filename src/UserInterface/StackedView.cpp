#include "StackedView.h"

StackedView::StackedView(QWidget *parent)
    : QWidget(parent), homeView(new HomeView), readerView(new ReaderView), stackedWidget(new QStackedWidget),
      homeButton(new QPushButton)
{
    showNormal();

    // Set the button icon and style
    homeButton->setText(QString::fromUtf8("\xF0\x9F\x8F\xA0 Home"));
    homeButton->setStyleSheet("QPushButton { background-color: #f7f7f7; border-radius: 8px; color: black; }"
                          "QPushButton:hover { background-color: #e3e3e3; }"
                          "QPushButton:pressed { background-color: #d1d1d1; }");
    homeButton->setFixedHeight(30);
    stackedWidget->addWidget(homeView);
    stackedWidget->addWidget(readerView);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(stackedWidget);
    layout->addWidget(homeButton);
    homeButton->hide();
    setLayout(layout);

    connect(homeView, &HomeView::itemClicked, this, &StackedView::switchToReaderView);
    connect(stackedWidget, &QStackedWidget::currentChanged, this, [this](int index) {
        if (index == 0)
        {
            homeButton->hide();
        }
        else
        {
            homeButton->show();
            connect(homeButton, &QPushButton::clicked, this, &StackedView::switchView);
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