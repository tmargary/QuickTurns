#include <QPushButton>
#include <QFileDialog>
#include <QHBoxLayout>

#include "MainView/MainView.h"
#include "ReaderView/ReaderView.h"

MainView::MainView(QWidget* parent): QWidget(parent) {
    QHBoxLayout *layout = new QHBoxLayout(parent);
    this->setLayout(layout);
    button = new QPushButton("Button");
    button->setStyleSheet("background-color:green;");
    layout->addWidget(button);
    QObject::connect(button, &QPushButton::clicked, [=](){
        const QString fileName = QFileDialog::getOpenFileName(nullptr, "Open File", QDir::homePath());
        if (!fileName.isEmpty()) {
            QPushButton* newButton = new QPushButton(fileName);
            newButton->setStyleSheet("background-color: blue;");
            layout->addWidget(newButton);
            ReaderView* readerView = new ReaderView();
            QObject::connect(newButton, &QPushButton::clicked, [=](){
                readerView->show();
            });
            newButton->show();
        }
    });
    button->show();
}
