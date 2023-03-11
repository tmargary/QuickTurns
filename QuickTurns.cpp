#include "QuickTurns.h"
#include <QHBoxLayout>

QuickTurns::QuickTurns(QWidget* parent): QWidget(parent) {
    QHBoxLayout *layout = new QHBoxLayout(parent);
    this->setLayout(layout);
    button = new QPushButton("Button");
    button->setStyleSheet("background-color:green;");
    layout->addWidget(button);
    QObject::connect(button, &QPushButton::clicked, [](){
        QFileDialog::getOpenFileName(nullptr, "Open File", QDir::homePath());
    });
    button->show();
}
