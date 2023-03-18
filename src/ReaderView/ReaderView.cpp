#include "ReaderView/ReaderView.h"
#include <QLabel>
#include <QPixmap>
#include <QSize>
#include <QIcon>
#include <memory>
#include <string>
ReaderView::ReaderView(QWidget *parent) : QWidget(parent) {
    // Create the top part of the window
    bool isClicked=false;
   
    QPushButton* backgroundButton=new QPushButton(this);
    backgroundButton->setGeometry(140,100,100,100);
 chooseBackColor(backgroundButton);
    


    QPushButton *leftButton = new QPushButton("Left");
    QPushButton *middleButton = new QPushButton("Middle");
    QPushButton *rightButton = new QPushButton("Right");
    QHBoxLayout *topLayout = new QHBoxLayout;

    
   
        QPushButton* homeButton;
    homeButton=new QPushButton(this);
    homeButton->setGeometry(10,100,100,100);
    QPixmap* p=new QPixmap("C:/Users/User/Desktop/QuickTurns/src/IconFolder/home.png");
    QIcon icon1(*p);
    int w1 = homeButton->width();
    int h1 = homeButton->height();
    homeButton->setIcon(icon1);
    homeButton->setIconSize(QSize(w1,h1));
    

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

void ReaderView::chooseBackColor(QPushButton* backgroundButton){
   QPixmap* p1=new QPixmap("C:/Users/User/Desktop/QuickTurns/src/IconFolder/color.png");
    int h =backgroundButton->height();
    int w=backgroundButton->width();
    QSize iconSize(h,w);
    
    backgroundButton->setIcon(QIcon(QPixmap(p1->scaled(w,h,Qt::KeepAspectRatio))));
    backgroundButton->setIconSize(iconSize);

    
    QWidget* obj=new QWidget();
    obj->setWindowIcon(QIcon(QPixmap(p1->scaled(w,h,Qt::KeepAspectRatio))));
    obj->setWindowTitle("colorMania");
     QObject::connect(backgroundButton, &QPushButton::clicked, [obj,this](){
        
         QPushButton* c1=new QPushButton(obj);
           QPushButton* c2=new QPushButton(obj);
         QPushButton* c3=new QPushButton(obj);
         QPushButton* c4=new QPushButton(obj);
         QPushButton* c5=new QPushButton(obj);
          
          c1->setGeometry(20,50,50,50);
         c2->setGeometry(120,50,50,50);
        c3->setGeometry(220,50,50,50);
        c4->setGeometry(320,50,50,50);
         c5->setGeometry(420,50,50,50);
         
       
       c1->setStyleSheet("background-color:white;"
                           "border: 1px solid white;"
                           "border-radius: 15px;"
                           "font-size: 25px;"
                           );


        c2->setStyleSheet("background-color: #f6edd3;"
                           "border: 1px solid white;"
                           "border-radius: 15px;"
                           "font-size: 25px;"
                           );
                           
       
        c3->setStyleSheet("background-color:wheat;"
                              "border: 1px solid white;"
                              "border-radius: 15px;"
                               "font-size: 25px;"
                               );
        c4->setStyleSheet("background-color:#f6dab1;"
                              "border: 1px solid white;"
                              "border-radius: 15px;"
                              "font-size: 25px;"
                              );
        c5->setStyleSheet("background-color:#d2c5b6;"
                            "border: 1px solid white;"
                            "border-radius: 15px;"
                            "font-size: 25px;"
                            );

             QObject::connect(c1, &QPushButton::clicked, [this](){
                 this->setStyleSheet("background-color:white;");});
        
              QObject::connect(c2, &QPushButton::clicked, [this](){
                 this->setStyleSheet("background-color:#f6edd3;");});
        
           QObject::connect(c3, &QPushButton::clicked, [this](){
                this->setStyleSheet("background-color:wheat;");});

       
             QObject::connect(c4, &QPushButton::clicked, [this](){
                this->setStyleSheet("background-color:#f6dab1;");});
     
         
            QObject::connect(c5, &QPushButton::clicked, [this](){
                this->setStyleSheet("background-color:#d2c5b6;");});
            obj->show();

        
   
});

}