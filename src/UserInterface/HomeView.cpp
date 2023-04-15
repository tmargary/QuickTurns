#include <QCoreApplication>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QListWidget>
#include <QListWidgetItem>
#include <QtCore/QTextStream>
#include <iostream>

#include "HomeView.h"
#include "ReaderView.h"

HomeView::HomeView(QWidget *parent) : QWidget(parent)
{
    layout = new QVBoxLayout(parent);
    this->setLayout(layout);

    // Set the path to the configuration file
    configFilePath = QCoreApplication::applicationDirPath() + "/config.txt";

    setupListWidget();
    setupAddFileButton();
}

void HomeView::setupAddFileButton()
{
    QPushButton *addFileButton = new QPushButton("Add File");
    addFileButton->setStyleSheet("QPushButton { background-color: #f7f7f7; border-radius: 8px; color: black; }"
                                 "QPushButton:hover { background-color: #e3e3e3; }"
                                 "QPushButton:pressed { background-color: #d1d1d1; }");
    addFileButton->setFixedHeight(30);

    layout->addWidget(addFileButton);

    QObject::connect(addFileButton, &QPushButton::clicked, [=]() {
        const QString fileName = QFileDialog::getOpenFileName(nullptr, "Open File", QDir::homePath());
        if (!fileName.isEmpty())
        {
            // Copy the file to a directory
            QString destinationPath =
                QCoreApplication::applicationDirPath() + "/../test/data/" + QFileInfo(fileName).fileName();
            QFile::copy(fileName, destinationPath);

            QListWidgetItem *newItem = new QListWidgetItem(destinationPath);
            listWidget->addItem(newItem);

            // Save the new item's file path to the configuration file
            saveButtonConfig(destinationPath);
        }
    });
}

void HomeView::setupListWidget()
{
    listWidget = new QListWidget;
    layout->addWidget(listWidget);

    // Load the items from the configuration file
    loadButtonConfig();

    QObject::connect(listWidget, &QListWidget::itemClicked,
                     [=](QListWidgetItem *item) { emit itemClicked(item->text()); });
}

void HomeView::saveButtonConfig(const QString &filePath)
{
    QFile configFile(configFilePath);
    if (configFile.open(QIODevice::Append | QIODevice::Text))
    {
        QTextStream out(&configFile);
        out << filePath << "\n";
        configFile.close();
    }
}

void HomeView::loadButtonConfig()
{
    QFile configFile(configFilePath);
    if (!configFile.open(QIODevice::ReadOnly))
    {
        return;
    }

    QTextStream stream(&configFile);
    while (!stream.atEnd())
    {
        QString filePath = stream.readLine();

        QListWidgetItem *newItem = new QListWidgetItem(filePath);
        listWidget->addItem(newItem);
    }

    configFile.close();
}

#include "moc_HomeView.cpp"
