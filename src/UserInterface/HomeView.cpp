#include <QCoreApplication>
#include <QFileDialog>
#include <QHeaderView>
#include <QMessageBox>
#include <QPair>
#include <QString>
#include <QTableWidgetItem>
#include <QVariant>
#include <string>

#include "ArchiveExtractor.h"
#include "BookMetadata.h"
#include "DataBase.h"
#include "HomeView.h"
#include "StringOp.h"

const int DELETE_BUTTON_HEIGHT = 30;
const int DELETE_BUTTON_WIDTH = 90;

HomeView::HomeView(const QString &folderPath, QWidget *parent)
    : QWidget(parent), m_folderPath(folderPath.toStdString()), database((m_folderPath + "/bookdb.db"))
{
    QGridLayout *mainLayout = new QGridLayout(parent);
    this->setLayout(mainLayout);

    setupAddFileButton();
    setupTableWidget();

    deleteBookButton = new QPushButton(this);
    deleteBookButton->setText(QString::fromUtf8("\xF0\x9F\x97\x91")); // Recycle bin emoji
    deleteBookButton->setToolTip("Delete Book");
    setButtonStyle(deleteBookButton);
    deleteBookButton->setFixedHeight(DELETE_BUTTON_HEIGHT);
    deleteBookButton->setFixedWidth(DELETE_BUTTON_WIDTH);
    connect(deleteBookButton, &QPushButton::clicked, this, &HomeView::handleDeleteBookClick);

    mainLayout->addWidget(tableWidget, 0, 0);

    // Create a QHBoxLayout to hold addFileButton and deleteBookButton
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(addFileButton);
    buttonLayout->addWidget(deleteBookButton);

    // Add the buttonLayout to the mainLayout
    mainLayout->addLayout(buttonLayout, 1, 0);

    QFrame *frame = new QFrame;
    QVBoxLayout *frameLayout = new QVBoxLayout(frame);

    // Divide the right side of the window into three vertical parts
    QVBoxLayout *rightLayout = new QVBoxLayout();
    rightLayout->addWidget(frame, 0);
    QSpacerItem *rightSpacer = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    rightLayout->addItem(rightSpacer);
    QWidget *rightWidget = new QWidget();
    rightWidget->setLayout(rightLayout);

    mainLayout->addWidget(rightWidget, 0, 1, 2, 1);

    coverLabel = new QLabel();
    coverLabel->setFixedSize(200, 300);
    coverLabel->setAlignment(Qt::AlignCenter);
    frameLayout->addWidget(coverLabel, 0, Qt::AlignCenter);

    // Add a spacer item to the bottom of the frameLayout
    QSpacerItem *frameSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);
    frameLayout->addItem(frameSpacer);

    metadataLabel = new QLabel();
    metadataLabel->setWordWrap(true);
    metadataLabel->setAlignment(Qt::AlignTop);
    metadataLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    metadataLabel->setFixedWidth(coverLabel->width());

    // Create a layout for the metadata label
    QVBoxLayout *metadataLayout = new QVBoxLayout();
    metadataLayout->addWidget(metadataLabel);
    metadataLayout->addSpacerItem(new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding));

    // Add a spacer item to the left of the metadata layout
    QSpacerItem *metadataSpacer = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    metadataLayout->insertSpacerItem(0, metadataSpacer);

    // Add the metadata layout to the rightLayout
    rightLayout->addLayout(metadataLayout);

    // Set stretch factor of first and second column to 1
    mainLayout->setColumnStretch(0, 1);
    mainLayout->setColumnStretch(1, 0);
}

void HomeView::addBookToTableWidget(int bookId, const QString &bookName, const QString &bookAuthor,
                                    const QString &bookDate, const QString &bookPath)
{
    int row = tableWidget->rowCount();
    tableWidget->insertRow(row);

    QPair<int, QString> bookData;
    bookData.first = bookId;    // Assuming bookId is of type int
    bookData.second = bookPath; // Assuming bookPath is of type QString

    QTableWidgetItem *nameItem = new QTableWidgetItem(bookName);
    nameItem->setData(Qt::UserRole, QVariant::fromValue(bookData)); // Store the bookPath in the item
    tableWidget->setItem(row, 0, nameItem);

    QTableWidgetItem *authorItem = new QTableWidgetItem(bookAuthor);
    authorItem->setData(Qt::UserRole, QVariant::fromValue(bookData)); // Store the bookPath in the item
    tableWidget->setItem(row, 1, authorItem);

    QTableWidgetItem *dateItem = new QTableWidgetItem(bookDate);
    dateItem->setData(Qt::UserRole, QVariant::fromValue(bookData)); // Store the bookPath in the item
    tableWidget->setItem(row, 2, dateItem);
}

void HomeView::setupAddFileButton()
{
    addFileButton = new QPushButton("Add");
    addFileButton->setFont(QFont("Segoe UI Emoji"));
    setButtonStyle(addFileButton);
    addFileButton->setFixedHeight(30);

    QObject::connect(addFileButton, &QPushButton::clicked, [=]() { handleButtonClick(); });
}

void HomeView::setButtonStyle(QPushButton *button)
{
    button->setStyleSheet("QPushButton { background-color: #cacfd2 ; border-radius: 8px; color: black; }"
                          "QPushButton:hover { background-color: #e3e3e3; }"
                          "QPushButton:pressed { background-color: #d1d1d1; }");
}

Book HomeView::parseMetadataAndCheckDatabase(const QString &filePath)
{
    try
    {
        Book addedBookMeta = parseMetadata(filePath.toStdString());

        if (database.bookExists(addedBookMeta))
        {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Book already exists");
            msgBox.setText("The selected book already exists.");
            msgBox.setStandardButtons(QMessageBox::Ok);
            msgBox.setDefaultButton(QMessageBox::Ok);

            int ret = msgBox.exec();
            if (ret == QMessageBox::Ok)
            {
                qDebug() << "User clicked Okay.";
            }

            return {};
        }

        return addedBookMeta;
    }
    catch (std::exception &e)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Error");
        msgBox.setText("Could not read the file: " + QString(e.what()));
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);

        int ret = msgBox.exec();
        if (ret == QMessageBox::Ok)
        {
            qDebug() << "User clicked Okay.";
        }

        return {};
    }
}

bool HomeView::createDestinationDirectory(QDir &destinationDir, const fs::path &destinationPath)
{
    destinationDir = QFileInfo(destinationPath).dir();
    if (!destinationDir.mkpath(destinationDir.path()))
    {
        qDebug() << "Failed to create directory" << destinationDir.path();
        QMessageBox msgBox;
        msgBox.setWindowTitle("Error");
        msgBox.setText("Failed to create directory: " + destinationDir.path());
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);

        int ret = msgBox.exec();
        if (ret == QMessageBox::Ok)
        {
            qDebug() << "User clicked Okay.";
        }

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
        qDebug() << std::string("Attempting to find " + cover).c_str();
        fs::path destinationCoverPath = destinationPath.parent_path() / fs::path(cover);
        bool success = extractor->extractSpecificEntry(cover, destinationCoverPath);
        if (success)
        {
            qDebug() << "Cover found!";
            break;
        }
    }
}

void HomeView::addBookToDatabaseAndTableWidget(const Book &addedBookMeta, const fs::path &destinationPath)
{
    int bookId = database.addBookToDatabase(addedBookMeta);
    QString bookName = QString::fromStdString(addedBookMeta.title.value_or("unknown"));
    QString bookAuthor = QString::fromStdString(addedBookMeta.author.value_or("unknown"));
    QString bookDate = QString::fromStdString(addedBookMeta.date.value_or("unknown"));

    addBookToTableWidget(bookId, bookName, bookAuthor, bookDate, QString::fromStdString(destinationPath.string()));
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

        std::string author = createUnderscoreName(addedBookMeta.author.value_or("unknown"));
        std::string bookName = createUnderscoreName(addedBookMeta.title.value_or("unknown"));

        fs::path destinationPath =
            fs::path(m_folderPath) / fs::path(author) / fs::path(bookName) / fs::path("sample.epub");

        addedBookMeta.bookPath = destinationPath.string();

        QDir destinationDir;
        if (!createDestinationDirectory(destinationDir, destinationPath))
        {
            return;
        }

        copyBookAndCover(filePath, destinationPath);

        addBookToDatabaseAndTableWidget(addedBookMeta, destinationPath);

        updateMetadataLabel(addedBookMeta);
        updateCoverLabel(destinationPath);
    }
}

void HomeView::handleDeleteBookClick()
{
    int selectedRow = tableWidget->currentRow();
    if (selectedRow >= 0)
    {
        QPair<int, QString> retrievedData =
            tableWidget->item(selectedRow, 0)->data(Qt::UserRole).value<QPair<int, QString>>();
        int bookId = retrievedData.first;

        // Remove the book file and directory from the filesystem
        std::string bookPath = database.getBookById(bookId).bookPath;
        std::filesystem::path bookFilePath(bookPath);
        std::filesystem::path bookDirPath = bookFilePath.parent_path();

        database.removeBook(bookId);
        tableWidget->removeRow(selectedRow);

        if (std::filesystem::exists(bookDirPath))
        {
            std::filesystem::remove_all(bookDirPath);
            std::cout << "bookDirPath" << bookDirPath << "is removed.\n";
        }

        metadataLabel->setText(""); // Clear the metadata label
        coverLabel->clear();        // Clear the cover label
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
    // Load the items from the database
    std::map<int, Book> *bookMap = database.getBooksList();
    if (bookMap)
    {
        for (const auto &pair : *bookMap)
        {
            int bookId = pair.first;
            QString bookName = QString::fromStdString(pair.second.title.value_or("unknown"));
            QString bookAuthor = QString::fromStdString(pair.second.author.value_or("unknown"));
            QString bookDate = QString::fromStdString(pair.second.date.value_or("unknown"));
            QString bookPath = QString::fromStdString(pair.second.bookPath);
            addBookToTableWidget(bookId, bookName, bookAuthor, bookDate,
                                 bookPath); // Add the author name and date to the table widget
        }
        delete bookMap;
    }

    QObject::connect(tableWidget, &QTableWidget::itemClicked, [=](QTableWidgetItem *item) {
        QPair<int, QString> retrievedData = item->data(Qt::UserRole).value<QPair<int, QString>>();
        int retrievedBookId = retrievedData.first;
        QString retrievedBookPath = retrievedData.second;

        QString bookPath = item->data(Qt::UserRole).toString(); // Retrieve the bookPath from the item
        updateMetadataAndCoverLabels(retrievedBookPath);
    });

    QObject::connect(tableWidget, &QTableWidget::itemDoubleClicked, [=](QTableWidgetItem *item) {
        QPair<int, QString> retrievedData = item->data(Qt::UserRole).value<QPair<int, QString>>();
        int retrievedBookId = retrievedData.first;
        QString retrievedBookPath = retrievedData.second;

        QString bookPath = item->data(Qt::UserRole).toString(); // Retrieve the bookPath from the item
        emit itemClicked(retrievedBookPath);
    });

    QObject::connect(tableWidget, &QTableWidget::currentItemChanged, this, &HomeView::updateSelectedBookLabels);
}

void HomeView::updateSelectedBookLabels(QTableWidgetItem *current, QTableWidgetItem *previous)
{
    Q_UNUSED(previous);
    if (current == nullptr)
    {
        metadataLabel->clear();
        coverLabel->clear();
        return;
    }
    QPair<int, QString> retrievedData = current->data(Qt::UserRole).value<QPair<int, QString>>();
    QString retrievedBookPath = retrievedData.second;

    updateMetadataAndCoverLabels(retrievedBookPath);
}

void HomeView::updateMetadataLabel(const Book &book)
{
    QString metadataText;
    if (book.title)
    {
        metadataText += "<b>Title:</b> " + QString::fromStdString(*book.title) + "<br>";
    }
    if (book.author)
    {
        metadataText += "<b>Author:</b> " + QString::fromStdString(*book.author) + "<br>";
    }
    if (book.publisher)
    {
        metadataText += "<b>Publisher:</b> " + QString::fromStdString(*book.publisher) + "<br>";
    }
    if (book.date)
    {
        metadataText += "<b>Date:</b> " + QString::fromStdString(*book.date) + "<br>";
    }
    metadataLabel->setText(metadataText);
}

void HomeView::updateCoverLabel(const fs::path &bookPath)
{
    Book bookMeta = database.getBookByPath(bookPath.string());

    QString parentPath = QFileInfo(QString::fromStdString(bookMeta.bookPath)).dir().path();
    QPixmap coverPixmap;

    std::vector<std::string> coverExtensions = {".png", ".jpg", ".jpeg", ".gif"};
    for (const auto &extension : coverExtensions)
    {
        QString coverFilePath = parentPath + "/cover" + QString::fromStdString(extension);
        coverPixmap = QPixmap(coverFilePath);
        if (!coverPixmap.isNull())
        {
            break;
        }
    }

    if (coverPixmap.isNull())
    {
        qDebug() << "Error loading cover image.";
        // Set default image to cover label
        coverPixmap = QPixmap("");
    }
    coverLabel->setPixmap(coverPixmap.scaled(coverLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void HomeView::updateMetadataAndCoverLabels(const QString &bookPath)
{
    Book book = database.getBookByPath(bookPath.toStdString());
    updateMetadataLabel(book);
    fs::path fsBookPath(bookPath.toStdString());
    updateCoverLabel(fsBookPath);
}

#include "moc_HomeView.cpp"