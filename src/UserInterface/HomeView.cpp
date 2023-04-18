#include <QCoreApplication>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QListWidget>
#include <QListWidgetItem>
#include <QtCore/QTextStream>
#include <iostream>

#include "ArchiveExtractor.h"
#include "BookMetadata.h"
#include "DataBase.h"
#include "HomeView.h"
#include "ReaderView.h"
#include "StringOp.h"

HomeView::HomeView(const QString &folderPath, QWidget *parent)
    : QWidget(parent), m_folderPath(folderPath.toStdString()), database((m_folderPath + "/bookdb.db"))

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

Book HomeView::parseMetadataAndCheckDatabase(const QString &filePath)
{
    Book addedBookMeta = parseMetadata(filePath.toStdString());

    if (database.bookExists(addedBookMeta))
    {
        qDebug() << "Book already exists in the database.";
        return {};
    }

    return addedBookMeta;
}

bool HomeView::createDestinationDirectory(QDir &destinationDir, const fs::path &destinationPath)
{
    destinationDir = QFileInfo(destinationPath).dir();
    if (!destinationDir.mkpath(destinationDir.path()))
    {
        qDebug() << "Failed to create directory" << destinationDir.path();
        return false;
    }

    return true;
}

void HomeView::copyBookAndCover(const QString &filePath, const fs::path &destinationPath)
{
    QFile::copy(filePath, QString::fromStdString(destinationPath.string()));

    std::unique_ptr<ArchiveExtractor> extractor = createExtractor(destinationPath, "");
    fs::path sourcePath = fs::path(filePath.toStdString());
    std::string cover;
    std::vector<std::string> coverExtensions = {".png", ".jpg", ".jpeg", ".gif"};
    for (const auto &ext : coverExtensions)
    {
        cover = "cover" + ext;
        fs::path destinationCoverPath = destinationPath.parent_path() / fs::path(cover);
        bool success = extractor->extractSpecificEntry(cover, destinationCoverPath);
        if (success) {break;}
    }
}

void HomeView::addBookToDatabaseAndListWidget(const Book &addedBookMeta, const fs::path &destinationPath)
{
    int bookId = database.addBookToDatabase(addedBookMeta);

    QString bookName = QString::fromStdString(addedBookMeta.title.value_or(""));

    addBookToListWidget(bookName, QString::fromStdString(destinationPath.string()));
}

void HomeView::handleButtonClick()
{
    namespace fs = std::filesystem;
    const QString filePath = QFileDialog::getOpenFileName(nullptr, "Open File", QDir::homePath());

    if (!filePath.isEmpty())
    {
        Book addedBookMeta = parseMetadataAndCheckDatabase(filePath);
        if (!addedBookMeta.title) { return; }

        fs::path destinationPath = fs::path(m_folderPath) /
                                   fs::path(createUnderscoreName(addedBookMeta.author.value_or("unknown"))) /
                                   fs::path("sample.epub");

        addedBookMeta.bookPath = destinationPath.string();

        QDir destinationDir;
        if (!createDestinationDirectory(destinationDir, destinationPath)) { return; }

        copyBookAndCover(filePath, destinationPath);

        addBookToDatabaseAndListWidget(addedBookMeta, destinationPath);
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

#include "moc_HomeView.cpp"
