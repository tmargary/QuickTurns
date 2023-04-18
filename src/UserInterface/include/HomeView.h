#pragma once
#include <QDir>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTableWidget>

#include "DataBase.h"

namespace fs = std::filesystem;

class HomeView : public QWidget
{
    Q_OBJECT

  public:
    explicit HomeView(const QString &folderPath, QWidget *parent = nullptr);
    void setupTableWidget();
    void setupAddFileButton();
    void addBookToTableWidget(const QString &bookName, const QString &bookAuthor, const QString &bookDate,
                              const QString &bookPath);

        private : void setButtonStyle(QPushButton *button);
    QString createDestinationPath(const QString &fileName);
    bool bookExists(const Book &bookToCheck);
    void handleButtonClick();
    Book parseMetadataAndCheckDatabase(const QString &filePath);
    bool createDestinationDirectory(QDir &destinationDir, const fs::path &destinationPath);
    void copyBookAndCover(const QString &filePath, const fs::path &destinationPath);
    void addBookToDatabaseAndTableWidget(const Book &addedBookMeta, const fs::path &destinationPath);

  signals:
    void itemClicked(const QString &filePath);

  private:
    QTableWidget *tableWidget;
    QVBoxLayout *layout;
    std::string m_folderPath;
    BookDB database;
};