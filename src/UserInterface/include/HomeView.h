#pragma once
#include <QDir>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
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

  private:
    void setButtonStyle(QPushButton *button);
    QString createDestinationPath(const QString &fileName);
    bool bookExists(const Book &bookToCheck);
    void handleButtonClick();
    Book parseMetadataAndCheckDatabase(const QString &filePath);
    bool createDestinationDirectory(QDir &destinationDir, const fs::path &destinationPath);
    void copyBookAndCover(const QString &filePath, const fs::path &destinationPath);
    void addBookToDatabaseAndTableWidget(const Book &addedBookMeta, const fs::path &destinationPath);

  private:
    void updateMetadataLabel(const Book &book);
    void updateCoverLabel(const fs::path &bookPath);
    void updateMetadataAndCoverLabels(const QString &bookPath);
    

  signals:
    void itemClicked(const QString &filePath);

  private:
    QLabel *coverLabel;
    QPushButton *addFileButton;
    QLabel *metadataLabel;
    QTableWidget *tableWidget;
    QVBoxLayout *mainLayout;
    std::string m_folderPath;
    BookDB database;
};