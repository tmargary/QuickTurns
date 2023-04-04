#include <QPushButton>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QtCore/QTextStream>
#include <iostream>

#include "HomeView.h"
#include "ReaderView.h"

HomeView::HomeView(QWidget *parent) : QWidget(parent) {
    layout = new QHBoxLayout(parent);
    this->setLayout(layout);
    button = new QPushButton("Button");
    button->setStyleSheet("background-color:green;");
    layout->addWidget(button);

    // Set the path to the configuration file
    configFilePath = QCoreApplication::applicationDirPath() + "/config.txt";

    // Load the buttons from the configuration file
    loadButtonConfig();

    QObject::connect(button, &QPushButton::clicked, [=]() {
        const QString fileName = QFileDialog::getOpenFileName(nullptr, "Open File", QDir::homePath());
        if (!fileName.isEmpty()) {
            // Copy the file to a directory
            QString destinationPath = QCoreApplication::applicationDirPath() + "/files/" + QFileInfo(fileName).fileName();
            QFile::copy(fileName, destinationPath);

            QPushButton *newButton = new QPushButton(destinationPath);
            newButton->setStyleSheet("background-color: blue;");
            layout->addWidget(newButton);
            ReaderView *readerView = new ReaderView/*(destinationPath)*/;
            QObject::connect(newButton, &QPushButton::clicked, [=]() {
                readerView->show();
            });
            newButton->show();

            // Save the new button's file path to the configuration file
            saveButtonConfig(destinationPath);
        }
    });
    button->show();
}

void HomeView::saveButtonConfig(const QString &filePath) {
    QFile configFile(configFilePath);
    if (configFile.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&configFile);
        out << filePath << "\n";
        configFile.close();
    }
}

void HomeView::loadButtonConfig() {
    QFile configFile(configFilePath);
    if (configFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&configFile);
        while (!in.atEnd()) {
            QString filePath = in.readLine();
            QPushButton *newButton = new QPushButton(filePath);
            newButton->setStyleSheet("background-color: blue;");
            layout->addWidget(newButton);
            ReaderView *readerView = new ReaderView;
            QObject::connect(newButton, &QPushButton::clicked, [=]() {
                readerView->show();
            });
            newButton->show();
        }
        configFile.close();
    }
}

#include "moc_HomeView.cpp"