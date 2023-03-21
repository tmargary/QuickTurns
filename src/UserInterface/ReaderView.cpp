#include "ReaderView.h"

ReaderView::ReaderView(QWidget *parent) : QWidget(parent) {
    // Create the top part of the window
    QPushButton *leftButton = new QPushButton("Left");
    QPushButton *middleButton = new QPushButton("Middle");
    QPushButton *rightButton = new QPushButton("Right");
    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->addWidget(leftButton);
    topLayout->addWidget(new QFrame);
    topLayout->addWidget(middleButton);
    topLayout->addWidget(new QFrame);
    topLayout->addWidget(rightButton);
    
    // Create the middle part of the window
    QLabel *textLabel = new QLabel("Sample Text");
    QVBoxLayout *middleLayout = new QVBoxLayout;
    middleLayout->addWidget(textLabel);
    middleLayout->addStretch();
    
    // Create the bottom part of the window
    QPushButton *bottomLeftButton = new QPushButton("Left");
    QPushButton *bottomMiddleButton = new QPushButton("Middle");
    QPushButton *bottomRightButton = new QPushButton("Right");
    QHBoxLayout *bottomLayout = new QHBoxLayout;
    bottomLayout->addWidget(bottomLeftButton);
    bottomLayout->addWidget(new QFrame);
    bottomLayout->addWidget(bottomMiddleButton);
    bottomLayout->addWidget(new QFrame);
    bottomLayout->addWidget(bottomRightButton);
    
    // Create the main layout and add the three parts
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(middleLayout);
    mainLayout->addLayout(bottomLayout);
    
    // Set the main layout for the window
    setLayout(mainLayout);
}
