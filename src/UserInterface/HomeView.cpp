#include <QCoreApplication>
#include <QFileDialog>
#include <QHeaderView>
#include <QTableWidgetItem>

#include "ArchiveExtractor.h"
#include "BookMetadata.h"
#include "DataBase.h"
#include "HomeView.h"
#include "StringOp.h"

HomeView::HomeView(const QString &folderPath, QWidget *parent)
    : QWidget(parent), m_folderPath(folderPath.toStdString()), database((m_folderPath + "/bookdb.db"))

{
    layout = new QVBoxLayout(parent);
    this->setLayout(layout);

    setupTableWidget();
    setupAddFileButton();
}

void HomeView::addBookToTableWidget(const QString &bookName, const QString &bookAuthor, const QString &bookDate,
                                    const QString &bookPath)
{
    int row = tableWidget->rowCount();
    tableWidget->insertRow(row);

    QTableWidgetItem *nameItem = new QTableWidgetItem(bookName);
    nameItem->setData(Qt::UserRole, bookPath); // Store the bookPath in the item
    tableWidget->setItem(row, 0, nameItem);

    QTableWidgetItem *authorItem = new QTableWidgetItem(bookAuthor);
    authorItem->setData(Qt::UserRole, bookPath); // Store the bookPath in the item
    tableWidget->setItem(row, 1, authorItem);

    QTableWidgetItem *dateItem = new QTableWidgetItem(bookDate);
    dateItem->setData(Qt::UserRole, bookPath); // Store the bookPath in the item
    tableWidget->setItem(row, 2, dateItem);
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
        if (success)
        {
            break;
        }
    }
}

void HomeView::addBookToDatabaseAndTableWidget(const Book &addedBookMeta, const fs::path &destinationPath)
{
    int bookId = database.addBookToDatabase(addedBookMeta);
    QString bookName = QString::fromStdString(addedBookMeta.title.value_or(""));
    QString bookAuthor = QString::fromStdString(addedBookMeta.author.value_or(""));
    QString bookDate = QString::fromStdString(addedBookMeta.date.value_or(""));

    addBookToTableWidget(bookName, bookAuthor, bookDate, QString::fromStdString(destinationPath.string()));
}

void HomeView::handleButtonClick()
{
    namespace fs = std::filesystem;
    const QString filePath = QFileDialog::getOpenFileName(nullptr, "Open File", QDir::homePath());
    if (!filePath.isEmpty())
    {
        Book addedBookMeta = parseMetadataAndCheckDatabase(filePath);
        if (!addedBookMeta.title)
        {
            return;
        }

        fs::path destinationPath = fs::path(m_folderPath) /
                                   fs::path(createUnderscoreName(addedBookMeta.author.value_or("unknown"))) /
                                   fs::path("sample.epub");

        addedBookMeta.bookPath = destinationPath.string();

        QDir destinationDir;
        if (!createDestinationDirectory(destinationDir, destinationPath))
        {
            return;
        }

        copyBookAndCover(filePath, destinationPath);

        addBookToDatabaseAndTableWidget(addedBookMeta, destinationPath);
    }
}

void HomeView::setupTableWidget()
{
    tableWidget = new QTableWidget;
    tableWidget->setColumnCount(3); // Set the number of columns to 3
    tableWidget->setHorizontalHeaderLabels(QStringList() << "Book Name"
                                                         << "Author"
                                                         << "Date"); // Add column headers
    tableWidget->horizontalHeader()->setStretchLastSection(true);
    tableWidget->setColumnWidth(0, tableWidget->width() *
                                       0.5); // Set the width of the "Book Name" column to 50% of the total width
    layout->addWidget(tableWidget);
    // Load the items from the database
    std::map<int, Book> *bookMap = database.getBooksList();
    if (bookMap)
    {
        for (const auto &pair : *bookMap)
        {
            QString bookName = QString::fromStdString(pair.second.title.value_or(""));
            QString bookAuthor = QString::fromStdString(pair.second.author.value_or(""));
            QString bookDate = QString::fromStdString(pair.second.date.value_or(""));
            QString bookPath = QString::fromStdString(pair.second.bookPath);
            addBookToTableWidget(bookName, bookAuthor, bookDate,
                                 bookPath); // Add the author name and date to the table widget
        }
        delete bookMap;
    }

    QObject::connect(tableWidget, &QTableWidget::itemClicked, [=](QTableWidgetItem *item) {
        QString bookPath = item->data(Qt::UserRole).toString(); // Retrieve the bookPath from the item
        emit itemClicked(bookPath);
    });
}

#include "moc_HomeView.cpp"
