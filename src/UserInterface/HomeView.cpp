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

QString HomeView::createDestinationPath(const QString &fileName)
{
    return QCoreApplication::applicationDirPath() + "/../test/data/" + QFileInfo(fileName).fileName();
}

void HomeView::handleButtonClick()
{
    const QString fileName = QFileDialog::getOpenFileName(nullptr, "Open File", QDir::homePath());

    // Extract the epub archive
    std::unique_ptr<ArchiveExtractor> extractor = createExtractor(fileName.toStdString());
    const std::string xmlContent = extractor->readSpecificEntry("content.opf");
    BookMetadata bookMeta = parseMetadata(xmlContent); 

    if (!fileName.isEmpty())
    {
        QString destinationPath = createDestinationPath(fileName);
        QFile::copy(fileName, destinationPath);

        int bookId = addBookToDatabase(destinationPath.toStdString());

        Book addedBook = database.getBookById(bookId);
        QString bookName = QString::fromStdString(addedBook.bookName);

        addBookToListWidget(bookName, destinationPath);

        addBookToDatabase(destinationPath.toStdString());
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

int HomeView::addBookToDatabase(const std::string &filePath)
{
    Book girq(filePath, "bName", "aName", 1999, 0);
    int bookId = database.addBookToDatabase(girq);
    return bookId;
}

#include "moc_HomeView.cpp"
