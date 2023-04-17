#include <QCoreApplication>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QListWidget>
#include <QListWidgetItem>
#include <QtCore/QTextStream>
#include <iostream>

#include "DataBase.h"
#include "HomeView.h"
#include "ReaderView.h"

HomeView::HomeView(const QString &folderPath, QWidget *parent)
    : QWidget(parent), database((folderPath + "/bookdb.db").toStdString())
{
    layout = new QVBoxLayout(parent);
    this->setLayout(layout);

    setupListWidget();
    setupAddFileButton();
}

void HomeView::addBookToListWidget(const QString &bookName, const QString &bookPath)
{
    QListWidgetItem *newItem = new QListWidgetItem(bookName);
    newItem->setData(Qt::UserRole, bookPath); // Store the bookPath in the item
    listWidget->addItem(newItem);
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

            // Add the book to the database
            int bookId = saveButtonConfig(destinationPath.toStdString());

            // Get the bookName from the database
            Book addedBook = database.getBookById(bookId);
            QString bookName = QString::fromStdString(addedBook.bookName);

            // Add the book to the list widget
            addBookToListWidget(bookName, destinationPath);

            // Save the new item's file path to the configuration file
            saveButtonConfig(destinationPath.toStdString());
        }
    });
}

void HomeView::setupListWidget()
{
    listWidget = new QListWidget;
    layout->addWidget(listWidget);

    // Load the items from the database
    std::map<int, Book> *bookMap = database.getBooksList();
    if (bookMap)
    {
        for (const auto &pair : *bookMap)
        {
            QString bookName = QString::fromStdString(pair.second.bookName);
            QString bookPath = QString::fromStdString(pair.second.bookPath);
            addBookToListWidget(bookName, bookPath);
        }
        delete bookMap;
    }

    QObject::connect(listWidget, &QListWidget::itemClicked, [=](QListWidgetItem *item) {
        QString bookPath = item->data(Qt::UserRole).toString(); // Retrieve the bookPath from the item
        emit itemClicked(bookPath);
    });
}

int HomeView::saveButtonConfig(const std::string &filePath)
{
    Book girq(filePath, "bName", "aName", 1999, 0);
    int bookId = database.addBookToDatabase(girq);
    return bookId;
}

#include "moc_HomeView.cpp"
