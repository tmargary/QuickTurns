#include "QuickTurns.h"
#include <QHBoxLayout>
#include "ReaderView.h"

QuickTurns::QuickTurns(QWidget* parent): QWidget(parent) {
    QHBoxLayout *layout = new QHBoxLayout(parent);
    this->setLayout(layout);
    button = new QPushButton("Button");
    button->setStyleSheet("background-color:green;");
    layout->addWidget(button);
    QObject::connect(button, &QPushButton::clicked, [=](){
        QString fileName = QFileDialog::getOpenFileName(nullptr, "Open File", QDir::homePath());
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
