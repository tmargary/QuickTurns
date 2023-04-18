#pragma once
#include <QListWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QWidget>

#include "DataBase.h"

class HomeView : public QWidget {
    Q_OBJECT

public:
    explicit HomeView(const QString &folderPath, QWidget *parent = nullptr);
    void setupListWidget();
    void setupAddFileButton();
    void addBookToListWidget(const QString &bookName, const QString &bookPath);

private:
    void setButtonStyle(QPushButton *button);
    QString createDestinationPath(const QString &fileName);
    bool bookExists(const Book &bookToCheck);
    void handleButtonClick();

signals:
    void itemClicked(const QString &filePath);

private:
    QListWidget *listWidget;
    QVBoxLayout *layout;
    std::string m_folderPath;
    BookDB database;
};