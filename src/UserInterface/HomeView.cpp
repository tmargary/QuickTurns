#include <QCoreApplication>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QListWidget>
#include <QListWidgetItem>
#include <QtCore/QTextStream>
#include <iostream>

#include "BookMetadata.h"
#include "ArchiveExtractor.h"
#include "DataBase.h"
#include "HomeView.h"
#include "ReaderView.h"

HomeView::HomeView(const QString &folderPath, QWidget *parent)
    : QWidget(parent), m_folderPath(folderPath), database((m_folderPath + "/bookdb.db").toStdString())

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
    setButtonStyle(addFileButton);
    addFileButton->setFixedHeight(30);

    layout->addWidget(addFileButton);

    QObject::connect(addFileButton, &QPushButton::clicked, [=]() { handleButtonClick(); });
}

void HomeView::setButtonStyle(QPushButton *button)
{
    button->setStyleSheet("QPushButton { background-color: #f7f7f7; border-radius: 8px; color: black; }"
                          "QPushButton:hover { background-color: #e3e3e3; }"
                          "QPushButton:pressed { background-color: #d1d1d1; }");
}

void HomeView::handleButtonClick()
{
    const QString filePath = QFileDialog::getOpenFileName(nullptr, "Open File", QDir::homePath());

    if (!filePath.isEmpty())
    {
        QString destinationPath = filePath;
        QFile::copy(filePath, destinationPath);

        // Parse metadata and store it in a Book object
        Book addedBook = parseMetadata(destinationPath.toStdString());

        addedBook.bookPath = destinationPath.toStdString();

        int bookId = addBookToDatabase(destinationPath.toStdString());

        QString bookName = QString::fromStdString(addedBook.title.value_or(""));

        addBookToListWidget(bookName, destinationPath);
    }
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
            QString bookName = QString::fromStdString(pair.second.title.value_or(""));
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

int HomeView::addBookToDatabase(const std::string &filePath)
{
    Book::Builder builder = Book::create();
    builder.setBookPath(filePath)
           .setTitle("bName")
           .setAuthor("aName")
           .setLastPage(0)
           .setDate("1999");

    Book book = builder.build();
    int bookId = database.addBookToDatabase(book);
    return bookId;
}


#include "moc_HomeView.cpp"
